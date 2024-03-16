#include "Shoot+Intake.h"

frc::Timer shooterTimer{};

void ShootAndIntake(frc::XboxController& xbox, 
            frc::VictorSP& motorIntakeArm, 
            frc::VictorSP& motorIntakeWheel, 
            frc::VictorSP& motorShooterLeft,
            frc::VictorSP& motorShooterRight)
{
auto seconds = shooterTimer.Get();

if (true == xbox.GetYButton())
{
    shooterTimer.Reset();
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

}