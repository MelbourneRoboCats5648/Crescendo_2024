#include "IntakingButton.h"



void IntakingButton(ShootAndIntake& shootAndIntake, 
                    DriveTrain& driveTrain)
{
    frc::ChassisSpeeds speeds{1.0_mps, 0.0_mps, units::radians_per_second_t(0)};
    shootAndIntake.m_intake.motorIntakeWheel.Set(intakeWheelInSpeed);
    driveTrain.SetAllModules(speeds);
}