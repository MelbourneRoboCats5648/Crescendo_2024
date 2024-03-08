#include "Shooter.h"
#include <frc/motorcontrol/VictorSP.h>

//Shooter Motors
frc::VictorSP motorShooterLeft{motorShooterLeftPort};
frc::VictorSP motorShooterRight{motorShooterRightPort};


//When Shooting, the Y and A buttons will control the speed for the shooter
//When The driver wants to shoot the note, they will use the intake release button
//Make sure the shooter wheels are running before releasing intake to shoot
void Shooter(frc::XboxController& xbox){

//Speaker
if (true == xbox.GetYButton())
{
  motorShooterLeft.Set(speakerShooterSpeed);
  motorShooterRight.Set(-1.0*speakerShooterSpeed); //inverting motor direction
}
//Amp
else if (true == xbox.GetAButton())
{
  motorShooterLeft.Set(ampShooterSpeed);
  motorShooterRight.Set(-1.0*ampShooterSpeed); //inverting motor direction
}
else
{
  motorShooterLeft.Set(0.0);
  motorShooterRight.Set(0.0);
}


}
