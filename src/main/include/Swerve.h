#pragma once

#include <frc/kinematics/ChassisSpeeds.h>

#include <frc/Joystick.h>

class Swerve {
public:
//calculates the chassis x and y speed and rotation speed based on joystick
    void manualChassisSpeed(frc::Joystick& joystick);

};