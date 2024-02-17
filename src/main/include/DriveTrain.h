#pragma once

#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/CANcoder.hpp>
#include <units/angle.h>

#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/controller/ProfiledPIDController.h>

using namespace ctre::phoenix6::hardware;

//Module constants defining
 static constexpr auto kModuleMaxAngularVelocity =
      std::numbers::pi * 1_rad_per_s;  // radians per second
 static constexpr auto kModuleMaxAngularAcceleration =
    std::numbers::pi * 2_rad_per_s / 1_s;  // radians per second^2

class DriveModule{
public:
    DriveModule(int speedMotorID, int directionMotorID, int directionEncoderID) :
        m_speedMotor(speedMotorID, "rio"),
        m_directionMotor(directionMotorID, "rio"),
        m_directionEncoder(directionEncoderID, "rio"),
        m_turningPIDController{
            1.0,
            0.0,
            0.0,
            {kModuleMaxAngularVelocity, kModuleMaxAngularAcceleration}}
    {
        // Reset PID controller on startup
    }

public:
    TalonFX m_speedMotor;
    TalonFX m_directionMotor;
    CANcoder m_directionEncoder;
    frc::ProfiledPIDController<units::radians> m_turningPIDController;
};

class DriveTrain{
public:
    void SetAllModules(frc::ChassisSpeeds chasisSpeed);

private:
    void SetModule(frc::SwerveModuleState state, DriveModule& driveModule);

private:
    // Todo - update these hard coded id numbers to constants
    DriveModule m_frontLeftModule{1, 5, 9};
    DriveModule m_frontRightModule{2, 6, 10};
    DriveModule m_backLeftModule{3, 7, 11};
    DriveModule m_backRightModule{4, 5, 12};
};