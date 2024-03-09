#pragma once

#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/CANcoder.hpp>
#include <ctre/phoenix6/core/CoreCANcoder.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>
#include <ctre/phoenix6/signals/SpnEnums.hpp>
#include <units/angle.h>

#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/controller/ProfiledPIDController.h>

using namespace ctre::phoenix6::hardware;

//Module constants defining
 static constexpr auto kModuleMaxAngularVelocity =
      std::numbers::pi * 1_rad_per_s;  // radians per second

 static constexpr auto kModuleMaxAngularAcceleration =
    std::numbers::pi * 2_rad_per_s / 1_s;  // radians per second^2

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

const double FRONT_LEFT_MAG_OFFSET = 0.4599609375;
const double FRONT_RIGHT_MAG_OFFSET = 0.41162109375;
const double BACK_LEFT_MAG_OFFSET = 0.389404296875;
const double BACK_RIGHT_MAG_OFFSET = 0.192138671875; // this mag offset has been set by the phoenix tuner set the new offsets
// set the offsets by using pheonix tuner
class DriveModule{
public:
    DriveModule(int speedMotorID, int directionMotorID, int directionEncoderID, double magOffset) :
        m_speedMotor(speedMotorID, "rio"),
        m_directionMotor(directionMotorID, "rio"),
        m_directionEncoder(directionEncoderID, "rio"),
        m_magOffset(magOffset),
        m_turningPIDController{
           3,
           0.05,
           0.0,
          {kModuleMaxAngularVelocity, kModuleMaxAngularAcceleration}}
{
    }

    // Ki is enough
    // sets the drive of all motors to zero    
    void Stop();
    void Initialise();
    void SetModule(frc::SwerveModuleState state);
    double GetModulePositionDistance();
    void SetModulePositionToZeroDistance();

public:
    TalonFX m_speedMotor;
    TalonFX m_directionMotor;
    CANcoder m_directionEncoder;
    double m_magOffset;
    frc::ProfiledPIDController<units::radians> m_turningPIDController;
    //const units::meter_t WHEEL_RADIUS = 0.0508_m;
    // CIRCUMFERECNE calc here
     private:
  // Mechanical Constants
  static constexpr double TURNING_GEAR_RATIO = 150.0 / 7.0;
  static constexpr double DRIVE_GEAR_RATIO = 6.75;  // L2 - Fast kit check the gear ratio
  static constexpr units::meter_t WHEEL_RADIUS = 0.0508_m;
  static constexpr units::meter_t WHEEL_CIRCUMFERENCE = 2 * std::numbers::pi * WHEEL_RADIUS;
};



