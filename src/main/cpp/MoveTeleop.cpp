#include "MoveTeleop.h"
#include <iostream>
#include <frc/filter/SlewRateLimiter.h>


//const double falcon500RPM{6380};
//const units::length::meter_t wheelCircumference{0.32};
//const double L1GearRatio(8.41/1);
//const double L2GearRatio(6.75/1);
//const double L3GearRatio(6.12/1);
//const units::meters_per_second_t maxVelocity{((falcon500RPM/L1GearRatio)/60_s) * wheelCircumference}; // fixme - Limit this to half??
const double chosenMaxVelocity{8.0};
const double chosenRotationSpeed{M_PI*2};

 //for smoother ride
static frc::SlewRateLimiter<units::scalar> xLimiter{2 / 1_s};
static frc::SlewRateLimiter<units::scalar> yLimiter{2 / 1_s};
static frc::SlewRateLimiter<units::scalar> rotLimiter{2 / 1_s};

//const double deadband = 0.08;
       // return frc::ChassisSpeeds{
         //   -xLimiter.Calculate(frc::ApplyDeadband(controller.GetLeftY(), deadband)) * chosenMaxVelocity,
           // -yLimiter.Calculate(frc::ApplyDeadband(controller.GetLeftX(), deadband)) * chosenMaxVelocity,
            //-rotLimiter.Calculate(frc::ApplyDeadband(controller.GetRightX(), deadband)) *
                //chosenRotationSpeed};//
 


// 1) Move according to joystick input - joystick
// 2) Translate movement into field oriented drive for each module - gyro angle and the physical dimensions of the robot
// 3) Each module needs to move according to the speed and angle calculated - module motors and the current angle of the wheel

void MoveTeleop(DriveTrain& driveTrain, frc::Joystick& joystick, frc::ADIS16470_IMU& gyro){

    // will need to actually convert the double output from joystick to a meters per sec velocity later
    //double xSpeed = (-1.0*DeadBand(joystick.GetX(),0.1) * chosenMaxVelocity);
    //double ySpeed = (-1.0*DeadBand(joystick.GetY(),0.1) * chosenMaxVelocity); // consider inverting
    //assuming joystick twist is one to negative one

    //* will need to actually convert the double output from joystick to a meters per sec velocity later
    double xSpeed = xLimiter.Calculate(-1.0*DeadBand(joystick.GetX(),0.1) * chosenMaxVelocity);
    double ySpeed = yLimiter.Calculate(-1.0*DeadBand(joystick.GetY(),0.1) * chosenMaxVelocity); // consider inverting
    //assuming joystick twist is one to negative one*/

    //double rotationSpeed = (-1.0*DeadBand(joystick.GetTwist(), 0.5) * chosenRotationSpeed);
    double rotationSpeed = rotLimiter.Calculate(-1.0*DeadBand(joystick.GetTwist(), 0.1) * chosenRotationSpeed);
    
    std::cout << "xSpeed " << xSpeed << " ySpeed " << ySpeed << " rotation Speed " << rotationSpeed << std::endl;

    // May need to limit acceleration with something like this https://github.com/Liam-Stow/flex-commandsInSubsystems/blob/e150c482f54ff3f080e057e53795809a7af17466/src/main/cpp/subsystems/DriveBase.cpp#L108
    // (if its hard to drive)

    // measured robot angle - TODO reenable
    units::angle::degree_t robotAngle = gyro.GetAngle();

    //getting the chassis speed based on the field centric speeds
    frc::ChassisSpeeds chassisSpeed = frc::ChassisSpeeds::FromFieldRelativeSpeeds(
            units::meters_per_second_t{ySpeed}, 
            units::meters_per_second_t{xSpeed}, 
            units::radians_per_second_t{rotationSpeed}, 
            frc::Rotation2d{robotAngle});

 /*frc::ChassisSpeeds chassisSpeed(
        units::meters_per_second_t{ySpeed}, 
        units::meters_per_second_t{xSpeed}, 
        units::radians_per_second_t{rotationSpeed});
*/
    // command the drive train to move based on the the required field oriented speed
    driveTrain.SetAllModules(chassisSpeed);
}

double DeadBand(double joystickValue, double deadbandRange)
{
    if (abs(joystickValue) <= deadbandRange)
    {
        return 0;
    }
    return joystickValue;
}
