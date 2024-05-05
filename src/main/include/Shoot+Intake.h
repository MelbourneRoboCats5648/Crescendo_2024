#pragma once

#include <frc/XboxController.h>
#include <frc/motorcontrol/VictorSP.h>

const double speakerShooterSpeed = 1.0;
const double ampShooterSpeed = 0.5;

const double intakeWheelInSpeed = 0.4;
const double ampIntakeWheelOutSpeed = -1.0;
const double speakerIntakeWheelOutSpeed = -1.0;

void ShootAndIntake(frc::XboxController& xbox, 
            frc::VictorSP& motorIntakeArm, 
            frc::VictorSP& motorIntakeWheel, 
            frc::VictorSP& motorShooterLeft,
            frc::VictorSP& motorShooterRight);
