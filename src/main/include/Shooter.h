#pragma once

#include <frc/XboxController.h>
#include <frc/motorcontrol/VictorSP.h>


// Speeds
const double speakerShooterSpeed = 1.0;
const double ampShooterSpeed = 0.2;



void Shooter(frc::XboxController& xbox, frc::VictorSP& motorShooterLeft, frc::VictorSP& motorShooterRight);