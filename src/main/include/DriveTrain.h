#pragma once

#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/CANcoder.hpp>
#include <units/angle.h>

#include <frc/kinematics/SwerveDriveKinematics.h>
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

const double FRONT_LEFT_MAG_OFFSET = 0.2939453125;
const double FRONT_RIGHT_MAG_OFFSET = 0.346435546875;
const double BACK_LEFT_MAG_OFFSET = 0.06201171875;
const double BACK_RIGHT_MAG_OFFSET = 0.012451171875; // this mag offset has been set by the phoenix tuner set the new offsets
// set the offsets by using pheonix tuner

class DriveTrain{
public:
    void SetAllModules(frc::ChassisSpeeds chasisSpeed);
    void StopAllModules();
    void InitialiseAllModules();
    double GetPositionDistance();
    void SetPositionToZeroDistance();


public:                                         
    DriveModule m_frontLeftModule{FRONT_LEFT_SPEED_MOTOR_ID, FRONT_LEFT_DIRECTION_MOTOR_ID, FRONT_LEFT_DIRECTION_ENCODER_ID, FRONT_LEFT_MAG_OFFSET, "Front Left"};
    DriveModule m_frontRightModule{FRONT_RIGHT_SPEED_MOTOR_ID, FRONT_RIGHT_DIRECTION_MOTOR_ID, FRONT_RIGHT_DIRECTION_ENCODER_ID, FRONT_RIGHT_MAG_OFFSET, "Front Right"};
    DriveModule m_backLeftModule{BACK_LEFT_SPEED_MOTOR_ID, BACK_LEFT_DIRECTION_MOTOR_ID, BACK_LEFT_DIRECTION_ENCODER_ID, BACK_LEFT_MAG_OFFSET, "Back Left"};
    DriveModule m_backRightModule{BACK_RIGHT_SPEED_MOTOR_ID, BACK_RIGHT_DIRECTION_MOTOR_ID, BACK_RIGHT_DIRECTION_ENCODER_ID, BACK_RIGHT_MAG_OFFSET, "Back Right"};

};