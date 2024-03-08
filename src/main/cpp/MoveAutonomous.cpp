#include "MoveAutonomous.h"
#include <frc/Timer.h>
#include "frc/DriverStation.h"

frc::Timer autoTimer{};

void AutoInit()
{
    autoTimer.Start();
    frc::DriverStation::GetAlliance();
}

// Do our autonomous, called from AutoPeriodic
void AutoYay(
    frc::VictorSP motorShooterLeft,
    frc::VictorSP motorShooterRight,
    frc::VictorSP motorIntakeWheel)
{
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
    }
}


