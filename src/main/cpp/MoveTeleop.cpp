#include "MoveTeleop.h"
#include <iostream>


const double falcon500RPM{6380};
const units::length::meter_t wheelCircumference{0.32};
const double L1GearRatio(8.41/1);
const double L2GearRatio(6.75/1);
const double L3GearRatio(6.12/1);
const units::meters_per_second_t maxVelocity{((falcon500RPM/L1GearRatio)/60_s) * wheelCircumference}; // fixme - Limit this to half??
const double chosenMaxVelocity{5.0};
const double chosenRotationSpeed{M_PI*2};


// 1) Move according to joystick input - joystick
// 2) Translate movement into field oriented drive for each module - gyro angle and the physical dimensions of the robot
// 3) Each module needs to move according to the speed and angle calculated - module motors and the current angle of the wheel

void MoveTeleop(DriveTrain& driveTrain, frc::Joystick& joystick, frc::ADIS16470_IMU& gyro){

    // will need to actually convert the double output from joystick to a meters per sec velocity later
    double xSpeed = (DeadBand(joystick.GetX(),0.1) * chosenMaxVelocity);
    double ySpeed = (DeadBand(joystick.GetY(),0.1) * chosenMaxVelocity); // consider inverting
    //assuming joystick twist is one to negative one
    double rotationSpeed = (DeadBand(joystick.GetTwist(), 0.1) * chosenRotationSpeed);
    
    //std::cout << "xSpeed " << xSpeed << " ySpeed " << ySpeed << " rotation Speed " << rotationSpeed << "\n";
    std::cout << " rotation speed " << rotationSpeed << std::endl;

    // measured robot angle - TODO reenable
    //units::angle::degree_t robotAngle = gyro.GetAngle();

    //getting the chassis speed based on the field centric speeds
    /*frc::ChassisSpeeds chassisSpeed = frc::ChassisSpeeds::FromFieldRelativeSpeeds(
    xSpeed, ySpeed, rotationSpeed, frc::Rotation2d{robotAngle});*/

    frc::ChassisSpeeds chassisSpeed(units::meters_per_second_t{xSpeed}, units::meters_per_second_t{ySpeed}, units::radians_per_second_t{rotationSpeed});

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
