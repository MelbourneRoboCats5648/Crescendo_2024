#include "PathFinder.h"
#include <frc/motorcontrol/VictorSP.h>

void Path(frc::XboxController& xbox)
{
   if  (xbox.GetLeftBumperPressed());
    frc::Trajectory trajectory;
    fs::path deployDirectory = frc::filesystem::GetDeployDirectory();
    deployDirectory = deployDirectory / "paths" / "TestPath.wpilib.json";
    trajectory = frc::TrajectoryUtil::FromPathweaverJson(deployDirectory.string());
}