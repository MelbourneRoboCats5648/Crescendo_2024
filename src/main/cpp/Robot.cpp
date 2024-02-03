// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/motorcontrol/VictorSP.h>
#include <frc/Joystick.h>

// PWM ports - TODO Check
const int motorClimbLeftPort = 0;
const int motorClimbRightPort = 1;

// USB ports - TODO Check
const int driveJoystickPort = 0;

// Joystick buttons - TODO Check
const int leftUpButton = 1;
const int leftDownButton = 2;
const int rightUpButton = 3;
const int rightDownButton = 4;

// Speed constants
const int climbUpSpeed = 0.8;
const int climbDownSpeed = -0.8;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
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
 * Controls the climbing arms.
 * Controls 2 Victor SP motors independently.
 * Controlled by the Joystick controller using the top buttons
 * This will allow the driver to raise and lower the climb arms independently
 * 
 * TODO - research how to 'lock' our climb
 */
void Robot::Climb() {
  frc::VictorSP motorClimbLeft{motorClimbLeftPort};
  frc::VictorSP motorClimbRight{motorClimbRightPort};
  frc::Joystick driveJoyStick{driveJoystickPort};

  /* Lauren's code 
  if (driveJoystick.GetRawButton(leftUpButton))
  {
    motorClimbLeft.Set(0.8);
  }
  */
 
  //Ariya's code 
  /*if (driveJoyStick.GetRawButton(leftUpButton))
  {
    motorClimbLeft.Set(0.8);
  }
  else if (driveJoyStick.GetRawButtonReleased(leftUpButton))
  {
    motorClimbLeft.Set(0);
  }
  if (driveJoyStick.GetRawButton(leftDownButton))
  {
    motorClimbLeft.Set(-0.8);
  }
   else if (driveJoyStick.GetRawButtonReleased(leftDownButton))
  {
    motorClimbLeft.Set(0);
  }


  if (driveJoyStick.GetRawButton(rightUpButton))
  {
    motorClimbRight.Set(0.8);
  }
   else if (driveJoyStick.GetRawButtonReleased(rightUpButton))
  {
    motorClimbRight.Set(0);
  }
    if (driveJoyStick.GetRawButton(rightDownButton))
  {
    motorClimbRight.Set(-0.8);
  }
   else if (driveJoyStick.GetRawButtonReleased(rightDownButton))
  {
    motorClimbRight.Set(0);
  }*/

  // Mikaela's code
  /*if (driveJoyStick.GetRawButton(leftUpButton))
{
  motorClimbLeft.Set(climbUpSpeed);
}
else if (driveJoyStick.GetRawButton(leftDownButton))
{
  motorClimbLeft.Set(climbDownSpeed);
}
else
{
  motorClimbLeft.Set(0);
}

if (driveJoyStick.GetRawButton(rightUpButton))
{
  motorClimbRight.Set(climbUpSpeed);
}
else if (driveJoyStick.GetRawButton(rightDownButton))
{
  motorClimbRight.Set(climbDownSpeed);
}
else
{
  motorClimbRight.Set(0);
}
*/


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
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {}

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