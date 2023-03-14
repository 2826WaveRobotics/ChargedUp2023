
#include "commands/SequentialScoreTopCone.h"
#include "commands/ExtendElevatorTopCone.h"
#include "commands/WaveWaitCommand.h"
#include "commands/StowElevator.h"

SequentialScoreTopCone::SequentialScoreTopCone(Elevator* m_elevator)
:m_elevator(m_elevator)
{
    SetName("SequentialScoreTopCone");
    AddRequirements({m_elevator});

    AddCommands(
        frc2::SequentialCommandGroup(
            // place cone (top)
            ExtendElevatorTopCone(m_elevator),

            // pause
            WaveWaitCommand(units::second_t(0.5)),

            // TODO: score with end effector

            // stow sequence
            StowElevator(m_elevator)
        )
    );
}

bool SequentialScoreTopCone::RunsWhenDisabled() const 
{
    return false;
}