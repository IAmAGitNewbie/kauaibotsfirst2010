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

import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.command.Command;
import org.usfirst.frc2465.Robot.Robot;
import org.usfirst.frc2465.Robot.RobotPreferences;
import org.usfirst.frc2465.Robot.subsystems.Arms;

/**
 *
 */
public class  ArmsHandoff extends Command {

    
    public ArmsHandoff() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
	
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
        // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    }

    // Called just before this Command runs the first time
    
    protected void initialize() {
        Robot.arms.disable();        
        Robot.arms.setSetpoint(RobotPreferences.getArmsVoltsHandoff());
        Robot.arms.getPIDController().setPID(
                                RobotPreferences.getArmsPHandoff(),
                                RobotPreferences.getArmsIHandoff(),
                                RobotPreferences.getArmsDHandoff());
        Robot.arms.enable();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return Robot.arms.onTarget();
    }

    // Called once after isFinished returns true
    protected void end() {
        Robot.arms.disable();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    }
}
