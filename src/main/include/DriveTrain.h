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
    }

public:
    TalonFX m_speedMotor;
    TalonFX m_directionMotor;
    CANcoder m_directionEncoder;
    frc::ProfiledPIDController<units::radians> m_turningPIDController;
};


const int FRONT_LEFT_SPEED_MOTOR_ID = 1;
const int FRONT_RIGHT_SPEED_MOTOR_ID = 2;
const int BACK_LEFT_SPEED_MOTOR_ID = 3;
const int BACK_RIGHT_SPEED_MOTOR_ID = 4;

const int FRONT_LEFT_DIRECTION_MOTOR_ID = 5;
const int FRONT_RIGHT_DIRECTION_MOTOR_ID = 6;
const int BACK_LEFT_DIRECTION_MOTOR_ID = 7;
const int BACK_RIGHT_DIRECTION_MOTOR_ID = 8;

const int FRONT_LEFT_DIRECTION_ENCODER_ID = 9;
const int FRONT_RIGHT_DIRECTION_ENCODER_ID = 10;
const int BACK_LEFT_DIRECTION_ENCODER_ID = 11;
const int BACK_RIGHT_DIRECTION_ENCODER_ID = 12;

class DriveTrain{
public:
    void SetAllModules(frc::ChassisSpeeds chasisSpeed);

private:
    void SetModule(frc::SwerveModuleState state, DriveModule& driveModule);

private:
    DriveModule m_frontLeftModule{FRONT_LEFT_SPEED_MOTOR_ID, FRONT_LEFT_DIRECTION_MOTOR_ID, FRONT_LEFT_DIRECTION_ENCODER_ID};
    DriveModule m_frontRightModule{FRONT_RIGHT_SPEED_MOTOR_ID, FRONT_RIGHT_DIRECTION_MOTOR_ID, FRONT_RIGHT_DIRECTION_ENCODER_ID};
    DriveModule m_backLeftModule{BACK_LEFT_SPEED_MOTOR_ID, BACK_LEFT_DIRECTION_MOTOR_ID, BACK_LEFT_DIRECTION_ENCODER_ID};
    DriveModule m_backRightModule{BACK_RIGHT_SPEED_MOTOR_ID, BACK_RIGHT_DIRECTION_MOTOR_ID, BACK_RIGHT_DIRECTION_ENCODER_ID};
};