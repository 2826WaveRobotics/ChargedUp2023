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


#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include "subsystems/Elevator.h"
#include "subsystems/SwerveDrive.h"

#include <frc2/command/SequentialCommandGroup.h>

/**
 *
 *
 * @author ExampleAuthor
 */
class ScoreMidConeWithBalance: public frc2:: CommandHelper<frc2::SequentialCommandGroup,
ScoreMidConeWithBalance>{
public:

    explicit ScoreMidConeWithBalance(Elevator* m_elevator, SwerveDrive* m_drive);

    bool RunsWhenDisabled() const override;

private:

    Elevator* m_elevator;
    SwerveDrive* m_drive;
};
