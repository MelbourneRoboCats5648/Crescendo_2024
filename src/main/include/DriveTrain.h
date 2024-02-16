#pragma once

#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/CANcoder.hpp>
#include <units/angle.h>

#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/controller/ProfiledPIDController.h>
#include <frc/motorcontrol/PWMSparkMax.h>

//using namespace ctre::phoenix6::hardware;

void SetModule(frc::SwerveModuleState state, TalonFX& driveMotor, ctre::phoenix6::hardware::TalonFX& angleMotor, CANcoder& angleEncoder);



