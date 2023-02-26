// RobotBuilder Version: 4.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: Robot.

#include "Robot.h"
#include "Globals.h"

#include <iostream> 

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <iostream>

void Robot::RobotInit() {
  m_container = RobotContainer::GetInstance();
  m_container->m_elevator.Initialize();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() 
{ 
  frc2::CommandScheduler::GetInstance().Run(); 

  // TODO: check redundant with SwerveDrive::UpdatePodOffsetAngles 
  // SET pod offset angles with values from dashboard
  double leftOffset = frc::SmartDashboard::GetNumber("Left Offset", 404.0);
  double rightOffset = frc::SmartDashboard::GetNumber("Right Offset", 404.0);
  double pointOffset = frc::SmartDashboard::GetNumber("Point Offset", 404.0);
  m_container->m_swerveDrive.SetLeftPodOffsetAngle(leftOffset);
  m_container->m_swerveDrive.SetRightPodOffsetAngle(rightOffset);
  m_container->m_swerveDrive.SetPointPodOffsetAngle(pointOffset);
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
  m_autonomousCommand = m_container->GetAutonomousCommand();

  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Schedule();
  }
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }
}

double Joystick(double input, double deadzone) 
{ 
  return (std::fabs(input) < deadzone) ? 0 : input; 
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() 
{  
  // updates pod angle offsets (on dashboard)
  m_container->m_swerveDrive.UpdatePodOffsetAngles();

  // Drive Operations
  double targetJoystickLX =  Joystick(m_container->getDriver()->GetLeftX(), k_jsDeadband);
  double targetJoystickLY =  Joystick(m_container->getDriver()->GetLeftY(), k_jsDeadband);
  double targetJoystickRX = Joystick(m_container->getDriver()->GetRightX(), k_jsDeadband);

  // joystick inputs for swerve - scaling / ramp speed
  // double currentJoystickLX = m_container->LinearInterpolate(m_container->GetPreviousJoystickInputLX(), targetJoystickLX, 0.5);
  // double currentJoystickLY = m_container->LinearInterpolate(m_container->GetPreviousJoystickInputLY(), targetJoystickLY, 0.5);
  // double currentJoystickRX = m_container->LinearInterpolate(m_container->GetPreviousJoystickInputRX(), targetJoystickRX, 0.5);
  // m_container->m_swerveDrive.DrivePods(currentJoystickLX, currentJoystickLY, currentJoystickRX);
  // m_container->SetPreviousJoystickInputLX(currentJoystickLX);
  // m_container->SetPreviousJoystickInputLY(currentJoystickLY);
  // m_container->SetPreviousJoystickInputRX(currentJoystickRX);

  // #ifdef _TESTJOYSTICK
  // std::cout << "LX: " << currentJoystickLX << "     " << "LY: " << currentJoystickLY << "     " << "RX: " << currentJoystickRX << std::endl;
  // std::cout << "LY: " << targetJoystickLY << 
  //   "   scaled: " << m_container->LinearInterpolate(m_container->GetPreviousJoystickInputLY(), targetJoystickLY, 0.001) << 
  //   "   prev: " << m_container->GetPreviousJoystickInputLY() << std::endl;
  // #endif

  // std::cout << "LX: " << targetJoystickLX << "     " << "LY: " << targetJoystickLY << "     " << "RX: " << targetJoystickRX << std::endl;
  bool lockSwerve = m_container->getDriver()->GetYButton();
  if (!lockSwerve) {
    // joystick inputs for swerve - NO scaling / ramp
    // std::cout << "SWERVE DRIVE NO SCALING - drive pods" << std::endl;
    m_container->m_swerveDrive.DrivePods(targetJoystickLX, targetJoystickLY, targetJoystickRX);

    // Initial Swerve State
    bool initialSwerveState = m_container->getDriver()->GetStartButton();
    if (initialSwerveState) {
      std::cout << "INITIALIZE DRIVE - drive pods" << std::endl;
      m_container->m_swerveDrive.InitialSwerve();
    }
    
    // Swerve Diagnostics State
    bool testRightPod = m_container->getDriver()->GetBButton();
    bool testLeftPod = m_container->getDriver()->GetXButton();
    bool testPointPod = m_container->getDriver()->GetAButton();
    int testMotor = m_container->getDriver()->GetPOV();
    if ((testRightPod || testLeftPod || testPointPod) && (testMotor == 0 || testMotor == 180))
    {
      std::cout << "TESTING HARNESS DRIVE - drive pods" << std::endl;
      std::string podInput;
      std::string motorInput; 
      podInput = testRightPod ? "RIGHT" : podInput;
      podInput = testLeftPod ? "LEFT" : podInput;
      podInput = testPointPod ? "POINT" : podInput;
      motorInput = testMotor == 0 ? "TOP" : motorInput; 
      motorInput = testMotor == 180 ? "BOTTOM" : motorInput;

      // set motors for testing
      m_container->m_swerveDrive.DiagonosticSwerveRotate(podInput, motorInput, 0.7);
    }
  } else {
    std::cout << "LOCK DRIVE - drive pods" << std::endl;
    m_container->m_swerveDrive.LockSwerve();
  }
  
  // Elevator Operations
  m_container->m_elevator.runElevator();
}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
