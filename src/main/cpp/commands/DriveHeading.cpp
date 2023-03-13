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

#include "commands/DriveHeading.h"
#include "commands/WaveWaitCommand.h"

DriveHeading::DriveHeading(SwerveDrive* swerveDrive, double inputLX, double inputLY, double inputRX, double targetYaw, units::second_t timeout)
                      : WaitCommand(timeout), m_swerveDrive(swerveDrive), m_inputLX(inputLX),
                        m_inputLY(inputLY), m_inputRX(inputRX), m_targetYaw(targetYaw), m_timeout(timeout)
{

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("DriveHeading");
    m_timeout = timeout;
}

// Called just before this Command runs the first time
void DriveHeading::Initialize() {
    WaitCommand::Initialize();
}

// Called repeatedly when this Command is scheduled to run
void DriveHeading::Execute() {
    // m_swerveDrive->DrivePods(m_inputLX, m_inputLY, m_inputRX);
    // double topMotorSpeed = 0.0;
    // double bottomMotorSpeed = 0.0;

    // // tracking angles
    // // pod state angle (target) is -180 to 180
    // // encoder angle (current) is 0 - 360
    // // offsetAngle adjusts "forward" to align to position on robot
    // double current_angle = m_offsetAngle + ToDegree(m_podEncoder->GetAbsolutePosition());
    // // double current_angle = ToDegree(m_podEncoder->GetAbsolutePosition());
    // double target_angle;
    // if (!GetIsReversed()) {
    //     target_angle = state.angle.Degrees().value() + 180.0;

    // } else {
    //     target_angle = state.angle.Degrees().value() + 360.0;
    //     if (target_angle >= 360) {
    //         target_angle -= 360.0;
    //     }
    // }

    // if (target_angle < 0) {
    //     target_angle += 360;
    // }
    
    // // conversion from input state speed (rpm) to a motor power % val (0-1)
    // double commanded_speed = (state.speed.value() / 5200.0);
    // if (1 < commanded_speed)
    // {
    //     commanded_speed = 1;
    // }

    // double angle_delta = target_angle - current_angle;
    // if (angle_delta > 180.0)
    // {
    //     angle_delta -= 360.0;
    // }
    // else if (angle_delta < -180.00)
    // {
    //     angle_delta += 360.0;
    // }
    // double angle_delta_optimized = 0.0;
    // double normalizer = 1 / 180.0;
    // std::string swerveCase = "DID NOT ENTER";

    // if (fabs(angle_delta) < 30.0)
    // {
    //     // tuning factor is the P in PID (if we decide to use it)
    //     // double tunedAngleDelta = angle_delta * turnTuningFactor;

    //     // check aligned
    //     swerveCase = "ALIGNED";

    //     // station keep alg
    //     double stationKeepTop;
    //     double stationKeepBottom;
    //     double divisor;
    //     if (GetIsReversed())
    //     {
    //         stationKeepTop = (1.0 - angle_delta * normalizer);
    //         stationKeepBottom = (1.0 + angle_delta * normalizer);
    //     }
    //     else
    //     {            
    //         // stationKeepTop = (1 + tunedAngleDelta * normalizer);
    //         // stationKeepBottom = (1 - tunedAngleDelta * normalizer);
    //         stationKeepTop = (1.0 + angle_delta * normalizer);
    //         stationKeepBottom = (1.0 - angle_delta * normalizer);
    //     }
    //     if (fabs(stationKeepTop) > fabs(stationKeepBottom))
    //     {
    //         divisor = stationKeepTop / stationKeepBottom;
    //     }
    //     else
    //     {
    //         divisor = stationKeepBottom / stationKeepTop;
    //     }

    //     if (!GetIsReversed())
    //     {
    //         topMotorSpeed = -commanded_speed * (stationKeepTop / divisor);
    //         bottomMotorSpeed = -commanded_speed * (stationKeepBottom / divisor);
    //     }
    //     else
    //     {
    //         topMotorSpeed = commanded_speed * (stationKeepTop / divisor);
    //         bottomMotorSpeed = commanded_speed * (stationKeepBottom / divisor);
    //     }
    // }
    // else if (angle_delta < -90.0)
    // {
    //     // check optimal path
    //     swerveCase = "OPTIMIZE < -90";

    //     FlipIsReversed();
    //     if (!GetIsReversed())
    //     {
    //         angle_delta_optimized = (angle_delta - 180.0);
    //     }
    //     else
    //     {
    //         angle_delta_optimized = (angle_delta + 180.0);
    //     }

    //     topMotorSpeed = commanded_speed * angle_delta_optimized * normalizer;
    //     bottomMotorSpeed = -commanded_speed * angle_delta_optimized * normalizer;
    // }
    // else if (angle_delta > 90.0)
    // {
    //     // check optimal path
    //     swerveCase = "OPTIMIZE > 90";

    //     FlipIsReversed();
    //     if (!GetIsReversed())
    //     {
    //         angle_delta_optimized = (angle_delta - 180.0);
    //     }
    //     else
    //     {
    //         angle_delta_optimized = (angle_delta + 180.0);
    //     }

    //     topMotorSpeed = -commanded_speed * angle_delta_optimized * normalizer;
    //     bottomMotorSpeed = commanded_speed * angle_delta_optimized * normalizer;
    // }
    // else
    // {
    //     swerveCase = "ROTATE";

    //     // min max functions to add (P) of PID
    //     // if ( angle_delta < 0 ) {
    //     //     // angle delta is negative
    //     //     topMotorSpeed = -commanded_speed * (std::min(-turnTuningFactor, angle_delta * normalizer));
    //     //     bottomMotorSpeed = commanded_speed * (std::min(-turnTuningFactor, angle_delta * normalizer));
    //     // } else {
    //     //     // angle delta is positive
    //     //     topMotorSpeed = -commanded_speed * (std::max(turnTuningFactor, angle_delta * normalizer));
    //     //     bottomMotorSpeed = commanded_speed * (std::max(turnTuningFactor, angle_delta * normalizer));
    //     // }

    //     topMotorSpeed = -commanded_speed * angle_delta * normalizer;
    //     bottomMotorSpeed = commanded_speed * angle_delta * normalizer;        
    // }

    // // assign motor speeds
    // m_topMotor->Set(topMotorSpeed);
    // m_bottomMotor->Set(bottomMotorSpeed);
}

// Make this return true when this Command no longer needs to run execute()
// bool DriveHeading::IsFinished() {
//     // m_swerveDrive->DrivePods(0, 0, 0);
//     // return false;
// }

// Called once after isFinished returns true
void DriveHeading::End(bool interrupted) {
    WaitCommand::End(interrupted);
    m_swerveDrive->DrivePods(0, 0, 0, nullptr);
}

bool DriveHeading::RunsWhenDisabled() const {
    return false;

}
