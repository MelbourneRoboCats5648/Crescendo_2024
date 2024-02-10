#include "Intake.h"
#include <frc/motorcontrol/VictorSP.h>

//Speeds
const int intakeArmRetractSpeed = 0.8;
const int intakeArmExtendSpeed = -0.8;
const int intakeWheelInSpeed = 0.5;
const int intakeWheelOutSpeed = -0.5;

// xbox buttons
const int dpadUpButton = 0;
const int dpadDownButton = 180;

//Ports
const int motorIntakeArmPort = 4;
const int motorIntakeWheelPort = 5;

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
void Intake() {

    // arm in and out

    if (xbox.GetPOV(dpadUpButton))
    {
    motorIntakeArm.Set(intakeArmRetractSpeed);
    }

    else if (xbox.GetPOV(dpadDownButton))
    {
    motorIntakeArm.Set(intakeArmExtendSpeed);
    }

    else 
    {
    motorIntakeArm.Set(0);
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
    motorIntakeWheel.Set(0);
    }

}

// For intake:
// code the encoder