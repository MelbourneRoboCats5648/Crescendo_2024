#include "DriveTrain.h"

//Encoder Counts Per RV
const int countsPerRevolution = 4096;


/*
 * tell motors how to move
 * get motor angle and speed from module state info
 * move each motor
*/


void SetModule(frc::SwerveModuleState state, ctre::phoenix6::hardware::TalonFX& driveMotor, ctre::phoenix6::hardware::TalonFX& directionMotor, ctre::phoenix6::hardware::CANcoder& encoder) {
//reference state


// Setting Motor Speed
const units::meters_per_second_t MAX_SPEED_MPS = 32.203_mps;

double normalisedSpeed = (double)state.speed / (double)MAX_SPEED_MPS;

driveMotor.Set(normalisedSpeed);

//TODO check encoder range
double encoderCurrentState = encoder.GetAbsolutePosition().GetValueAsDouble();
units::angle::radian_t encoderRotation = units::angle::radian_t{encoderCurrentState/(2* M_PI)};


//optimise
frc::SwerveModuleState::Optimize(state, encoderRotation);

//Module constants defining
 static constexpr auto kModuleMaxAngularVelocity =
      std::numbers::pi * 1_rad_per_s;  // radians per second
 static constexpr auto kModuleMaxAngularAcceleration =
    std::numbers::pi * 2_rad_per_s / 1_s;  // radians per second^2

//define PID
 frc::ProfiledPIDController<units::radians> m_turningPIDController{
      1.0,
      0.0,
      0.0,
      {kModuleMaxAngularVelocity, kModuleMaxAngularAcceleration}};


// Calculate the turning motor output from the turning PID controller.
  const auto turnOutput = m_turningPIDController.Calculate(
    {encoderRotation}, state.angle.Radians());



// Set the motor outputs for the turning of the wheels
directionMotor.SetVoltage(units::volt_t{turnOutput}); //+ drFeedforward);



};

// Find out current angle of direction motor from encoder
// Find out which direction to rotate direction motor
// Drive the angle motor
// Find out when to stop (maybe need to check if you are ate the required angle)

