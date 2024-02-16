#pragma once

#include <frc/kinematics/ChassisSpeeds.h>
#include <frc/Joystick.h>
#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/kinematics/SwerveModuleState.h>
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/CANcoder.hpp>
#include <units/angular_velocity.h>
#include <frc/ADIS16470_IMU.h>
#include <frc/geometry/Rotation2d.h>
#include <math.h>


using namespace ctre::phoenix6::hardware;

class Swerve {
public:
//calculates the chassis x and y speed and rotation speed based on joystick
    void MoveTeleop(frc::Joystick& joystick);
    void SetModule(frc::SwerveModuleState state, TalonFX& driveMotor, TalonFX& angleMotor, CANcoder& angleEncoder);
};