#pragma once

#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/CANcoder.hpp>
#include <units/angle.h>

#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/controller/ProfiledPIDController.h>

#include "DriveModule.h"


class DriveTrain{
public:
    void SetAllModules(frc::ChassisSpeeds chasisSpeed);
    void StopAllModules();
    void InitialiseAllModules();
    void SetAllModulesZero();

public:                                         
    DriveModule m_frontLeftModule{FRONT_LEFT_SPEED_MOTOR_ID, FRONT_LEFT_DIRECTION_MOTOR_ID, FRONT_LEFT_DIRECTION_ENCODER_ID, FRONT_LEFT_MAG_OFFSET};
    DriveModule m_frontRightModule{FRONT_RIGHT_SPEED_MOTOR_ID, FRONT_RIGHT_DIRECTION_MOTOR_ID, FRONT_RIGHT_DIRECTION_ENCODER_ID, FRONT_RIGHT_MAG_OFFSET};
    DriveModule m_backLeftModule{BACK_LEFT_SPEED_MOTOR_ID, BACK_LEFT_DIRECTION_MOTOR_ID, BACK_LEFT_DIRECTION_ENCODER_ID, BACK_LEFT_MAG_OFFSET};
    DriveModule m_backRightModule{BACK_RIGHT_SPEED_MOTOR_ID, BACK_RIGHT_DIRECTION_MOTOR_ID, BACK_RIGHT_DIRECTION_ENCODER_ID, BACK_RIGHT_MAG_OFFSET};

};