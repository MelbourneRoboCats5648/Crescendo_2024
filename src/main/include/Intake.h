
#pragma once

#include <frc/XboxController.h>
#include <frc/motorcontrol/VictorSP.h>

const double intakeArmRetractSpeed = 0.4;
const double intakeArmExtendSpeed = -0.4;

const double intakeWheelInSpeed = 0.7;
const double ampIntakeWheelOutSpeed = -0.7;
const double speakerIntakeWheelOutSpeed = -1.0;



//PWM Ports
const int motorIntakeArmPort = 3;
const int motorIntakeWheelPort = 2;

/** Intake encoder
const int aChannel = 0; 
const int bChannel = 1; 
*/

class Intake{
    public:
        Intake()
        {     
        }

    public:
        frc::VictorSP motorIntakeArm{motorIntakeArmPort};
        frc::VictorSP motorIntakeWheel{motorIntakeWheelPort};
    public:
        void DoIntake(frc::XboxController& xbox);

};
