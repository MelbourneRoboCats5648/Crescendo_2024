#include "DriveModule.h"
#include <iostream>

using namespace ctre::phoenix6::configs;
using namespace ctre::phoenix6::signals;

void DriveModule::Stop()
{
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

    m_turningPIDController.EnableContinuousInput(
      units::angle::radian_t{-1.0*M_PI},
      units::angle::radian_t{M_PI});
}

void DriveModule::SetModule(frc::SwerveModuleState state) {
  // encoder range -0.5 +0.5,  GetValue returns rotation
  // encoder current angle is -pi to +pi
  units::angle::radian_t encoderCurrentAngleRadians = units::angle::radian_t{m_directionEncoder.GetAbsolutePosition().GetValueAsDouble()*2*M_PI};
  
    // updates state variable angle to the optimum change in angle
  frc::SwerveModuleState::Optimize(state, encoderCurrentAngleRadians);

  // Setting Motor Speed
  const units::meters_per_second_t MAX_SPEED_MPS = 5.0_mps;
  double normalisedSpeed = state.speed / MAX_SPEED_MPS;
  m_speedMotor.Set(normalisedSpeed);

  // Calculate the turning motor output from the turning PID controller.
  const auto turnOutput = m_turningPIDController.Calculate(
    encoderCurrentAngleRadians, state.angle.Radians());

  // Set the motor outputs for the turning of the wheels
  //units::angle::radian_t error = state.angle.Radians() - encoderCurrentAngle;
  //double normalisedAngle = error / units::angle::radian_t(10*M_PI);
  //driveModule.m_directionMotor.Set(normalisedAngle);

  std::cout << "State speed " << double{state.speed} << std::endl;
  std::cout << "Encoder current angle " << double{encoderCurrentAngleRadians} << std::endl;
  std::cout << "State angle " << double{state.angle.Radians()} << std::endl;
  std::cout << "Turn output " << double{-1.0 * turnOutput} << std::endl << std::endl;
    
  

  m_directionMotor.SetVoltage(units::voltage::volt_t{-1.0 * turnOutput});
};