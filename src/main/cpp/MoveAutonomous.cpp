#include "MoveAutonomous.h"
#include "Shooter.cpp"
#include "Intake.cpp"
#include "time.h"
#include "future"




void AutoYay()
{
   
if(Timer.getMatchTime()=2) 
{
    motorShooterLeft.Set(ampShooterSpeed);
    motorShooterRight.Set(-1.0*ampShooterSpeed);
}
if(Timer.getMatchTime()=6)
{
   motorIntakeWheel.Set(speakerIntakeWheelOutSpeed);
}
if(Timer.getMatchTime()=8)
{
    motorShooterLeft.Set(0);
    motorShooterRight.Set(0);
    motorIntakeWheel.Set(0);
};
}


