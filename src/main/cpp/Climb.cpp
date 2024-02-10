#include "CLimb.h"
#include <frc/motorcontrol/VictorSP.h>
#include <frc/Joystick.h>


// PWM ports - TODO Check
const int motorClimbLeftPort = 0;
const int motorClimbRightPort = 1;

// Speeds
const int climbUpSpeed = 0.8;
const int climbDownSpeed = -0.8;

// Climb variables
frc::VictorSP motorClimbLeft{motorClimbLeftPort};
frc::VictorSP motorClimbRight{motorClimbRightPort};

// Joystick buttons - TODO Check
const int leftUpButton = 1;
const int leftDownButton = 2;
const int rightUpButton = 3;
const int rightDownButton = 4;


/**
 * Controls the climbing arms.
 * Controls 2 Victor SP motors independently.
 * Controlled by the Joystick controller using the top buttons
 * This will allow the driver to raise and lower the climb arms independently
 * 
 * TODO - research how to 'lock' our climb
 */
void Climb() {

  if (driveJoyStick.GetRawButton(leftUpButton))
  {
    motorClimbLeft.Set(climbUpSpeed);
  }
  else if (driveJoyStick.GetRawButton(leftDownButton))
  {
    motorClimbLeft.Set(climbDownSpeed);
  }
  else
  {
    motorClimbLeft.Set(0);
  }

  if (driveJoyStick.GetRawButton(rightUpButton))
  {
    motorClimbRight.Set(climbUpSpeed);
  }
  else if (driveJoyStick.GetRawButton(rightDownButton))
  {
    motorClimbRight.Set(climbDownSpeed);
  }
  else
  {
    motorClimbRight.Set(0);
  }
}