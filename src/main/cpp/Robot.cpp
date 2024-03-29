// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include "Climb.h"
#include "Intake.h"
#include "Shooter.h"
#include "MoveTeleop.h"
#include "MoveAutonomous.h"

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <frc/Joystick.h>
#include <frc/XboxController.h>

#include "cameraserver/CameraServer.h"

// USB ports - TODO Check
const int driveJoystickPort = 0;
const int xboxControllerPort = 1;

//Drivetrain
DriveTrain driveTrain{};

//gyro
frc::ADIS16470_IMU gyro{};

// Controllers
frc::XboxController xbox{xboxControllerPort};
frc::Joystick driveJoyStick{driveJoystickPort};

//MotorPorts
// PWM ports - TODO Check
const int motorShooterLeftPort = 4;
const int motorShooterRightPort = 5;
//PWM Ports
const int motorIntakeArmPort = 2;
const int motorIntakeWheelPort = 3;

//Motors
frc::VictorSP motorIntakeArm{motorIntakeArmPort};
frc::VictorSP motorIntakeWheel{motorIntakeWheelPort};

frc::VictorSP motorShooterLeft{motorShooterLeftPort};
frc::VictorSP motorShooterRight{motorShooterRightPort};

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  gyro.Calibrate();

  driveTrain.InitialiseAllModules();
  driveTrain.StopAllModules();

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
    AutoInit(driveTrain);
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
    AutoYay(driveTrain, motorShooterLeft, motorShooterRight, motorIntakeArm, motorIntakeWheel);
  
  }
  }


void Robot::TeleopInit() {

  driveTrain.StopAllModules();

}

void Robot::TeleopPeriodic() {
  Climb(driveJoyStick);
  Intake(xbox, motorIntakeArm, motorIntakeWheel);
  Shooter(xbox, motorShooterLeft, motorShooterRight);
  
  MoveTeleop(driveTrain, driveJoyStick, gyro);
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
