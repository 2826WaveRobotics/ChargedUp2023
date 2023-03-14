
#include "commands/ScoreTopConeBackout.h"
#include "commands/WaveWaitCommand.h"
#include "commands/DriveTimed.h"
#include "commands/SequentialScoreTopCone.h"

ScoreTopConeBackout::ScoreTopConeBackout(Elevator* m_elevator, SwerveDrive* m_drive)
:m_elevator(m_elevator), m_drive(m_drive)
{
    SetName("ScoreTopConeBackout");
    AddRequirements({m_elevator});

    AddCommands(
        frc2::SequentialCommandGroup
        (
            // score cone (top)
            SequentialScoreTopCone(m_elevator),
            // pause 1 sec
            WaveWaitCommand(units::second_t(1.0)),
            // exit community
            DriveTimed(m_drive, 0.0, 0.5, 0.0, units::second_t(1.5))
        )
    );
}

bool ScoreTopConeBackout::RunsWhenDisabled() const 
{
    return false;
}