// RobotBuilder Version: 5.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: Command.

#include "commands/WaveWaitCommand.h"
#include "frc2/command/WaitCommand.h"
#include <iostream>

WaveWaitCommand::WaveWaitCommand(units::second_t timeout): WaitCommand(timeout) {

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("WaveWaitCommand");
    m_timeout = timeout;
}

// Called just before this Command runs the first time
void WaveWaitCommand::Initialize() {
    
}

// Called repeatedly when this Command is scheduled to run
void WaveWaitCommand::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool WaveWaitCommand::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void WaveWaitCommand::End(bool interrupted) {
    // std::cout << "Wave Wait" << std::endl;
    WaitCommand::End(interrupted);
}

bool WaveWaitCommand::RunsWhenDisabled() const {
    return false;

}
