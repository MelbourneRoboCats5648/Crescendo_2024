#include "Swerve.h"
#include <units/angular_velocity.h>

   // Locations for the swerve drive modules relative to the robot center.
   //THESE NEED TO BE FIXED!!!!
    frc::Translation2d m_frontLeftLocation{0.381_m, 0.381_m};
    frc::Translation2d m_frontRightLocation{0.381_m, -0.381_m};
    frc::Translation2d m_backLeftLocation{-0.381_m, 0.381_m};
    frc::Translation2d m_backRightLocation{-0.381_m, -0.381_m};

const units::revolutions_per_minute_t falcon500RPM{6380};
const units::length::meter_t wheelCircumference{0.32};

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

void Swerve::kinematicsObject(){  
    // Creating my kinematics object using the module locations.
    frc::SwerveDriveKinematics<4> m_kinematics{
    m_frontLeftLocation, m_frontRightLocation, m_backLeftLocation,
    m_backRightLocation};
}



