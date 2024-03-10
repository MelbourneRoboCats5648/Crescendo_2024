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

    double position = driveTrain.GetPositionDistance();
    if( seconds>5_s && seconds<8_s){        
            std::cout << "DRIVING "<< std::endl;
        if(position>1.130)
        {
            driveTrain.SetAllModules(frc::ChassisSpeeds{0.0_mps, 0.0_mps, units::radians_per_second_t(0)});
            std::cout << "STOP POSITION REACHED"<< std::endl;
        }
        if(seconds>5_s && position<1.130)
        {
            driveTrain.SetAllModules(speeds);
            std::cout << "driveTrainPosition " << position << std::endl;
        }
    } else {
        driveTrain.StopAllModules();        
            std::cout << "STOP "<< std::endl;
    }
    
   
}


