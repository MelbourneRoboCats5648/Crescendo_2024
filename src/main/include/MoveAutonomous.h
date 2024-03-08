#pragma once
#include "DriveTrain.h"
#include "Intake.h"
#include "Shooter.h"
#include <frc/motorcontrol/VictorSP.h>


void AutoInit();
void AutoYay(
    frc::VictorSP motorShooterLeft,
    frc::VictorSP motorShooterRight,
    frc::VictorSP motorIntakeWheel);

