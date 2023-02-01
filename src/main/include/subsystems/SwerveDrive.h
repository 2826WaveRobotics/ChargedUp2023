// RobotBuilder Version: 4.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: Subsystem.
#pragma once

#include <frc2/command/SubsystemBase.h>
#include "ctre/Phoenix.h"
#include <frc/Encoder.h>
#include <rev/CANSparkMax.h>
#include "subsystems/SwervePod.h"
#include <frc/kinematics/SwerveDriveKinematics.h>
#include <units/velocity.h>

#define FRONT_RIGHT  0
#define FRONT_LEFT  1
#define BACK_RIGHT  2
#define BACK_LEFT  3

#define k_DB (double)0.07
/**
 * SwerveDrive header file
 *
 * @author 2826WaveRobotics
 */
class SwerveDrive: public frc2::SubsystemBase {
    // It's desirable that everything possible is private except
    // for methods that implement subsystem capabilities
    private:        

        rev::CANSparkMax *m_rightBottomMotor;
        rev::CANSparkMax *m_rightTopMotor;
        rev::CANSparkMax *m_leftBottomMotor;
        rev::CANSparkMax *m_leftTopMotor;
        rev::CANSparkMax *m_pointBottomMotor;
        rev::CANSparkMax *m_pointTopMotor;

        frc::SwerveDriveKinematics<3> *m_kinematics;

        SwervePod *m_rightPod;
        SwervePod *m_leftPod;
        SwervePod *m_pointPod;

        // motor currents;
        double m_leftPodTopMotorCurrent = 0.0;
        double m_leftPodBottomMotorCurrent = 0.0;
        double m_rightPodTopMotorCurrent = 0.0;
        double m_rightPodBottomMotorCurrent = 0.0;
        double m_pointPodTopMotorCurrent = 0.0;
        double m_pointPodBottomMotorCurrent = 0.0;

        double m_leftPodOffsetAngle = 107.0;
        double m_rightPodOffsetAngle = 124.0;
        double m_pointPodOffsetAngle = -11.0;
        double leftOffset;
        double rightOffset;
        double pointOffset;

    public:
        // length of the intake side
        const double robotWidth = 0.717;
        // length of the point to the midpoint of the intake side
        const double robotHeight = 0.617;

        SwerveDrive();

        void Periodic() override;
        void SimulationPeriodic() override;

        /**
         * Function that takes inputs from the joysticks and transforms
         * the inputs into states (speed, angle) that individual swerve modules will utilize
         * 
         * @param foward joystick input from left x-axis (LX)
         * @param strafe joystick input from left y-axis (LY)
         * @param rotation joystick input from right x-axis (RX)
         **/
        void DrivePods(double forward, double strafe, double rotation);

        double GetLeftPodOffsetAngle();
        double GetRightPodOffsetAngle();
        double GetPointPodOffsetAngle();

        /**
         * Function that gets the current of a given pod and motor in amps
         * 
         * @param pod which pod you want to queery
         * rght: 0
         * left: 1
         * point: 2
         * @param motor which motor you want to get the current from
         * bottom: 0
         * top: 1
        */
        double GetPodCurrent(int pod, bool motor);

        void SetLeftPodOffsetAngle(double offsetAngle);
        void SetRightPodOffsetAngle(double offsetAngle);
        void SetPointPodOffsetAngle(double offsetAngle);  

        void initialize();
        
};

