#include "ShootAndIntake.h"

frc::Timer shooterTimer{};

// TODO - add consts for timings
const auto SHOOT_DURATION = 1_s;
const auto INTAKE_START = 0.4_s;

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
        if(milliseconds < SHOOT_DURATION && milliseconds > 0_s)
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

        if(milliseconds < SHOOT_DURATION && milliseconds > INTAKE_START)
        { 
            m_intake.motorIntakeWheel.Set(speakerIntakeWheelOutSpeed);
        }
        else
        {
            m_intake.motorIntakeWheel.Set(0.0);
        }

        if(milliseconds > SHOOT_DURATION)
        {
            shooterTimer.Stop();
            shooterTimer.Reset();
        }
    }

}