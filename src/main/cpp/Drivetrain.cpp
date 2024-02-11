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