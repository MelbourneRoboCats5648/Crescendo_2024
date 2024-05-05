#include "DriveModule.h"
#include <iostream>

using namespace ctre::phoenix6::configs;
using namespace ctre::phoenix6::signals;

void DriveModule::Stop()
{
  m_directionMotor.Set(0);
  m_speedMotor.Set(0);
  m_speedMotor.StopMotor();
  m_directionMotor.StopMotor();
}

void DriveModule::Initialise()
{
    // Wait for at most 250ms for a CAN position update
    // From:
    // https://www.chiefdelphi.com/t/converting-c-swerve-code-from-phoenix-5-to-phoenix-6-not-pro/450050/2
    m_directionMotor.SetPosition(m_directionEncoder.GetAbsolutePosition().WaitForUpdate(250_ms).GetValue());
    
    // Config CANCoder   
    CANcoderConfiguration cancoderConfig;
    cancoderConfig.MagnetSensor.AbsoluteSensorRange = AbsoluteSensorRangeValue::Signed_PlusMinusHalf;
    cancoderConfig.MagnetSensor.SensorDirection = SensorDirectionValue::CounterClockwise_Positive;
    cancoderConfig.MagnetSensor.MagnetOffset = m_magOffset;
    m_directionEncoder.GetConfigurator().Apply(cancoderConfig);

    // Drive motor config
    // To setup the drive motor to be able to drive at a target speed
    TalonFXConfiguration speedMotorConfig;
    speedMotorConfig.Feedback.FeedbackSensorSource = FeedbackSensorSourceValue::RotorSensor;
    speedMotorConfig.Feedback.SensorToMechanismRatio = DRIVE_GEAR_RATIO;
    speedMotorConfig.ClosedLoopGeneral.ContinuousWrap = false;
    speedMotorConfig.Slot0.kP = 0.3;
    speedMotorConfig.Slot0.kI = 0.0;
    speedMotorConfig.Slot0.kD = 0.0;
    speedMotorConfig.CurrentLimits.SupplyCurrentLimitEnable = true;
    speedMotorConfig.Slot0.kV = 0.1;
    speedMotorConfig.CurrentLimits.SupplyCurrentLimit = 50;      // Amps
    speedMotorConfig.CurrentLimits.SupplyCurrentThreshold = 60;  // Amps
    speedMotorConfig.CurrentLimits.SupplyTimeThreshold = 0.1;    // Seconds
    speedMotorConfig.MotorOutput.Inverted = true;  // +V should rotate the motor counter-clockwise
    speedMotorConfig.MotorOutput.NeutralMode = NeutralModeValue::Brake;
    m_speedMotor.GetConfigurator().Apply(speedMotorConfig);

    //example: https://github.com/Liam-Stow/flex-commandsInSubsystems/blob/master/src/main/cpp/utilities/SwerveModule.cpp
    // speedMotorConfig.Feedback.FeedbackSensorSource = FeedbaclSensorSourceValue::RotorSensor;
    // other things to config
    /*
      speedMotorConfig.Slot0.kV = <amount of volts to drive at 1 wheel turn per second> // tune this first, then PID
    */

    m_turningPIDController.EnableContinuousInput(
      units::angle::radian_t{-1.0*M_PI},
      units::angle::radian_t{M_PI});
}

void DriveModule::SetModule(frc::SwerveModuleState state) {
  // encoder range -0.5 +0.5,  GetValue returns rotation
  // encoder current angle is -pi to +pi
  units::angle::radian_t encoderCurrentAngleRadians = units::angle::radian_t{m_directionEncoder.GetAbsolutePosition().GetValueAsDouble()*2*M_PI};
  
    // updates state variable angle to the optimum change in angle
  auto optimizedState = state = frc::SwerveModuleState::Optimize(state, encoderCurrentAngleRadians);

  // Setting Motor Speed
  ////const units::meters_per_second_t MAX_SPEED_MPS = 5.0_mps;
  // double normalisedSpeed = state.speed / MAX_SPEED_MPS; // max speed set in DriveTrain::SetAllModules()

  //to find desired wheel speed:
  // divide desired robot speed (m/s) by wheel circumference (set CIRCUMFERECNE in header file)
  
  // to set the speed using control onboard the motor, use m_speedMotor.SetControl(ctre::phoenix6::controls::VelocityVoltage{desiredWheelSpeed}); // desiredWheelSpeed in turns per second
  units::angular_velocity::turns_per_second_t desiredWheelSpeed{(state.speed.value())/WHEEL_CIRCUMFERENCE.value()};
  m_speedMotor.SetControl(ctre::phoenix6::controls::VelocityVoltage{desiredWheelSpeed*6.75});
  ////m_speedMotor.Set(normalisedSpeed); 

  // Calculate the turning motor output from the turning PID controller. 
  const auto turnOutput = m_turningPIDController.Calculate(
    encoderCurrentAngleRadians, optimizedState.angle.Radians());

  // Set the motor outputs for the turning of the wheels
  //units::angle::radian_t error = state.angle.Radians() - encoderCurrentAngle;
  //double normalisedAngle = error / units::angle::radian_t(10*M_PI);
  //driveModule.m_directionMotor.Set(normalisedAngle);

  /*std::cout << "State speed " << double{state.speed} << std::endl;
  std::cout << "desiredANGLE " << double{optimizedState.angle.Radians()} << std::endl;
  std::cout << "State angle " << double{state.angle.Radians()} << std::endl;
  std::cout << "Turn output " << double{-1.0 * turnOutput} << std::endl << std::endl;*/
    
  
  // alternative to using negative voltage is to invert the motor with motorConfig.MotorOutput.Inverted = true; when setting up the configs.
  m_directionMotor.SetVoltage(units::voltage::volt_t{-1.0 * turnOutput});
}

double DriveModule::GetModulePositionDistance()
{
  double distance = m_speedMotor.GetPosition().GetValueAsDouble()*0.3198;  
  std::cout << m_name << " modulePosition " << distance << std::endl;
  return distance;
}

void DriveModule::SetModulePositionToZeroDistance()
{
  m_speedMotor.SetPosition(units::angle::turn_t {0.0});
}