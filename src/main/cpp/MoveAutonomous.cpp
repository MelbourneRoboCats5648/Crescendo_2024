#include "MoveAutonomous.h"
#include <frc/Timer.h>
#include "frc/DriverStation.h"
#include <iostream>

frc::Timer autoTimer{};

void AutoInit(DriveTrain& driveTrain)
{
    autoTimer.Start();
    frc::DriverStation::GetAlliance();    
    driveTrain.SetPositionToZeroDistance();
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

    if(seconds<9_s&&seconds>0_s)
    {
        motorShooterLeft.Set(1.0);
        motorShooterRight.Set(-1.0*1.0);
    }
    else
    {
        motorShooterLeft.Set(0.0);
        motorShooterRight.Set(0.0);
    }
    
    
    if(seconds<5_s&&seconds>3_s)
    {
        motorIntakeWheel.Set(speakerIntakeWheelOutSpeed);
    }
    else{
        motorIntakeWheel.Set(0);
    }
    if(driveTrain.GetPositionDistance()>1.130)
    {
       driveTrain.StopAllModules();
    }
    else if(seconds>5_s)
    {
       driveTrain.SetAllModules(speeds);
       std::cout << "driveTrainPosition " << driveTrain.GetPositionDistance() << std::endl;
    }
    
   
}


