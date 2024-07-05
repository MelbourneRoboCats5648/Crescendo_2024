#include "CLimb.h"

// Speeds
const double climbUpSpeed = 0.6; //was 0.25
const double climbDownSpeed = -0.6;


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
void Climb::ClimbFunctions(frc::Joystick& joystick) {

  if (joystick.GetRawButton(leftUpButton))
  {
    m_motorClimbLeft.Set(climbUpSpeed);
  }
  else if (joystick.GetRawButton(leftDownButton))
  {
    m_motorClimbLeft.Set(climbDownSpeed);
  }
  else
  {
    m_motorClimbLeft.Set(0 );
  }

  if (joystick.GetRawButton(rightUpButton))
  {
    m_motorClimbRight.Set(climbUpSpeed);
  }
  else if (joystick.GetRawButton(rightDownButton))
  {
    m_motorClimbRight.Set(climbDownSpeed);
  }
  else
  {
    m_motorClimbRight.Set(0);
  }
}