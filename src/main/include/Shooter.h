#pragma once

#include <frc/XboxController.h>

// Speeds
const double speakerShooterSpeed = 1.0;
const double ampShooterSpeed = 0.4;
// PWM ports - TODO Check
const int motorShooterLeftPort = 4;
const int motorShooterRightPort = 5;



void Shooter(frc::XboxController& xbox);