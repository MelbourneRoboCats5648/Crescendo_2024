#pragma once

#include <frc/XboxController.h>
#include <frc/motorcontrol/VictorSP.h>
#include <frc/Timer.h>

#include "Shooter.h"
#include "Intake.h"


class ShootAndIntake{
    public:
        ShootAndIntake() :
        m_shooter{},
        m_intake{}
        {     
        }
    public:
        void ShootAndIntakeFunctions(frc::XboxController& xbox);

    public:
        Shooter m_shooter;
        Intake m_intake;

    public:
              
};