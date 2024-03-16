#include "Shoot+Intake.h"

frc::Timer shooterTimer{};

void ShootAndIntake(frc::XboxController& xbox, 
            frc::VictorSP& motorIntakeArm, 
            frc::VictorSP& motorIntakeWheel, 
            frc::VictorSP& motorShooterLeft,
            frc::VictorSP& motorShooterRight)
{


if (true == xbox.GetYButtonPressed())
{
    shooterTimer.Reset();
    auto seconds = shooterTimer.Get();
    shooterTimer.Start();
    
    motorShooterLeft.Set(speakerShooterSpeed);
    motorShooterRight.Set(-1.0*speakerShooterSpeed);
    if (seconds<5_s && seconds>3_s)
    {
        motorIntakeWheel.Set(speakerIntakeWheelOutSpeed);
    }
    else
    {
        motorIntakeWheel.Set(0);
    }
}

else if (true == xbox.GetAButtonPressed())
{
    shooterTimer.Reset();
    auto seconds = shooterTimer.Get();
    shooterTimer.Start();
    
    motorShooterLeft.Set(ampShooterSpeed);
    motorShooterRight.Set(-1.0*ampShooterSpeed);
    if (seconds<5_s && seconds>3_s)
    {
        motorIntakeWheel.Set(speakerIntakeWheelOutSpeed);
    }
    else
    {
        motorIntakeWheel.Set(0);
    }
}

else {
    motorShooterLeft.Set(0);
    motorShooterRight.Set(0);
    motorIntakeWheel.Set(0);
}

}