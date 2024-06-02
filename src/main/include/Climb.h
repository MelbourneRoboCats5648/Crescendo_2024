
#pragma once

#include <frc/Joystick.h>
#include <frc/motorcontrol/VictorSP.h>

// PWM ports - TODO Check
const int motorClimbLeftPort = 1;
const int motorClimbRightPort = 0;

class Climb{
    public:
        Climb()
        {     
        }
    public:
        void ClimbFunctions(frc::Joystick& joystick);

    public:
        frc::VictorSP m_motorClimbLeft{motorClimbLeftPort};
        frc::VictorSP m_motorClimbRight{motorClimbRightPort};
};
