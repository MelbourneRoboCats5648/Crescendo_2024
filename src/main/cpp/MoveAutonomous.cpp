#include "MoveAutonomous.h"
#include <frc/Timer.h>
#include "frc/DriverStation.h"
#include <iostream>

/**The Autonomous Timeline :)))))
 * Shooter wheels always running
 * at 3-5 seconds intake wheels spins
 * swerve moves from 5- 8 seconds
 * intake arm starts coming down from 6 - 8 seconds
 * intake sucks in note from 8-10 seconds
 * 10 - 12 seconds intake retracts arm
 * 10 - 13 seconds swerve goes back
**/

frc::Timer autoTimer{};


void AutoInit(DriveTrain& driveTrain)
//timer
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

    if(seconds<15_s&&seconds>0_s)
    {
        motorShooterLeft.Set(1.0);
        motorShooterRight.Set(-1.0*1.0);
    }
    else
    {
        motorShooterLeft.Set(0.0);
        motorShooterRight.Set(0.0);
    }
    
//intake wheels
    if(seconds<5_s&&seconds>3_s){
        motorIntakeWheel.Set(speakerIntakeWheelOutSpeed);
    }
    if(seconds<9_s && seconds<7_s){
        motorIntakeWheel.Set(intakeWheelInSpeed);
    }
    if(seconds<14_s && seconds<12_s){
        motorIntakeWheel.Set(speakerIntakeWheelOutSpeed);
    }
    else{
        motorIntakeWheel.Set(0);
    }

//swerve drive
    double position = driveTrain.GetPositionDistance();
    if( seconds>5_s && seconds<8_s)
    {        
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

    }

//Intake arm extending/retracting
    if (seconds>6_s && seconds<7_s){
        motorIntakeArm.Set(intakeArmExtendSpeed);
    }

    if (seconds>9_s && seconds<10_s){
        motorIntakeArm.Set(intakeArmRetractSpeed);
    }
    else {
        motorIntakeArm.Set(0);
    }

    //swerve drive
    if( seconds>9_s && seconds<12_s)
    {        
            std::cout << "DRIVING "<< std::endl;
        if(position<-1.130)
        {
            driveTrain.SetAllModules(frc::ChassisSpeeds{0.0_mps, 0.0_mps, units::radians_per_second_t(0)});
            std::cout << "STOP POSITION REACHED"<< std::endl;
        }
        if(seconds>9_s && position>-1.130)
        {
            driveTrain.SetAllModules(-speeds);
            std::cout << "driveTrainPosition " << position << std::endl;
        }
    }
    
    //} else {
       // driveTrain.StopAllModules();        
        //    std::cout << "STOP "<< std::endl;
    //}
    
   
}


    
   



