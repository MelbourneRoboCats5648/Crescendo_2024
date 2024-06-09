#pragma once

#include <frc/XboxController.h>
#include <frc/motorcontrol/VictorSP.h>


// Speeds
const double speakerShooterSpeed = 1.0;
const double ampShooterSpeed = 0.2;

//MotorPorts
// PWM ports - TODO Check
const int motorShooterLeftPort = 4;
const int motorShooterRightPort = 5;


class Shooter{
    public:
        Shooter()
        {     
        }
    public:
        frc::VictorSP motorShooterLeft{motorShooterLeftPort};
        frc::VictorSP motorShooterRight{motorShooterRightPort};
    public:
        void DoShoot(frc::XboxController& xbox);

};        