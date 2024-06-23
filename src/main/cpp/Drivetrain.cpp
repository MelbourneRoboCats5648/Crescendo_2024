#include "DriveTrain.h"

void DriveTrain::SetAllModules(frc::ChassisSpeeds chassisSpeed){
     
    // Convert to module states. Here, we can use C++17's structured
    // bindings feature to automatically split up the array into its
    // individual SwerveModuleState components.
    // chassisSpeed = frc::ChassisSpeeds::FromFieldRelativeSpeeds(chassisSpeed, robotAngle) // <- switch to FR
    auto states = kinematics.ToSwerveModuleStates(chassisSpeed);

  // limit to max speed
  const units::meters_per_second_t MAX_SPEED_MPS = 5.0_mps;
  kinematics.DesaturateWheelSpeeds(&states, MAX_SPEED_MPS);

  auto [fl, fr, bl, br] = states;

    m_frontLeftModule.SetModule(fl);
    m_frontRightModule.SetModule(fr);
    m_backLeftModule.SetModule(bl);
    m_backRightModule.SetModule(br);
}

void DriveTrain::InitialiseAllModules()
{
  m_gyro.Calibrate();
    
  m_frontLeftModule.Initialise();
  m_frontRightModule.Initialise();
  m_backLeftModule.Initialise();
  m_backRightModule.Initialise();
}

void DriveTrain::ResetGyro()
{
  m_gyro.Reset();
}

void DriveTrain::StopAllModules()
{
  m_frontLeftModule.Stop();
  m_frontRightModule.Stop();
  m_backLeftModule.Stop();
  m_backRightModule.Stop();
}

double DriveTrain::GetPositionDistance()
{
  return (m_frontLeftModule.GetModulePositionDistance()+
  m_frontRightModule.GetModulePositionDistance()+
  m_backLeftModule.GetModulePositionDistance()+
  m_backRightModule.GetModulePositionDistance())/4;
}

void DriveTrain::SetPositionToZeroDistance()
{
  m_frontLeftModule.SetModulePositionToZeroDistance();
  m_frontRightModule.SetModulePositionToZeroDistance();
  m_backLeftModule.SetModulePositionToZeroDistance();
  m_backRightModule.SetModulePositionToZeroDistance();
}

