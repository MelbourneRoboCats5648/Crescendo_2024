#pragma once
#include "DriveTrain.h"
#include "ShootAndIntake.h"



void IntakingButton(ShootAndIntake& shootAndIntake, 
                    DriveTrain& driveTrain,
                    units::meters_per_second_t desiredSpeed);
