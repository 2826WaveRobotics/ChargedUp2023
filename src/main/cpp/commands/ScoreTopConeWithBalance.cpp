// RobotBuilder Version: 5.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: SequentialCommandGroup.

#include "commands/ScoreTopConeWithBalance.h"
#include "commands/WaveWaitCommand.h"
#include "commands/AutoBalance.h"
#include "commands/SequentialScoreTopCone.h"
#include "frc2/command/SequentialCommandGroup.h"

ScoreTopConeWithBalance::ScoreTopConeWithBalance(Elevator* m_elevator, SwerveDrive* m_drive)
:m_elevator(m_elevator), m_drive(m_drive)
{
    SetName("ScoreTopConeWithBalance");
    AddRequirements({m_elevator});

    AddCommands(
        frc2::SequentialCommandGroup
        (
            // score cone (top)
            SequentialScoreTopCone(m_elevator),
            // pause 1 sec
            WaveWaitCommand(units::second_t(1.0)),
            // balance
            AutoBalance(m_drive)
        )
    );
}

bool ScoreTopConeWithBalance::RunsWhenDisabled() const 
{
    return false;
}