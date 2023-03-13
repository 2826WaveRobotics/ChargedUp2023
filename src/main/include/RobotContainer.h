// RobotBuilder Version: 4.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: RobotContainer.

#pragma once

#include <frc/smartdashboard/SendableChooser.h>
#include <frc2/command/Command.h>
#include <frc/XboxController.h>

#include "subsystems/SwerveDrive.h"
#include "subsystems/Elevator.h"
#include "subsystems/Intake.h"
#include "subsystems/Vision.h"

// need to include auto routines
#include "commands/AutonomousCommand.h"
#include "commands/DriveTimed.h"
#include "commands/WaveWaitCommand.h"
#include "commands/SwerveInitializeCommand.h"
#include "commands/SequentialScoreTopCone.h"
#include "commands/SequentialScoreMidCone.h"
#include "commands/ScoreTopConeWithBalance.h"
#include "commands/ScoreMidConeWithBalance.h"
#include "commands/AutoBalance.h"
#include "commands/StowElevator.h"
#include "commands/EndEffectorDown.h"
#include "commands/EndEffectorUp.h"
#include "commands/OpenGrabber.h"

class RobotContainer {

public:

    frc2::Command* GetAutonomousCommand();
    static RobotContainer* GetInstance();

    // The robot's subsystems
    SwerveDrive m_swerveDrive;
    Elevator m_elevator;
    Intake m_intake;
    Vision m_vision;

    // Controller input
    frc::XboxController* getDriver();
    frc::XboxController* getOperator();

    // joystick input smoothing functions
    double LinearInterpolate(double speed, double targetSpeed, double movePercentage);
    double GetPreviousJoystickInputLX();
    void SetPreviousJoystickInputLX(double input);
    double GetPreviousJoystickInputLY();
    void SetPreviousJoystickInputLY(double input);
    double GetPreviousJoystickInputRX();
    void SetPreviousJoystickInputRX(double input);

private:

    RobotContainer();

    // Joysticks
    frc::XboxController m_driver{0};
    frc::XboxController m_operator{1};

    // previous joystick input
    double m_previousJoystickInputLX = 0;
    double m_previousJoystickInputLY = 0;
    double m_previousJoystickInputRX = 0;

    // the chooser for the autonoumous routines
    frc::SendableChooser<frc2::Command*> m_chooser;

    // THIS IS EXTREMELY EXPERIMENTAL
    // frc::SendableChooser<frc2::Command*> m_customCommandChoosers[5];

    AutonomousCommand m_autonomousCommand;
    static RobotContainer* m_robotContainer;

    void ConfigureButtonBindings();
};