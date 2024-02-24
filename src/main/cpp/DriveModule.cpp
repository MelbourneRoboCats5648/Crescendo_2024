#include "DriveModule.h"
#include <iostream>

using namespace ctre::phoenix6::configs;
using namespace ctre::phoenix6::signals;

//encoders might have to be calibrated manually.
/*void DriveModule::SetEncodersZero()
{
  m_directionEncoder.

}*/

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
    m_directionMotor.SetPosition(m_directionEncoder.GetPosition().WaitForUpdate(250_ms).GetValue());
    // Config CANCoder
    /*CANcoderConfiguration cancoderConfig;
    cancoderConfig.MagnetSensor.AbsoluteSensorRange = AbsoluteSensorRangeValue::Signed_PlusMinusHalf;
    cancoderConfig.MagnetSensor.SensorDirection = SensorDirectionValue::CounterClockwise_Positive;
    cancoderConfig.MagnetSensor.MagnetOffset = m_magOffset;
    m_directionEncoder.GetConfigurator().Apply(cancoderConfig);*/

}

void DriveModule::SetModule(frc::SwerveModuleState state) {
  //optimise
  //frc::SwerveModuleState::Optimize(state, encoderCurrentAngle);
  
  // Setting Motor Speed
  const units::meters_per_second_t MAX_SPEED_MPS = 5.0_mps;

  double normalisedSpeed = state.speed / MAX_SPEED_MPS;

  m_speedMotor.Set(normalisedSpeed);

  //encoder range -0.5 +0.5,  GetValue returns rotation
  // encoder current angle is -pi to +pi
  units::angle::radian_t encoderCurrentAngle = units::angle::radian_t{m_directionEncoder.GetAbsolutePosition().GetValueAsDouble()*2*M_PI};
  //double encoderRotation = (encoderCurrentAngle/(2 * M_PI));

  // Calculate the turning motor output from the turning PID controller.
  const auto turnOutput = m_turningPIDController.Calculate(
    encoderCurrentAngle, state.angle.Radians());

  // Set the motor outputs for the turning of the wheels
  //units::angle::radian_t error = state.angle.Radians() - encoderCurrentAngle;
  //double normalisedAngle = error / units::angle::radian_t(10*M_PI);
  //driveModule.m_directionMotor.Set(normalisedAngle);
  std::cout << "State speed " << double{state.speed} << " state angle " << double{state.angle.Radians()} << "encoder current angle " << double{encoderCurrentAngle} << "\n";
  std::cout << "turnoutput " << double{turnOutput} << "\n";
    
  m_directionMotor.SetVoltage(units::voltage::volt_t{turnOutput});

};