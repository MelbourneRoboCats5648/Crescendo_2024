// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "DriveTrain.h"
#include "Climb.h"
#include "ShootAndIntake.h"
#include "IntakingButton.h"

#include <frc/Joystick.h>
#include <frc/XboxController.h>

// USB ports - TODO Check
const int driveJoystickPort = 0;
const int xboxControllerPort = 1;

class Robot : public frc::TimedRobot {
  public:
    void RobotInit() override;
    void RobotPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void DisabledInit() override;
    void DisabledPeriodic() override;
    void TestInit() override;
    void TestPeriodic() override;
    void SimulationInit() override;
    void SimulationPeriodic() override;
   
  private:
    frc::SendableChooser<std::string> m_chooser;
    const std::string kAutoNameDefault = "Default";
    const std::string kAutoNameCustom = "My Auto";
    std::string m_autoSelected;

  public:
    ShootAndIntake m_shootAndIntake;
    DriveTrain m_driveTrain{};
    // Controllers
    frc::XboxController m_xbox{xboxControllerPort};
    frc::Joystick m_driveJoyStick{driveJoystickPort};
    Climb m_climb;

};
