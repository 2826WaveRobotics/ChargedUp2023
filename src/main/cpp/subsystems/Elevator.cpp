// RobotBuilder Version: 5.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: Subsystem.

#include <iostream>
#include "subsystems/Elevator.h"
#include <frc/smartdashboard/SmartDashboard.h>

#include "RobotContainer.h"

Elevator::Elevator()
{
    SetName("Elevator");
    SetSubsystem("Elevator");

    m_elevatorMotorA = new rev::CANSparkMax(k_elevatorMotorA, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    m_elevatorMotorB = new rev::CANSparkMax(k_elevatorMotorB, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    m_endEffectorMotor = new rev::CANSparkMax(k_endofactorMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    m_elevatorMotorA->SetInverted(true);
    m_elevatorMotorB->SetInverted(true);
    m_endEffectorMotor->SetInverted(true);
    
    m_elevatorPID = new frc2::PIDController(k_P, k_I, k_D);

    m_elevatorFunction = Elevator_Off;
    m_elevatorEncoderA = new rev::SparkMaxRelativeEncoder(m_elevatorMotorA->GetEncoder());
    if(NULL != m_elevatorEncoderA) 
    {
        m_elevatorEncoderA->SetPositionConversionFactor(k_encoderPosConversionFactor);
    }

    m_elevatorEncoderB = new rev::SparkMaxRelativeEncoder(m_elevatorMotorB->GetEncoder());
    if(NULL != m_elevatorEncoderB) 
    {
        m_elevatorEncoderB->SetPositionConversionFactor(k_encoderPosConversionFactor); 
    }

    m_elevatorPosition = 0.0;
    m_elevatorHomePosition = 0.0;
    m_elevatorTarget = 0.0;
    m_isStowing = false;

    // May or may not use this
    m_distancePerRotation = (k_numOfTeeth * k_teethSize)/k_gearRatio;
}

void Elevator::initialize()
{
    m_operatorJoystick = RobotContainer::GetInstance()->getOperator();
}

bool Elevator::isElevatorAtHome() 
{
    if(m_elevatorAtHomeLimitSwitch.Get()) 
    {
        return true;
    }

    return false;
}

double Elevator::getElevatorPosition() 
{
    // Get the number of rotation of the motor
    double numOfRotationA = m_elevatorEncoderA->GetPosition();

    return (m_distancePerRotation * numOfRotationA);
}

void Elevator::setElevator(double speed) 
{
    m_elevatorMotorA->Set(speed);
    m_elevatorMotorB->Set(speed);    
}

void Elevator::Periodic() 
{
    // Put code here to be run every loop

    // Set zero position (temporary for testing)
    if(m_operatorJoystick->GetStartButton())
    {
        m_elevatorEncoderA->SetPosition(0.0);
        m_elevatorEncoderB->SetPosition(0.0);
    }
    // Set scoring object (shall be based on the sensor)
    if(m_operatorJoystick->GetBackButton())
    {
        // Toggle state (for testing)
        m_isCone = !m_isCone;
    }

    runElevator();

    runEndEffector();
}


void Elevator::SimulationPeriodic() 
{
    // This method will be called once per scheduler run when in simulation

}

double Elevator::getPIDSpeed(double pidCommand)
{
    // Convert PID output to speed command between -1.0 to 1.0
    double speedOut = 0;

    speedOut = pidCommand / 10.0;    // temporary place holder

    if(k_maxElevatorSpeed <= speedOut)
    {
        speedOut = k_maxElevatorSpeed;
    }
    else if(-k_maxElevatorSpeed >= speedOut)
    {
        speedOut = -k_maxElevatorSpeed;
    }

    return speedOut;
}

void Elevator::runElevator() 
{
    //////////////  Routine ELEVATOR FUNCTIONS  /////////////////////
    double elevatorSpeedCmd = 0.0;
    bool elevatorOverride = m_operatorJoystick->GetLeftBumper();

    m_elevatorPosition = getElevatorPosition();
    if(isElevatorAtHome())
    {
        m_elevatorHomePosition = m_elevatorHomePosition;
    }

    if(elevatorOverride) 
    {
        // Manual operation
        m_elevatorFunction = Elevator_Off;
        m_elevatorTarget = 0.0;
        elevatorSpeedCmd = m_operatorJoystick->GetRightY();
        if(k_jsDeadband > std::fabs(elevatorSpeedCmd))
        {
            elevatorSpeedCmd = 0.0;
        }
        
        std::cout << "Manual Operation" << std::endl;
    } 
    else 
    {
        // Get the target command
        if(m_operatorJoystick->GetAButton()) 
        {
            if(m_isCone) 
            {
                m_elevatorTarget = k_elevatorTargetTopCone;
            } 
            else 
            {
                m_elevatorTarget = k_elevatorTargetTopCube;
            }
            m_elevatorFunction = Elevator_Deploy;
        } else if(m_operatorJoystick->GetBButton()) 
        {
            if(m_isCone) 
            {
                m_elevatorTarget = k_elevatorTargetMiddleCone;
            } 
            else 
            {
                m_elevatorTarget = k_elevatorTargetMiddleCube;
            }
            m_elevatorFunction = Elevator_Deploy;
        } 
        else if(m_operatorJoystick->GetXButton()) 
        {
            m_elevatorTarget = k_elevatorHumanStation;
            m_elevatorFunction = Elevator_Deploy;
        } 
        else if(m_operatorJoystick->GetYButton()) 
        {
            m_elevatorTarget = m_elevatorHomePosition;
            m_elevatorFunction = Elevator_Deploy;
        } 


        // Set the elevator function based on Joystick command
        switch(m_elevatorFunction) 
        {
            case Elevator_Off:
            default:
                break;

            case Elevator_Deploy:
                // Check the direction to move the elevator
                double pidOut = getPIDSpeed(m_elevatorPID->Calculate(m_elevatorPosition, m_elevatorTarget));
                std::cout << "PIDOut: " << pidOut << std::endl;

                double delta = std::fabs(m_elevatorTarget - m_elevatorPosition);
                if(k_delta < delta)
                {
                    // Extend elevator
                    elevatorSpeedCmd = pidOut;
                }
                else
                {
                    if(m_isStowing)
                    {
                        // Finish stowing
                        if(!isElevatorAtHome() || (0.1 <= delta))
                        {
                            elevatorSpeedCmd = 0.5;
                        }
                        else
                        {
                            m_isStowing = false;
                        }
                    }
                    else
                    {
                        m_elevatorFunction = Elevator_Off;
                    }
                }

                break;
        }
    }

    // Elevator can not extend beyond the max limit
    if(k_maxElevatorPosition < m_elevatorPosition)
    {
        std::cout << "Max Elevator position reached." << std::endl;
        //elevatorSpeedCmd =0.0;
    }

    setElevator(elevatorSpeedCmd);
    std::cout << "ElevPosition: " << m_elevatorPosition << "; Target: " << m_elevatorTarget << ";  ElevCmd: " << elevatorSpeedCmd << std::endl;
}


//////////////// endEffector operation ////////////////////

void Elevator::setEndEffectorRoller(double speed) 
{
    m_endEffectorMotor->Set(speed);
}

void Elevator::moveEndEffector(bool down)
{
    m_endEffectorOut.Set(down);
}

void Elevator::closeGrabber()
{
    m_endEffectorGrabberOut.Set(false);
}

void Elevator::openGrabber()
{
    m_endEffectorGrabberOut.Set(true);
}

void Elevator::runEndEffector() 
{
    int endEffectorCmd = m_operatorJoystick->GetPOV(0);
    switch(m_endEffectorFunction)    {
        case EF_Up:
        default:
            // EndEffectorUp, turn off the output
            moveEndEffector(false);

            // EndEffector can go down only if the Elevator is above Human Station level
            if((0 == endEffectorCmd) && (k_elevatorHumanStation < m_elevatorPosition))
            {
                m_endEffectorFunction = EF_Down;
            }
            break;
        case EF_Down:
            // EndEffector Down, turn on the output
            moveEndEffector(true);

            if((180 == endEffectorCmd) || (k_elevatorHumanStation > m_elevatorPosition))
            {
                m_endEffectorFunction = EF_Up;
            }
            break;
    }

    std::cout << "EFCmd: " << endEffectorCmd << "; Function: " << m_endEffectorFunction << std::endl;

    /////////////// End Effector Operation ///////////////////

    double endEffectorRollerCmd = m_operatorJoystick->GetLeftY();

    if(k_jsDeadband > std::fabs(endEffectorRollerCmd)) 
    {
        endEffectorRollerCmd = 0;
    } 

    setEndEffectorRoller(endEffectorRollerCmd * k_endEffectorSpeedFactor);
 
    ///////////////////// End Effector Grabber Operations ///////////////////////

    if(0.5 < m_operatorJoystick->GetLeftTriggerAxis())
    {
        openGrabber();
    }
    else
    {
        closeGrabber();
    }

    // Print out for debugging
    // std::cout << "EFCmd1: " << endEffectorCmd1 << "; EFCmd2: " << endEffectorCmd2 << ";  EFCmd3: " << endEffectorCmd3 << std::endl;
}
