#include "DriveModule.h"


void DriveModule::SetZero()
{
  m_speedMotor.Set(0.0);
  m_directionMotor.Set(0.0);
}

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
}

void DriveModule::SetModule(frc::SwerveModuleState state) {
  // Setting Motor Speed
  const units::meters_per_second_t MAX_SPEED_MPS = 30.0_mps;

  double normalisedSpeed = state.speed / MAX_SPEED_MPS;

    m_speedMotor.Set(normalisedSpeed);

  //TODO check encoder range, also check if the GetValue returns radians or degrees
  units::angle::radian_t encoderCurrentAngle = m_directionEncoder.GetAbsolutePosition().GetValue();
  //double encoderRotation = (encoderCurrentAngle/(2 * M_PI));

  //optimise
  //frc::SwerveModuleState::Optimize(state, encoderCurrentAngle);

  // Calculate the turning motor output from the turning PID controller.
  //  const auto turnOutput = driveModule.m_turningPIDController.Calculate(
  //    encoderCurrentAngle, state.angle.Radians());

  // Set the motor outputs for the turning of the wheels
  double normalisedAngle = state.angle.Radians() / units::angle::radian_t(10 * 2 * M_PI);
  //driveModule.m_directionMotor.Set(normalisedAngle);
  m_directionMotor.Set(normalisedAngle);

};