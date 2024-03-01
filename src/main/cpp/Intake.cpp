#include "Intake.h"
#include <frc/motorcontrol/VictorSP.h>
//Speeds
const double intakeArmRetractSpeed = 1.0;
const double intakeArmExtendSpeed = -1.0;
const double intakeWheelInSpeed = 0.6;
const double intakeWheelOutSpeed = -0.6;

// xbox buttons
const int dpadUpButton = 0;
const int dpadDownButton = 180;

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

    if (xbox.GetXButton())
    {
    motorIntakeArm.Set(intakeArmRetractSpeed);
    }

    else if (xbox.GetBButton())
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
    if (xbox.GetLeftTriggerAxis())
    {
    motorIntakeWheel.Set(intakeWheelOutSpeed);
    }

    else if (xbox.GetRightTriggerAxis())
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