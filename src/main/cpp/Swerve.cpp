#include "Swerve.h"

void Swerve::manualChassisSpeed(frc::Joystick& joystick){

    // will need to actually convert the double output from joystick to a meters per sec velocity later
    units::meters_per_second_t xSpeed = (units::velocity::meters_per_second_t)(joystick.GetX());
    units::meters_per_second_t ySpeed = (units::velocity::meters_per_second_t)(joystick.GetY());
    double rotationSpeed = joystick.GetTwist();

    // The robot is moving at however speed the joystick tells it.  
    frc::ChassisSpeeds speeds{xSpeed, ySpeed, units::radians_per_second_t(rotationSpeed)};

    //need to convert speed into 4 swerve module states for each of the swerve modules (using kinemetaic stuff)
    //include swerve class inside robot class
    
}



