#pragma once

#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/CANcoder.hpp>
#include <units/angle.h>

#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/controller/ProfiledPIDController.h>
#include <frc/motorcontrol/PWMSparkMax.h>



class DriveTrain{
public:
    void SetAllModules(frc::ChassisSpeeds state);
private:
    void SetModule(frc::SwerveModuleState state, ctre::phoenix6::hardware::TalonFX& driveMotor, ctre::phoenix6::hardware::TalonFX& directionMotor, ctre::phoenix6::hardware::CANcoder& encoder);

};
