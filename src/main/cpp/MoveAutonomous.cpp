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
void AutoYay(DriveTrain& driveTrain,
            frc::VictorSP& motorShooterLeft, 
            frc::VictorSP& motorShooterRight,
            frc::VictorSP& motorIntakeArm, 
            frc::VictorSP& motorIntakeWheel)
{
    frc::ChassisSpeeds speeds{3.0_mps, 0.0_mps,
     units::radians_per_second_t(0)};

    auto seconds = autoTimer.Get();
    // shooter always on
    motorShooterLeft.Set(.3);
    motorShooterRight.Set(-1.0*.3);
    driveTrain.SetPositionToZeroDistance();
    
    if(seconds<5_s&&seconds>3_s)
    {
        motorIntakeWheel.Set(-.3);
    }
    else{
        motorIntakeWheel.Set(0);
    }
    /*if(seconds>5_s)
    {
        motorIntakeWheel.Set(0);
        driveTrain.SetAllModules(speeds);
    }
    if(driveTrain.GetPositionDistance()==113.0)
    {
        driveTrain.StopAllModules();
    }
    if(seconds==6_s)
    {
        motorShooterLeft.Set(0);
        motorShooterRight.Set(0);
        //driveTrain.StopAllModules();
    }*/
   
}


