// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// Java from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


package org.usfirst.frc2465.Robot.commands;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;
import org.usfirst.frc2465.Robot.Robot;
import org.usfirst.frc2465.Robot.RobotPreferences;
import org.usfirst.frc2465.Robot.subsystems.Kicker;
import org.usfirst.frc2465.Robot.subsystems.Tensioner;

/**
 *
 */
public class  Kick extends Command {

    public final int kStateInitial = 0;
    public final int kStateTriggerMotorStarted = 1;
    public final int kStateTriggerMotorStopped = 2;
    public final int kStateDone = 3;    
    
    int state;
    
    double start;
    double trigger_motor_start;
    double settle_period_start;
    boolean m_droparms;
    
    public Kick(boolean droparms) {
        m_droparms = droparms;
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
        requires(Robot.kicker);
        // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    }

    // Called just before this Command runs the first time
    protected void initialize() {
        state = kStateInitial;
        if(m_droparms == true) {
            Robot.arms.disable();
            Robot.arms.startArmsDown();
            Robot.arms.setSetpoint(RobotPreferences.getArmsVoltsHandoff());
            Robot.arms.getPIDController().setPID(
                    RobotPreferences.getArmsPHandoff(),
                    RobotPreferences.getArmsIHandoff(),
                    RobotPreferences.getArmsDHandoff());
        }
        start = Timer.getFPGATimestamp();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
        switch ( state ) {
            case kStateInitial:
                if ( Robot.kicker.isLegLatchedAndRetractorReady() &&
                     Robot.kicker.isBallPresent() ) {
                    //if ( ( Timer.getFPGATimestamp() - start ) > 0.1 ) {
                        trigger_motor_start = Timer.getFPGATimestamp();
                        Robot.kicker.startTriggerMotor();
                        state = kStateTriggerMotorStarted;
                   // }
                } else {
                    state = kStateDone;
                }
                break;
            case kStateTriggerMotorStarted:
                if ( ( ( Timer.getFPGATimestamp() - trigger_motor_start ) > 0.2 ) && 
                        !Robot.kicker.isLegLatched() ) {
                    Robot.kicker.stopTriggerMotor();
                    state = kStateTriggerMotorStopped;
                    settle_period_start = Timer.getFPGATimestamp();
                }
                break;
            case kStateTriggerMotorStopped:
                // Wait 1 second for robot to settle
                if ( ( Timer.getFPGATimestamp() - settle_period_start ) > 1 ) {
                    state = kStateDone;
                }
                break;
            case kStateDone:
                break;
        }        
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return (state == kStateDone);
    }

    // Called once after isFinished returns true
    protected void end() {
        Robot.kicker.stopTriggerMotor();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
        Robot.kicker.stopTriggerMotor();
    }
}
