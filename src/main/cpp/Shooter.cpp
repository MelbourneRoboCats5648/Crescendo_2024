#include "Shooter.h"
#include <frc/motorcontrol/VictorSP.h>

// PWM ports - TODO Check
const int motorShooterLeftPort = 2;
const int motorShooterRightPort = 3;

// Speeds
const int speakerShooterSpeed = 1;
const int ampShooterSpeed = 0.5;

//Shooter Motors
frc::VictorSP motorShooterLeft{motorShooterLeftPort};
frc::VictorSP motorShooterRight{motorShooterRightPort};


//When Shooting, the Y and A buttons will control the speed for the shooter
//When The driver wants to shoot the note, they will use the intake release button
//Make sure the shooter wheels are running before releasing intake to shoot
void Shooter(frc::XboxController& xbox){

//Speaker
if (xbox.GetYButtonPressed())
{
  motorShooterLeft.Set(speakerShooterSpeed);
  motorShooterRight.Set(speakerShooterSpeed);
}

//Amp
else if (xbox.GetAButtonPressed())
{
  motorShooterLeft.Set(ampShooterSpeed);
  motorShooterRight.Set(ampShooterSpeed);
}
else
{
  motorShooterLeft.Set(0);
  motorShooterRight.Set(0);
}

}
