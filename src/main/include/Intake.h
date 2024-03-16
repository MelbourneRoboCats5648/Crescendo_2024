
#pragma once

#include <frc/XboxController.h>
#include <frc/motorcontrol/VictorSP.h>

const double intakeArmRetractSpeed = 0.4;
const double intakeArmExtendSpeed = -0.4;

const double intakeWheelInSpeed = 0.4;
const double ampIntakeWheelOutSpeed = -1.0;
const double speakerIntakeWheelOutSpeed = -1.0;




/** Intake encoder
const int aChannel = 0; 
const int bChannel = 1; 
*/

void Intake(frc::XboxController& xbox, frc::VictorSP& motorIntakeArm, frc::VictorSP& motorIntakeWheel);


