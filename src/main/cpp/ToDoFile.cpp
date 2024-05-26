
    /* Port Locations for all motors
     * Physical motor locations from robot centre
     * Check encoder port locations
     * Finish coding Swerve
     * Code Auto
     * Figure out intake position control
     * Make speeds real \/
     * Calibrate gyro

    //TODO check encoder range


Module angle optimization
The SwerveModuleState class contains a static optimize() (Java) / Optimize() (C++) method that is used to “optimize” the speed and angle setpoint of a given SwerveModuleState to minimize the change in heading. For example, if the angular setpoint of a certain module from inverse kinematics is 90 degrees, but your current angle is -89 degrees, this method will automatically negate the speed of the module setpoint and make the angular setpoint -90 degrees to reduce the distance the module has to travel.

This method takes two parameters: the desired state (usually from the toSwerveModuleStates method) and the current angle. It will return the new optimized state which you can use as the setpoint in your feedback control loop.


JAVA

C++
auto flOptimized = frc::SwerveModuleState::Optimize(fl,
   units::radian_t(m_turningEncoder.GetDistance()));


    


    */
