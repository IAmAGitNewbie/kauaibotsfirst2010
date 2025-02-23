// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// Java from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


package org.usfirst.frc2465.GizmoBot.commands;

import edu.wpi.first.wpilibj.command.Command;
import org.usfirst.frc2465.GizmoBot.Robot;

/**
 *
 */
public class  SteerTopCam extends Command {

    public SteerTopCam() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
        requires(Robot.topCam);

        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	double value_h = Robot.oi.opJoystick.getRawAxis(0);
    	Robot.topCam.setHorizontal(value_h);
    	
    	double value_v = Robot.oi.opJoystick.getRawAxis(1);
    	Robot.topCam.setHorizontal(value_v);
    	
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    }
}
