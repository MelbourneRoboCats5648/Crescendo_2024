#include "IntakingButton.h"
#include <frc/filter/SlewRateLimiter.h>

// limit rate to 2mps per second
static frc::SlewRateLimiter<units::meters_per_second> speedLimiter{2_mps / 1_s};

void IntakingButton(ShootAndIntake& shootAndIntake, 
                    DriveTrain& driveTrain,
                    units::meters_per_second_t desiredSpeed)
{
    frc::ChassisSpeeds speeds{speedLimiter.Calculate(desiredSpeed), 0.0_mps, units::radians_per_second_t(0)};

    shootAndIntake.m_intake.motorIntakeWheel.Set(intakeWheelInSpeed);
    driveTrain.SetAllModules(speeds);
} 