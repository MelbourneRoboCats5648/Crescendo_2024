#include "MoveAutonomous.h"
#include <frc/Timer.h>
#include "frc/DriverStation.h"
#include <iostream>
#include "IntakingButton.h"
#include <frc/filter/SlewRateLimiter.h>

 #include "frc/geometry/Rotation2d.h"

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
frc::Timer autoShooterTimer{};

const auto TOL = 20_ms;
const auto SHOOT_TIME_1 = 3_s; //we shoot at 1 second
const auto DRIVE_TIME_START_1 = 2_s; //drive forward at 2 seconds
const auto ARM_OUT_START = 2_s;//arm extends alongside drive at 2 seconds
const auto COLLECT_TIME_START = 2.5_s;//wheels start spinning at 2.5

const auto DRIVE_TIME_END_1 = 4_s;
const auto ARM_OUT_TIME_END = 3_s;

const auto COLLECT_TIME_END = 5_s; //collecting finishes
const auto ARM_IN_TIME_START = 5_s; //start moving backwards
const auto DRIVE_TIME_START_2 = 5_s;
const auto ARM_IN_TIME_END = 6.5_s;
const auto DRIVE_TIME_END_2 = 6_s;

const auto SHOOT_TIME_2 = 7_s; //shoot
const auto DRIVE_TIME_START_3 = 13_s;
const auto DRIVE_TIME_END_3 = 14.5_s;

static frc::SlewRateLimiter<units::meters_per_second> autoSpeedLimiter{2_mps / 1_s};


void AutoInit(DriveTrain& driveTrain)
//timer
{
    autoTimer.Reset();
    autoTimer.Start();
    frc::DriverStation::GetAlliance();
    driveTrain.SetPositionToZeroDistance();
    driveTrain.m_gyro.Reset();
}
 

// Do our autonomous, called from AutoPeriodic
void AutoYay(DriveTrain& driveTrain, ShootAndIntake& shootAndIntake)
{
    //frc::ChassisSpeeds speeds{3.0_mps, 0.0_mps, units::radians_per_second_t(0)};

    auto seconds = autoTimer.Get();

    units::angle::degree_t robotAngle = driveTrain.m_gyro.GetAngle();

    units::meters_per_second_t desiredSpeed = autoSpeedLimiter.Calculate(1.0_mps);


    if( (seconds > SHOOT_TIME_1) && (seconds < SHOOT_TIME_1 + TOL))
    {
        autoShooterTimer.Reset();
        autoShooterTimer.Start();
    }
    else if ( (seconds > SHOOT_TIME_2) && (seconds < SHOOT_TIME_2 + TOL))
    {
        autoShooterTimer.Reset();
        autoShooterTimer.Start();
    }
    shootAndIntake.ShootAndIntakeFunctions(autoShooterTimer);

/*//intake wheels
    if(seconds>COLLECT_TIME_START && seconds<COLLECT_TIME_END)
    {
        shootAndIntake.m_intake.motorIntakeWheel.Set(intakeWheelInSpeed);
    }
    else if (seconds>(SHOOT_TIME_2 + TOL) && seconds < (SHOOT_TIME_2 + 2*TOL))
    {
        shootAndIntake.m_intake.motorIntakeWheel.Set(0); //CHECK idk if this might break the shoot thing
    }     


/Intake arm extending/retracting
    if(seconds>ARM_OUT_START && seconds<ARM_OUT_TIME_END)
    {
        shootAndIntake.m_intake.motorIntakeArm.Set(-0.3);
    }
    else if(seconds>ARM_IN_TIME_START && seconds<ARM_IN_TIME_END)
    {
        shootAndIntake.m_intake.motorIntakeArm.Set(0.3);
    }
    else 
    {
        shootAndIntake.m_intake.motorIntakeArm.Set(0);
    }

*/

//swerve drive
    //double position = driveTrain.GetPositionDistance();
    if(seconds>DRIVE_TIME_START_3 && seconds<DRIVE_TIME_END_3)
    {
       // IntakingButton(shootAndIntake, driveTrain, 0.7_mps);
        // limit rate to 2mps per second
       
        frc::ChassisSpeeds autoSpeed = frc::ChassisSpeeds::FromFieldRelativeSpeeds(
            units::meters_per_second_t{desiredSpeed}, 
            units::meters_per_second_t{0}, 
            units::radians_per_second_t{0}, 
            frc::Rotation2d{robotAngle});
    // command the drive train to move based on the the required field oriented speed
    driveTrain.SetAllModules(autoSpeed);
    }
/*
    else if(seconds>DRIVE_TIME_START_2 && seconds<DRIVE_TIME_END_2)
    {      
        
        frc::ChassisSpeeds autoSpeed = frc::ChassisSpeeds::FromFieldRelativeSpeeds(
            units::meters_per_second_t{-desiredSpeed}, 
            units::meters_per_second_t{0}, 
            units::radians_per_second_t{0}, 
            frc::Rotation2d{robotAngle});
    // command the drive train to move based on the the required field oriented speed
    driveTrain.SetAllModules(autoSpeed);
        
    }
    
    else if (seconds>DRIVE_TIME_START_3 && seconds<DRIVE_TIME_END_3)
    {
       
        frc::ChassisSpeeds autoSpeed = frc::ChassisSpeeds::FromFieldRelativeSpeeds(
            units::meters_per_second_t{desiredSpeed}, 
            units::meters_per_second_t{0}, 
            units::radians_per_second_t{0}, 
            frc::Rotation2d{robotAngle});
    // command the drive train to move based on the the required field oriented speed
    driveTrain.SetAllModules(autoSpeed);
    }
_*/
    else
    {
        driveTrain.StopAllModules();
        std::cout << "STOP "<< std::endl;
    }

}


    
   



