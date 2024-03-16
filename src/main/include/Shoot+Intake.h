#pragma once

#include <frc/XboxController.h>
#include <frc/motorcontrol/VictorSP.h>

void ShootAndIntake(frc::XboxController& xbox, 
            frc::VictorSP& motorIntakeArm, 
            frc::VictorSP& motorIntakeWhee, 
            frc::VictorSP& motorShooterLeft,
            frc::VictorSP& motorShooterRight);