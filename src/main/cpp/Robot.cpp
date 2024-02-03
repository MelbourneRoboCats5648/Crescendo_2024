// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/motorcontrol/VictorSP.h>

#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include <frc/Encoder.h>

#include "hal/AnalogTrigger.h"
#include "hal/Types.h"

// PWM ports - TODO Check
const int motorClimbLeftPort = 0;
const int motorClimbRightPort = 1;
const int motorShooterLeftPort = 2;
const int motorShooterRightPort = 3;
const int motorIntakeArmPort = 4;
const int motorIntakeWheelPort = 5;

// USB ports - TODO Check
const int driveJoystickPort = 0;
const int xboxControllerPort = 1;

// Joystick buttons - TODO Check
const int leftUpButton = 1;
const int leftDownButton = 2;
const int rightUpButton = 3;
const int rightDownButton = 4;

// Speeds
const int climbUpSpeed = 0.8;
const int climbDownSpeed = -0.8;

const int speakerShooterSpeed = 1;
const int ampShooterSpeed = 0.5;

const int intakeArmRetractSpeed = 0.8;
const int intakeArmExtendSpeed = -0.8;
const int intakeWheelInSpeed = 0.5;
const int intakeWheelOutSpeed = -0.5;

/** Intake encoder
const int aChannel = 0; 
const int bChannel = 1; 
*/


// xbox buttons
const int dpadUpButton = 0;
const int dpadDownButton = 180;

// Controllers
frc::XboxController xbox{xboxControllerPort};

// Climb variables
frc::VictorSP motorClimbLeft{motorClimbLeftPort};
frc::VictorSP motorClimbRight{motorClimbRightPort};
frc::Joystick driveJoyStick{driveJoystickPort};


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

  if (driveJoyStick.GetRawButton(leftUpButton))
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
}

//When Shooting, the Y and A buttons will control the speed for the shooter
//When The driver wants to shoot the note, they will use the intake release button
//Make sure the shooter wheels are running before releasing intake to shoot

void Robot::Shooter(){

frc::VictorSP motorShooterLeft{motorShooterLeftPort};
frc::VictorSP motorShooterRight{motorShooterRightPort};




//Speaker
if (xbox.GetYButtonPressed())
{
  motorShooterLeft.Set(speakerShooterSpeed);
  motorShooterRight.Set(speakerShooterSpeed);
}

//Amp
else if (xbox.GetAButtonPressed())
{
  motorShooterLeft.Set(ampShooterSpeed);
  motorShooterRight.Set(ampShooterSpeed);
}
else
{
  motorShooterLeft.Set(0);
  motorShooterRight.Set(0);
}


}


/**
 * Controls the intake arms and wheels
 * Controls 2 motors independently (one for move arms one for wheels)
 * Swing arms up and down → 1 motor - up button for in, down button for out
 * Spin wheels opposite directions (1 motor)
 * Triggers are for note in and out (wheel spinning)
 * Plus button for arm in and out
**/

void Robot::Intake() {

frc::VictorSP motorIntakeArm{motorIntakeArmPort};
frc::VictorSP motorIntakeWheel{motorIntakeWheelPort};
//frc::Encoder encoderIntake{aChannel, bChannel};

// arm in and out
if (xbox.GetPOV(dpadUpButton))
{
  motorIntakeArm.Set(intakeArmRetractSpeed);
}

else if (xbox.GetPOV(dpadDownButton))
{
  motorIntakeArm.Set(intakeArmExtendSpeed);
}

else 
{
  motorIntakeArm.Set(0);
}

// intake wheels spinning
// right trigger wheel in left trigger wheel out
// josh help how to fix
if (xbox.GetLeftTriggerAxis())
 {
  motorIntakeWheel.Set(intakeWheelOutSpeed);
 }

else if (xbox.GetRightTriggerAxis())
{
  motorIntakeWheel.Set(intakeWheelInSpeed);
}

else
{
  motorIntakeWheel.Set(0);
}

}

// For intake:
// define our motor $$
// define 2 speeds $$
// assign triggers $$
// assign plus button thingy $$
// deine xbox $$
// code the encoder





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