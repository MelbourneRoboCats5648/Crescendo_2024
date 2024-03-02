#include "Intake.h"
#include <frc/motorcontrol/VictorSP.h>
//Speeds
const double intakeArmRetractSpeed = 0.4;
const double intakeArmExtendSpeed = -0.4;

const double intakeWheelInSpeed = 0.6;
const double ampIntakeWheelOutSpeed = -0.6;
const double speakerIntakeWheelOutSpeed = -1.0;

// xbox buttons - not being used *******
//const int dpadUpButton = 0;
//const int dpadDownButton = 180;

//PWM Ports
const int motorIntakeArmPort = 2;
const int motorIntakeWheelPort = 3;

/** Intake encoder
const int aChannel = 0; 
const int bChannel = 1; 
*/

//Intake variables
frc::VictorSP motorIntakeArm{motorIntakeArmPort};
frc::VictorSP motorIntakeWheel{motorIntakeWheelPort};
//frc::Encoder encoderIntake{aChannel, bChannel};

/**
 * Controls the intake arms and wheels
 * Controls 2 motors independently (one for move arms one for wheels)
 * Swing arms up and down → 1 motor - up button for in, down button for out
 * Spin wheels opposite directions (1 motor)
 * Triggers are for note in and out (wheel spinning)
 * Plus button for arm in and out
**/
void Intake(frc::XboxController& xbox) {

    // arm in and out

    if (xbox.GetBButton())
    {
        motorIntakeArm.Set(intakeArmRetractSpeed);
    }

    else if (xbox.GetXButton())
    {
        motorIntakeArm.Set(intakeArmExtendSpeed);
    }
    else 
    {
        motorIntakeArm.Set(0.0);
    }

    // intake wheels spinning
    // right trigger wheel in left trigger wheel out
    // josh help how to fix
    if (xbox.GetRightTriggerAxis())
    {
    motorIntakeWheel.Set(speakerIntakeWheelOutSpeed);
    }

    else if (xbox.GetRightBumperPressed())
    {
    motorIntakeWheel.Set(ampIntakeWheelOutSpeed);
    }

    else if (xbox.GetLeftTriggerAxis())
    {
    motorIntakeWheel.Set(intakeWheelInSpeed);
    }
    else
    {
        motorIntakeWheel.Set(0.0);
    }

}

// For intake:
// code the encoder