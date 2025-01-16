#pragma once

#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/CANcoder.hpp>
#include <units/angle.h>
#include <frc/ADIS16470_IMU.h>

#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/kinematics/SwerveDriveOdometry.h>
#include <frc/controller/ProfiledPIDController.h>

#include "DriveModule.h"

const int FRONT_LEFT_SPEED_MOTOR_ID = 4;
const int FRONT_RIGHT_SPEED_MOTOR_ID = 2;
const int BACK_LEFT_SPEED_MOTOR_ID = 6;
const int BACK_RIGHT_SPEED_MOTOR_ID = 7;

const int FRONT_LEFT_DIRECTION_MOTOR_ID = 3;
const int FRONT_RIGHT_DIRECTION_MOTOR_ID = 5;
const int BACK_LEFT_DIRECTION_MOTOR_ID = 1;
const int BACK_RIGHT_DIRECTION_MOTOR_ID = 8;

const int FRONT_LEFT_DIRECTION_ENCODER_ID = 9;
const int FRONT_RIGHT_DIRECTION_ENCODER_ID = 10;
const int BACK_LEFT_DIRECTION_ENCODER_ID = 12;
const int BACK_RIGHT_DIRECTION_ENCODER_ID = 11;

const units::angle::turn_t FRONT_LEFT_MAG_OFFSET = units::angle::turn_t(0.303955);
const units::angle::turn_t FRONT_RIGHT_MAG_OFFSET = units::angle::turn_t(0.346436);
const units::angle::turn_t BACK_LEFT_MAG_OFFSET = units::angle::turn_t(0.064697);
const units::angle::turn_t BACK_RIGHT_MAG_OFFSET = units::angle::turn_t(0.015381); // this mag offset has been set by the phoenix tuner set the new offsets
// set the offsets by using pheonix tuner

// Locations for the swerve drive modules relative to the robot center.
// TODO - the below fails build if static keyword not used
static frc::Translation2d backLeftLocation{-0.26_m, +0.26_m};
static frc::Translation2d backRightLocation{-0.26_m, -0.26_m};
static frc::Translation2d frontLeftLocation{+0.26_m, +0.26_m};
static frc::Translation2d frontRightLocation{+0.26_m, -0.26_m};

class DriveTrain{
public:
    DriveTrain() :
        m_gyro()
    {
    }

public:
    void SetAllModules(frc::ChassisSpeeds chasisSpeed);
    void StopAllModules();
    void InitialiseAllModules();
    void ResetGyro();
    double GetPositionDistance();
    void SetPositionToZeroDistance();

public:
    frc::ADIS16470_IMU m_gyro;

    DriveModule m_frontLeftModule{FRONT_LEFT_SPEED_MOTOR_ID, FRONT_LEFT_DIRECTION_MOTOR_ID, FRONT_LEFT_DIRECTION_ENCODER_ID, FRONT_LEFT_MAG_OFFSET, "Front Left"};
    DriveModule m_frontRightModule{FRONT_RIGHT_SPEED_MOTOR_ID, FRONT_RIGHT_DIRECTION_MOTOR_ID, FRONT_RIGHT_DIRECTION_ENCODER_ID, FRONT_RIGHT_MAG_OFFSET, "Front Right"};
    DriveModule m_backLeftModule{BACK_LEFT_SPEED_MOTOR_ID, BACK_LEFT_DIRECTION_MOTOR_ID, BACK_LEFT_DIRECTION_ENCODER_ID, BACK_LEFT_MAG_OFFSET, "Back Left"};
    DriveModule m_backRightModule{BACK_RIGHT_SPEED_MOTOR_ID, BACK_RIGHT_DIRECTION_MOTOR_ID, BACK_RIGHT_DIRECTION_ENCODER_ID, BACK_RIGHT_MAG_OFFSET, "Back Right"};

public:
    const frc::SwerveDriveKinematics<4> kinematics{
                                        frontLeftLocation, 
                                        frontRightLocation, 
                                        backLeftLocation,
                                        backRightLocation};

};