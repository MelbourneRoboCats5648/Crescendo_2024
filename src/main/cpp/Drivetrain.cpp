#include "DriveTrain.h"

//speed motors
ctre::phoenix6::hardware::TalonFX frontLeftSpeedMotor(1,"rio");
ctre::phoenix6::hardware::TalonFX frontRightSpeedMotor(2,"rio");
ctre::phoenix6::hardware::TalonFX backLeftSpeedMotor(3,"rio");
ctre::phoenix6::hardware::TalonFX backRightSpeedMotor(4,"rio");

//direction motors
ctre::phoenix6::hardware::TalonFX frontLeftDirectionMotor(5,"rio");
ctre::phoenix6::hardware::TalonFX frontRightDirectionMotor(6,"rio");
ctre::phoenix6::hardware::TalonFX backLeftDirectionMotor(7,"rio");
ctre::phoenix6::hardware::TalonFX backRightDirectionMotor(8,"rio");

//direction encoders
ctre::phoenix6::hardware::CANcoder frontLeftDirectionEncoder(9,"rio");
ctre::phoenix6::hardware::CANcoder frontRightDirectionEncoder(10,"rio");
ctre::phoenix6::hardware::CANcoder backLeftDirectionEncoder(11,"rio");
ctre::phoenix6::hardware::CANcoder backRightDirectionEncoder(12,"rio");

//Encoder Counts Per RV
const int countsPerRevolution = 4096;


/*
 * tell motors how to move
 * get motor angle and speed from module state info
 * move each motor
 * 
 * 1
*/


void setModule(frc::SwerveModuleState state, ctre::phoenix6::hardware::TalonFX& driveMotor, ctre::phoenix6::hardware::TalonFX& directionMotor) {
//setting direction motors

// Setting Motor Speed
const units::meters_per_second_t MAX_SPEED_MPS = 32.203_mps;

double normalisedSpeed = (double)state.speed / (double)MAX_SPEED_MPS;

driveMotor.Set(normalisedSpeed);


//Setting Motor Direction

// Find out current angle of direction motor from encoder
// FInd out which direction to rotate direction motor
// Drive the angle motor
// Find out when to stop (maybe need to check if you are ate the required angle)


};

