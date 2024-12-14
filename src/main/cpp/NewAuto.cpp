#include "NewAuto.h"
#include <frc/Timer.h>
#include "frc/DriverStation.h"
#include <iostream>

void NewAuto::ResetTimer()
{
    m_AutoTimer.Reset();
    m_AutoTimer.Start();
}

void NewAuto::AutoInit(DriveTrain& driveTrain)
{
    ResetTimer();
    frc::DriverStation::GetAlliance();
    driveTrain.SetPositionToZeroDistance();

    m_state = AutoState::MOVE_FORWARD;
}

void NewAuto::AutoYay(DriveTrain& driveTrain, ShootAndIntake& shootAndIntake)
{
    units::time::second_t seconds = m_AutoTimer.Get();
    switch(m_state)
    {
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
                ResetTimer();
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
                ResetTimer();
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
                ResetTimer();
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