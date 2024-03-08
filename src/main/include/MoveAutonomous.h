#pragma once
#include "DriveTrain.h"
#include "Intake.h"
#include "Shooter.h"
#include "DriveModule.h"
#include <frc/motorcontrol/VictorSP.h>

#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/kinematics/SwerveModuleState.h>
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/CANcoder.hpp>
#include <units/angular_velocity.h>
#include <frc/ADIS16470_IMU.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/kinematics/ChassisSpeeds.h>


void AutoInit(DriveModule& driveModule);
void AutoYay(
    frc::VictorSP motorShooterLeft,
    frc::VictorSP motorShooterRight,
    frc::VictorSP motorIntakeWheel,
    DriveTrain& drivetrain,
    DriveModule& drivemodule);

