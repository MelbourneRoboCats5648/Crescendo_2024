#include "NewAuto.h"
#include <frc/Timer.h>
#include "frc/DriverStation.h"
#include <iostream>

void NewAuto::RestartTimer()
{
    m_AutoTimer.Reset();
    m_AutoTimer.Start();
}

void NewAuto::AutoInit(DriveTrain& driveTrain)
{
    frc::DriverStation::GetAlliance();
    m_state = AutoState::DEFAULT;
}

void NewAuto::Run(DriveTrain& driveTrain, ShootAndIntake& shootAndIntake)
{
    units::time::second_t seconds = m_AutoTimer.Get();
    switch(m_state)
    {
        case AutoState::DEFAULT:
            driveTrain.SetPositionToZeroDistance();
            // Transition to first state
            m_state = AutoState::MOVE_FORWARD;
            RestartTimer();
            break;

        case AutoState::MOVE_FORWARD:
            if (seconds <= 2_s)
            {
                driveTrain.SetAllModules(frc::ChassisSpeeds{0.5_mps, 0.0_mps, units::radians_per_second_t(0)});
                std::cout << "moving forward" << std::endl;
            }
            else
            {
                driveTrain.SetAllModules(frc::ChassisSpeeds{0.0_mps, 0.0_mps, units::radians_per_second_t(0)});
                
                m_state = AutoState::RUN_SHOOTER;
                RestartTimer();
            }
            break;

        case AutoState::RUN_SHOOTER:
            if (seconds <= 5_s)
            {
                shootAndIntake.m_shooter.motorShooterLeft.Set(1.0);
                shootAndIntake.m_shooter.motorShooterRight.Set(-1.0);
                std::cout << "running shooter" << std::endl;
            }
            else
            {
                shootAndIntake.m_shooter.motorShooterLeft.Set(0.0);
                shootAndIntake.m_shooter.motorShooterRight.Set(0.0);
                m_state = AutoState::MOVE_BACKWARD;
                RestartTimer();
            }
            break;

        case AutoState::MOVE_BACKWARD:
            if (seconds <= 2_s)
            {
                driveTrain.SetAllModules(frc::ChassisSpeeds{-0.5_mps, 0.0_mps, units::radians_per_second_t(0)});
                std::cout << "moving backward" << std::endl;
            }
            else 
            {
                driveTrain.SetAllModules(frc::ChassisSpeeds{0.0_mps, 0.0_mps, units::radians_per_second_t(0)});
                m_state = AutoState::FINISHED;
                RestartTimer();
            }
            break;

        case AutoState::FINISHED:
            std::cout << "finished" << std::endl;
            break;

        default:
            std::cout << "ERROR: invalid state " << m_state << std::endl;
            break;
    }
}