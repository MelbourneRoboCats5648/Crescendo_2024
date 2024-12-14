// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include "MoveTeleop.h"
#include "MoveAutonomous.h"

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "cameraserver/CameraServer.h"

const int JOYSTICK_BUTTON_11 = 11;

frc::Timer shooterTimer{};

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  m_driveTrain.InitialiseAllModules();
  m_driveTrain.ResetGyro();
  m_driveTrain.StopAllModules();

  cs::UsbCamera usbCamera = frc::CameraServer::StartAutomaticCapture();
  usbCamera.SetResolution(640, 480);

}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic()
{

}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  fmt::print("Auto selected: {}\n", m_autoSelected);

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
    m_newAuto.AutoInit(m_driveTrain);
  }
  m_driveTrain.InitialiseAllModules();
  m_driveTrain.ResetGyro();
  m_driveTrain.StopAllModules();

}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
    m_newAuto.AutoYay(m_driveTrain, m_shootAndIntake);

  
  }
  }


void Robot::TeleopInit() {

  m_driveTrain.StopAllModules();

}

void Robot::TeleopPeriodic() {
  m_climb.ClimbFunctions(m_driveJoyStick);
  m_shootAndIntake.m_intake.DoIntake(m_xbox);
  m_shootAndIntake.m_shooter.DoShoot(m_xbox);
  
  //when xbox button is pressed it starts the timer which lets the shootandintakefunction know when to shoot
  if (m_xbox.GetLeftStickButtonPressed() == true)
  {
    shooterTimer.Reset();
    shooterTimer.Start();
  }
   m_shootAndIntake.ShootAndIntakeFunctions(shooterTimer);

  if (m_xbox.GetRightTriggerAxis())
  {
    // power the intake while driving forward at desired speed
    IntakingButton(m_shootAndIntake, m_driveTrain, 0.5_mps);
  }
  else 
  {
    MoveTeleop(m_driveTrain, m_driveJoyStick, m_driveTrain.m_gyro);
  }

  if (m_driveJoyStick.GetRawButtonPressed(JOYSTICK_BUTTON_11) == true)
  {
    m_driveTrain.ResetGyro();
  }

}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
