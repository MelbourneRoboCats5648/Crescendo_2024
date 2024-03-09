#include "MoveAutonomous.h"
#include <frc/Timer.h>
#include "frc/DriverStation.h"

frc::Timer autoTimer{};

frc::VictorSP motorIntakeArmAuto{motorIntakeArmPort};
frc::VictorSP motorIntakeWheelAuto{motorIntakeWheelPort};

frc::VictorSP motorShooterLeftAuto{motorShooterLeftPort};
frc::VictorSP motorShooterRightAuto{motorShooterRightPort};

void AutoInit()
{
    autoTimer.Start();
    frc::DriverStation::GetAlliance();
}

// Do our autonomous, called from AutoPeriodic
void AutoYay(DriveTrain& driveTrain)
{
    frc::ChassisSpeeds speeds{3.0_mps, 0.0_mps,
     units::radians_per_second_t(0)};

    auto seconds = autoTimer.Get();
    // shooter always on
    motorShooterLeftAuto.Set(speakerShooterSpeed);
    motorShooterRightAuto.Set(-1.0*speakerShooterSpeed);
    driveTrain.SetPositionToZeroDistance();
    
    if(seconds<5_s&&seconds>3_s)
    {
        motorIntakeWheelAuto.Set(speakerIntakeWheelOutSpeed);
    }
    if(seconds>5_s)
    {
        motorIntakeWheelAuto.Set(0);
        driveTrain.SetAllModules(speeds);
    }
    if(driveTrain.GetPositionDistance()==113.0)
    {
        driveTrain.StopAllModules();
    }
    if(seconds==6_s)
    {
        motorShooterLeftAuto.Set(0);
        motorShooterRightAuto.Set(0);
        //driveTrain.StopAllModules();
    }
   
}


