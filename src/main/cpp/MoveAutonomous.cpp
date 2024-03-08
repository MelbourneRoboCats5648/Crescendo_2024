#include "MoveAutonomous.h"
#include <frc/Timer.h>
#include "frc/DriverStation.h"

frc::Timer autoTimer{};

void AutoInit(DriveModule& driveModule)
{
    autoTimer.Start();
    frc::DriverStation::GetAlliance();
    driveModule.Initialise();
}

// Do our autonomous, called from AutoPeriodic
void AutoYay(
    frc::VictorSP motorShooterLeft,
    frc::VictorSP motorShooterRight,
    frc::VictorSP motorIntakeWheel,
    DriveTrain& drivetrain,
    DriveModule& drivemodule)
{
    frc::ChassisSpeeds speeds{3.0_mps, -2.0_mps,
     units::radians_per_second_t(0)};
     
    auto seconds = autoTimer.Get();
    // shooter always on
    motorShooterLeft.Set(speakerShooterSpeed);
    motorShooterRight.Set(-1.0*speakerShooterSpeed);
    
    if(seconds<5_s&&seconds>3_s)
    {
        motorIntakeWheel.Set(speakerIntakeWheelOutSpeed);
    }
    if(seconds>5_s)
    {
        motorIntakeWheel.Set(0);
        drivetrain.SetAllModules(speeds);
    }
}


