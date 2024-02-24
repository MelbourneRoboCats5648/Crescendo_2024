#include "DriveTrain.h"

//Encoder Counts Per RV
const int countsPerRevolution = 4096;

// Locations for the swerve drive modules relative to the robot center.
frc::Translation2d m_frontLeftLocation{0.260825_m, 0.260825_m};
frc::Translation2d m_frontRightLocation{0.259325_m, -0.260825_m};
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
    //m_frontLeftModule.SetModule(fl);
    //m_frontRightModule.SetModule(fr);
    //m_backLeftModule.SetModule(bl);
    m_backRightModule.SetModule(br);
}

void DriveTrain::InitialiseAllModules()
{
  m_frontLeftModule.Initialise();
  m_frontRightModule.Initialise();
  m_backLeftModule.Initialise();
  m_backRightModule.Initialise();
}

/*void DriveTrain::SetAllModulesZero()
{
  m_frontLeftModule.SetZero();
  m_frontRightModule.SetZero();
  m_backLeftModule.SetZero();
  m_backRightModule.SetZero();
}*/

void DriveTrain::StopAllModules()
{
  m_frontLeftModule.Stop();
  m_frontRightModule.Stop();
  m_backLeftModule.Stop();
  m_backRightModule.Stop();
}

/*
 * tell motors how to move
 * get motor angle and speed from module state info
 * move each motor
 * update the PID controller
*/


