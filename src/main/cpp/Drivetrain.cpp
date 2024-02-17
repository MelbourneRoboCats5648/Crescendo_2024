#include "DriveTrain.h"

//Encoder Counts Per RV
const int countsPerRevolution = 4096;

using namespace ctre::phoenix6::hardware;

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

// Locations for the swerve drive modules relative to the robot center.
frc::Translation2d m_frontLeftLocation{0.260825_m, 0.260825_m};
frc::Translation2d m_frontRightLocation{0.259325_m, -260825_m};
frc::Translation2d m_backLeftLocation{-0.260825_m, 0.259825_m};
frc::Translation2d m_backRightLocation{-0.259325_m, -0.259825_m};
const frc::SwerveDriveKinematics<4> kinematics{
                                        m_frontLeftLocation, 
                                        m_frontRightLocation, 
                                        m_backLeftLocation,
                                        m_backRightLocation};

void DriveTrain::SetAllModules(frc::ChassisSpeeds fieldSpeeds){
     
    // Convert to module states. Here, we can use C++17's structured
    // bindings feature to automatically split up the array into its
    // individual SwerveModuleState components.
    auto [fl, fr, bl, br] = kinematics.ToSwerveModuleStates(fieldSpeeds);
    SetModule(fl, frontLeftSpeedMotor, frontLeftDirectionMotor, frontLeftDirectionEncoder);
    SetModule(fr, frontRightSpeedMotor, frontRightDirectionMotor, frontRightDirectionEncoder);
    SetModule(bl, backLeftSpeedMotor, backLeftDirectionMotor, backLeftDirectionEncoder);
    SetModule(br, backRightSpeedMotor, backRightDirectionMotor, backRightDirectionEncoder);
}

/*
 * tell motors how to move
 * get motor angle and speed from module state info
 * move each motor
*/
void DriveTrain::SetModule(frc::SwerveModuleState state, ctre::phoenix6::hardware::TalonFX& driveMotor, ctre::phoenix6::hardware::TalonFX& directionMotor, ctre::phoenix6::hardware::CANcoder& encoder) {
//reference state


// Setting Motor Speed
const units::meters_per_second_t MAX_SPEED_MPS = 32.203_mps;

double normalisedSpeed = (double)state.speed / (double)MAX_SPEED_MPS;

driveMotor.Set(normalisedSpeed);

//TODO check encoder range
double encoderCurrentState = encoder.GetAbsolutePosition().GetValueAsDouble();
units::angle::radian_t encoderRotation = units::angle::radian_t{encoderCurrentState/(2* M_PI)};


//optimise
frc::SwerveModuleState::Optimize(state, encoderRotation);

//Module constants defining
 static constexpr auto kModuleMaxAngularVelocity =
      std::numbers::pi * 1_rad_per_s;  // radians per second
 static constexpr auto kModuleMaxAngularAcceleration =
    std::numbers::pi * 2_rad_per_s / 1_s;  // radians per second^2

//define PID
 frc::ProfiledPIDController<units::radians> m_turningPIDController{
      1.0,
      0.0,
      0.0,
      {kModuleMaxAngularVelocity, kModuleMaxAngularAcceleration}};


// Calculate the turning motor output from the turning PID controller.
  const auto turnOutput = m_turningPIDController.Calculate(
    {encoderRotation}, state.angle.Radians());



// Set the motor outputs for the turning of the wheels
directionMotor.SetVoltage(units::volt_t{turnOutput}); //+ drFeedforward);



};

// Find out current angle of direction motor from encoder
// Find out which direction to rotate direction motor
// Drive the angle motor
// Find out when to stop (maybe need to check if you are ate the required angle)

