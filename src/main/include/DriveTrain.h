#pragma once

#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/CANcoder.hpp>
#include <units/angle.h>

#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/controller/ProfiledPIDController.h>

#include "DriveModule.h"


class DriveTrain{
public:
    void SetAllModules(frc::ChassisSpeeds chasisSpeed, DriveModule& driveModule);
    void StopAllModules(DriveModule& driveModule);
    void InitialiseAllModules(DriveModule& driveModule);
    void SetAllModulesZero(DriveModule& driveModule);
};