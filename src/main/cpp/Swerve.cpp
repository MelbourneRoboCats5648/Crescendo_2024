#include "Swerve.h"


TalonFX frontLeftSpeedMotor(1,"rio");
TalonFX frontRightSpeedMotor(2,"rio");
TalonFX backLeftSpeedMotor(3,"rio");
TalonFX backRightSpeedMotor(4,"rio");
TalonFX frontLeftDirectionMotor(5,"rio");
TalonFX frontRightDirectionMotor(6,"rio");
TalonFX backLeftDirectionMotor(7,"rio");
TalonFX backRightDirectionMotor(8,"rio");

//direction encoders
CANcoder frontLeftDirectionEncoder(9,"rio");
CANcoder frontRightDirectionEncoder(10,"rio");
CANcoder backLeftDirectionEncoder(11,"rio");
CANcoder backRightDirectionEncoder(12,"rio");

//gyro
frc::ADIS16470_IMU gyro{};

// Locations for the swerve drive modules relative to the robot center.
//THESE NEED TO BE FIXED!!!!
frc::Translation2d m_frontLeftLocation{0.260825_m, 0.260825_m};
frc::Translation2d m_frontRightLocation{0.259325_m, -260825_m};
frc::Translation2d m_backLeftLocation{-0.260825_m, 0.259825_m};
frc::Translation2d m_backRightLocation{-0.259325_m, -0.259825_m};
const frc::SwerveDriveKinematics<4> kinematics{
                                         m_frontLeftLocation, 
                                        m_frontRightLocation, 
                                        m_backLeftLocation,
                                        m_backRightLocation};

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

void Swerve::MoveTeleop(frc::Joystick& joystick){

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

    // Convert to module states. Here, we can use C++17's structured
    // bindings feature to automatically split up the array into its
    // individual SwerveModuleState components.
    auto [fl, fr, bl, br] = kinematics.ToSwerveModuleStates(fieldSpeeds);
    SetModule(fl, frontLeftSpeedMotor, frontLeftDirectionMotor, frontLeftDirectionEncoder);
    SetModule(fr, frontRightSpeedMotor, frontRightDirectionMotor, frontRightDirectionEncoder);
    SetModule(bl, backLeftSpeedMotor, backLeftDirectionMotor, backLeftDirectionEncoder);
    SetModule(br, backRightSpeedMotor, backRightDirectionMotor, backRightDirectionEncoder);
}


// 3) Each module needs to move according to the speed and angle calculated - module motors and the current angle of the wheel
void Swerve::SetModule(frc::SwerveModuleState state, TalonFX& driveMotor, TalonFX& angleMotor, CANcoder& angleEncoder)
{

}



