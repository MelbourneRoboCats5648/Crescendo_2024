#include "MoveTeleop.h"

DriveTrain driveTrain;

//gyro
frc::ADIS16470_IMU gyro{};

const double falcon500RPM{6380};
const units::length::meter_t wheelCircumference{0.32};
const double L1GearRatio(8.41/1);
const double L2GearRatio(6.75/1);
const double L3GearRatio(612/1);
const units::meters_per_second_t maxVelocity{((falcon500RPM/L1GearRatio)/60_s)*wheelCircumference}; //Limit this to half??
const units::meters_per_second_t chosenMaxVelocity{5.0};
const units::radians_per_second_t chosenRotationSpeed{M_PI*2};  


// 1) Move according to joystick input - joystick
// 2) Translate movement into field oriented drive for each module - gyro angle and the physical dimensions of the robot
// 3) Each module needs to move according to the speed and angle calculated - module motors and the current angle of the wheel

void MoveTeleop::moveTeleop(frc::Joystick& joystick){

    // will need to actually convert the double output from joystick to a meters per sec velocity later
    // TODO CONVERT to speeds

    units::meters_per_second_t xSpeed = (joystick.GetX()*units::velocity::meters_per_second_t{chosenMaxVelocity});
    units::meters_per_second_t ySpeed = (joystick.GetY()*units::velocity::meters_per_second_t{chosenMaxVelocity});
    //assuming joystick twist is one to negative one
    units::radians_per_second_t rotationSpeed = (joystick.GetTwist()*units::angular_velocity::radians_per_second_t{chosenRotationSpeed});
    units::angle::degree_t robotAngle = gyro.GetAngle();

    // The robot is moving at however speed the joystick tells it. 
    //getting the field centric speeds
    frc::ChassisSpeeds fieldSpeeds = frc::ChassisSpeeds::FromFieldRelativeSpeeds(
    xSpeed, ySpeed, rotationSpeed, frc::Rotation2d{robotAngle});

    //need to convert speed into 4 swerve module states for each of the swerve modules (using kinemetaic stuff)
    //include swerve class inside robot class

    driveTrain.SetAllModules(fieldSpeeds);
}

void MoveTeleop::CalibrateGyro()
{
    gyro.Calibrate();
}

