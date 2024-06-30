#include "ShootAndIntake.h"

// TODO - add consts for timings
const auto SHOOT_DURATION = 1_s;
const auto INTAKE_START = 0.4_s;

void ShootAndIntake::ShootAndIntakeFunctions(frc::Timer& shooterTimer)
{

    
    auto milliseconds = shooterTimer.Get();

    if (milliseconds > 0_s)
    {
        m_shooter.motorShooterLeft.Set(speakerShooterSpeed);
        m_shooter.motorShooterRight.Set(-1.0*speakerShooterSpeed);

        if(milliseconds > INTAKE_START)
        {
            m_intake.motorIntakeWheel.Set(speakerIntakeWheelOutSpeed);
        }

        if(milliseconds > SHOOT_DURATION)
        {
            m_shooter.motorShooterLeft.Set(0.0);
            m_shooter.motorShooterRight.Set(0.0);
            m_intake.motorIntakeWheel.Set(0.0);

            shooterTimer.Stop();
            shooterTimer.Reset();
        }
    }

}