
#pragma once

#include <frc/XboxController.h>

const double intakeArmRetractSpeed = 0.4;
const double intakeArmExtendSpeed = -0.4;

const double intakeWheelInSpeed = 0.6;
const double ampIntakeWheelOutSpeed = -0.6;
const double speakerIntakeWheelOutSpeed = -1.0;


//PWM Ports
const int motorIntakeArmPort = 2;
const int motorIntakeWheelPort = 3;

/** Intake encoder
const int aChannel = 0; 
const int bChannel = 1; 
*/

void Intake(frc::XboxController& xbox);


