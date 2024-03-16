#include "CLimb.h"
#include <frc/motorcontrol/VictorSP.h>



// PWM ports - TODO Check
const int motorClimbLeftPort = 1;
const int motorClimbRightPort = 0;

// Speeds
const double climbUpSpeed = 0.25;
const double climbDownSpeed = -0.25;

// Climb variables
frc::VictorSP motorClimbLeft{motorClimbLeftPort};
frc::VictorSP motorClimbRight{motorClimbRightPort};

// Joystick buttons - TODO Check
const int leftUpButton = 5;
const int leftDownButton = 3;
const int rightUpButton = 6;
const int rightDownButton = 4;

/**
 * Controls the climbing arms.
 * Controls 2 Victor SP motors independently.
 * Controlled by the Joystick controller using the top buttons
 * This will allow the driver to raise and lower the climb arms independently
 * 
 * TODO - research how to 'lock' our climb
 */
void Climb(frc::Joystick& joystick) {

  if (joystick.GetRawButton(leftUpButton))
  {
    motorClimbLeft.Set(climbUpSpeed);
  }
  else if (joystick.GetRawButton(leftDownButton))
  {
    motorClimbLeft.Set(climbDownSpeed);
  }
  else
  {
    motorClimbLeft.Set(0 );
  }

  if (joystick.GetRawButton(rightUpButton))
  {
    motorClimbRight.Set(climbUpSpeed);
  }
  else if (joystick.GetRawButton(rightDownButton))
  {
    motorClimbRight.Set(climbDownSpeed);
  }
  else
  {
    motorClimbRight.Set(0);
  }
}