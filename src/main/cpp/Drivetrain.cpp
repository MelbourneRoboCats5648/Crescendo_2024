#include "DriveTrain.h"

//Encoder Counts Per RV
const int countsPerRevolution = 4096;

// Locations for the swerve drive modules relative to the robot center.
frc::Translation2d m_frontLeftLocation{0.260825_m, 0.260825_m};
frc::Translation2d m_frontRightLocation{0.259325_m, -260825_m};
frc::Translation2d m_backLeftLocation{-0.260825_m, 0.259825_m};
frc::Translation2d m_backRightLocation{-0.259325_m, -0.259825_m};
const frc::SwerveDriveKinematics<4> kinematics{
                                        m_frontLeftLocation, 
                                        m_frontRightLocation, 
                                        m_backLeftLocation,
                                        m_backRightLocation};

void DriveTrain::SetAllModules(frc::ChassisSpeeds chassisSpeed){
     
    // Convert to module states. Here, we can use C++17's structured
    // bindings feature to automatically split up the array into its
    // individual SwerveModuleState components.
    auto [fl, fr, bl, br] = kinematics.ToSwerveModuleStates(chassisSpeed);
    SetModule(fl, m_frontLeftModule);
    //SetModule(fr, m_frontRightModule);
    SetModule(bl, m_backLeftModule);
    SetModule(br, m_backRightModule);
}

void DriveTrain::SetAllModulesZero()
{
  m_frontLeftModule.SetZero();
  m_frontRightModule.SetZero();
  m_backLeftModule.SetZero();
  m_backRightModule.SetZero();
}

void DriveModule::SetZero()
{
  m_speedMotor.Set(0.0);
  m_directionMotor.Set(0.0);
}

/*
 * tell motors how to move
 * get motor angle and speed from module state info
 * move each motor
 * update the PID controller
*/
void DriveTrain::SetModule(frc::SwerveModuleState state, DriveModule& driveModule) {
  // Setting Motor Speed
  const units::meters_per_second_t MAX_SPEED_MPS = 30.0_mps;

  double normalisedSpeed = state.speed / MAX_SPEED_MPS;

  driveModule.m_speedMotor.Set(normalisedSpeed);

  //TODO check encoder range, also check if the GetValue returns radians or degrees
  units::angle::radian_t encoderCurrentAngle = driveModule.m_directionEncoder.GetAbsolutePosition().GetValue();
  //double encoderRotation = (encoderCurrentAngle/(2 * M_PI));

  //optimise
  //frc::SwerveModuleState::Optimize(state, encoderCurrentAngle);

  // Calculate the turning motor output from the turning PID controller.
  //  const auto turnOutput = driveModule.m_turningPIDController.Calculate(
  //    encoderCurrentAngle, state.angle.Radians());

  // Set the motor outputs for the turning of the wheels
  double normalisedAngle = state.angle.Radians() / units::angle::radian_t(10 * 2 * M_PI);
  //driveModule.m_directionMotor.Set(normalisedAngle);
  driveModule.m_directionMotor.Set(normalisedAngle);

};

