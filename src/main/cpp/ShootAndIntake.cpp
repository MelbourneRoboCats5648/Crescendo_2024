#include "ShootAndIntake.h"

frc::Timer shooterTimer{};

// TODO - add consts for timings
//const int SHOOT_DURATION;
//const int INTAKE_DURATION;

void ShootAndIntake::ShootAndIntakeFunctions(frc::XboxController& xbox)
{
    if (xbox.GetLeftStickButtonPressed() == true)
    {
        shooterTimer.Reset();
        shooterTimer.Start();
    }
    
    auto milliseconds = shooterTimer.Get();

    if (milliseconds > 0_s)
    {
        if(milliseconds < 1_s && milliseconds > 0_s)
        {
            m_shooter.motorShooterLeft.Set(speakerShooterSpeed);
            m_shooter.motorShooterRight.Set(-1.0*speakerShooterSpeed);
        }
        else
        {
            m_shooter.motorShooterLeft.Set(0.0);
            m_shooter.motorShooterRight.Set(0.0);
            //TODO - maybe stop and reset timer here???
        }

        if(milliseconds < 1_s && milliseconds > 0.4_s)
        { 
            m_intake.motorIntakeWheel.Set(speakerIntakeWheelOutSpeed);
        }
        else
        {
            m_intake.motorIntakeWheel.Set(0.0);
        }

        if(milliseconds > 1_s)
        {
            shooterTimer.Stop();
            shooterTimer.Reset();
        }
    }

}