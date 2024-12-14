#pragma once

#include "DriveTrain.h"
#include "ShootAndIntake.h"
#include "DriveModule.h"

#include <frc/kinematics/SwerveDriveKinematics.h> //TODO - check if in drivetrain.h + can be removed
#include <frc/kinematics/SwerveModuleState.h>
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/CANcoder.hpp>
#include <units/angular_velocity.h>
#include <frc/ADIS16470_IMU.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/kinematics/ChassisSpeeds.h>

class NewAuto {
    private:
        enum State
        {
            DoNothing,
            MoveForward,
            RunShooter,
            MoveBackward,
            Finished
        };
        State m_state = DoNothing;
        frc::Timer m_AutoTimer = frc::Timer();
        void ResetTimer();
    
    public:
        void AutoInit(DriveTrain& driveTrain);
        void AutoYay(DriveTrain& driveTrain, ShootAndIntake& ShootAndIntake);
};