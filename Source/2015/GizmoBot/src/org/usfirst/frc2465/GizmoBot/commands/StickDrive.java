// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// Java from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


package org.usfirst.frc2465.GizmoBot.commands;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.command.Command;
import org.usfirst.frc2465.GizmoBot.Robot;
import org.usfirst.frc2465.GizmoBot.RobotMap;

/**
 *
 */
public class  StickDrive extends Command {

    static final double DEADZONE = .06;
    
    public class JoystickResponseCurve {
        double adjust;
        double power;
        double multiplier;
        double deadzone;
        
        public JoystickResponseCurve( double adj, double pow, double mult, double dead ) {
            adjust = adj;
            power = pow;
            multiplier = mult;
            deadzone = dead;
        }
        
        // f(x) = multiplier * (adjust * x^power+(1-adjust)*x)
        
        public double transform( double input ) {
            double output = 0.0;
            if ( ( input > deadzone ) || ( input < (-1 * deadzone ) ) ) {
                output = multiplier * ( adjust * Math.pow(input, power) + (1-adjust) * input );
            }
            return output;
        }
    }
    
    public class JoystickResponseCurveSet {
        JoystickResponseCurve fwd;
        JoystickResponseCurve strafe;
        JoystickResponseCurve rotate;
        
        public JoystickResponseCurveSet(
            JoystickResponseCurve fwd,
            JoystickResponseCurve strafe,
            JoystickResponseCurve rotate ) {
            this.fwd = fwd;
            this.strafe = strafe;
            this.rotate = rotate;
        }
        
        public double transformForward( double input )  { return fwd.transform(input); }
        public double transformStrafe( double input )   { return strafe.transform(input); }
        public double transformRotate( double input )   { return rotate.transform(input); }
    }
        
    JoystickResponseCurveSet linear = new JoystickResponseCurveSet(
            new JoystickResponseCurve( .00, 3, 1.0, DEADZONE ),
            new JoystickResponseCurve( .00, 3, 1.0, DEADZONE ),
            new JoystickResponseCurve( .00, 3, 1.0, DEADZONE ) );
    
    JoystickResponseCurveSet conservative = new JoystickResponseCurveSet(
            new JoystickResponseCurve( .40, 3, .50, DEADZONE ),
            new JoystickResponseCurve( .40, 3, .50, DEADZONE ),
            new JoystickResponseCurve( .40, 3, .35, DEADZONE ) );

    JoystickResponseCurveSet aggressive = new JoystickResponseCurveSet(
            new JoystickResponseCurve( .40, 3, 1.0, DEADZONE ),
            new JoystickResponseCurve( .40, 3, 1.0, DEADZONE ),
            new JoystickResponseCurve( .40, 3, 1.0, DEADZONE ) );
    
    JoystickResponseCurveSet aggressive_medium_rot = new JoystickResponseCurveSet(
            new JoystickResponseCurve( .40, 3, .75, DEADZONE ),
            new JoystickResponseCurve( .40, 3, .75, DEADZONE ),
            new JoystickResponseCurve( .40, 3, .35, DEADZONE ) );

    JoystickResponseCurveSet conservative_slow_rot = new JoystickResponseCurveSet(
            new JoystickResponseCurve( .40, 3, .125, DEADZONE ),
            new JoystickResponseCurve( .40, 3, .125, DEADZONE ),
            new JoystickResponseCurve( .40, 3, .06, DEADZONE ) );
    
    
    public StickDrive() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
	requires(Robot.drive);
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
        // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
        
        JoystickResponseCurveSet current;
        Joystick driver = Robot.oi.driver;
        Joystick op = Robot.oi.opJoystick;

        if ( driver.getRawButton(1) ) {
        	current = aggressive_medium_rot;
        } else {
        	current = conservative_slow_rot;
        }
        
        double vX = driver.getY();
        double vY = driver.getX();
        double vRot = driver.getRawAxis(3);
                         
        vX = current.transformStrafe(vX);
        vY = current.transformForward(vY);
        vRot = current.transformRotate(vRot);
        
        if ( driver.getRawButton(4) )
        {
        	if ( RobotMap.imu != null ) {
	            RobotMap.imu.zeroYaw();
        	}
        }
        
        if ( driver.getRawButton(5))
        {
            Robot.drive.setFODEnabled(true);
        }
        if ( driver.getRawButton(6))
        {
            Robot.drive.setFODEnabled(false);
        }
        if ( op.getRawButton(7))
        {
        	Robot.drive.setAutoRotation(true);
        	Robot.drive.setSetpoint(-90.0);
        }
        else if ( op.getRawButton(8))
        {
        	Robot.drive.setAutoRotation(true);
        	Robot.drive.setSetpoint(-179.0);
        }
        else if ( op.getRawButton(9))
        {
        	Robot.drive.setAutoRotation(true);
        	Robot.drive.setSetpoint(90.0);
        }
        else if ( op.getRawButton(10))
        {
        	Robot.drive.setAutoRotation(true);
        	Robot.drive.setSetpoint(0.0);
        }
        else if (driver.getRawButton(3))
        {
        	Robot.drive.setAutoRotation(true);
        	Robot.drive.setSetpoint(135.0);	
        }
        else if (driver.getRawButton(2))
        {
        	Robot.drive.setAutoRotation(true);
        	Robot.drive.setSetpoint(-135.0);	
        }
        
        else
        {
        	Robot.drive.setAutoRotation(false);
        }
        
        if(RobotMap.robotDrive != null)
        {
        	Robot.drive.doMecanum(vY,vX,vRot);
        }
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
