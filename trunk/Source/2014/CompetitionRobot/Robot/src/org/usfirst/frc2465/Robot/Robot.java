// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// Java from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


package org.usfirst.frc2465.Robot;

import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.DriverStationLCD;
import edu.wpi.first.wpilibj.IterativeRobot;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.command.Scheduler;
import edu.wpi.first.wpilibj.livewindow.LiveWindow;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import org.usfirst.frc2465.Robot.commands.*;
import org.usfirst.frc2465.Robot.subsystems.*;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class Robot extends IterativeRobot {

    Command autonomousCommand;

    public static OI oi;
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    public static Drive drive;
    public static Leg leg;
    public static Ankle ankle;
    public static Tensioner tensioner;
    public static Arms arms;
    public static WallRanger wallRanger;
    public static Camera camera;
    public static BallRanger ballRanger;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    /**
     * This function is run when the robot is first started up and should be
     * used for any initialization code.
     */
    public void robotInit() {
	RobotMap.init();
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
        if ( RobotMap.driveRobotDrive != null ) {
            drive = new Drive();
        }
        leg = new Leg();
        ankle = new Ankle();
        tensioner = new Tensioner();
        arms = new Arms();
        wallRanger = new WallRanger();
        camera = new Camera();
        ballRanger = new BallRanger();
        // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
        // This MUST be here. If the OI creates Commands (which it very likely
        // will), constructing it during the construction of CommandBase (from
        // which commands extend), subsystems are not guaranteed to be
        // yet. Thus, their requires() statements may grab null pointers. Bad
        // news. Don't move it.
        oi = new OI();
	
        // instantiate the command used for the autonomous period
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
        autonomousCommand = new Autonomous();
        // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
        LiveWindow.addActuator("Arms", "PIDController", arms.getPIDController());
        LiveWindow.addActuator("Tensioner", "PIDController", tensioner.getPIDController());
        LiveWindow.addActuator("Ankle", "PIDController", ankle.getPIDController());
        if ( drive != null ) {
            LiveWindow.addActuator("Drive", "PIDController", drive.getPIDController());
        }

    }

    public void autonomousInit() {
        // schedule the autonomous command (example)
        if (autonomousCommand != null) autonomousCommand.start();
    }

    /**
     * This function is called periodically during autonomous
     */
    public void autonomousPeriodic() {
        Scheduler.getInstance().run();
        updateDashboard();
    }

    public void teleopInit() {
	// This makes sure that the autonomous stops running when
        // teleop starts running. If you want the autonomous to 
        // continue until interrupted by another command, remove
        // this line or comment it out.
        if (autonomousCommand != null) autonomousCommand.cancel();
    }

    /**
     * This function is called periodically during operator control
     */
    public void teleopPeriodic() {
        Scheduler.getInstance().run();
        updateDashboard();
    }

    public void disabledPeriodic() {
        
    }
    
    public void testInit() {
        
    }
    
    public void disabledInit() {
        
    }
    
    /**
     * This function called periodically during test mode
     */
    public void testPeriodic() {
        LiveWindow.run();
    }
    
    
    int count = 0;
    public void updateDashboard() {
        SmartDashboard.putBoolean("IMU_Connected", RobotMap.imu.isConnected());
        SmartDashboard.putNumber("IMU_Yaw", RobotMap.imu.getYaw());
        SmartDashboard.putNumber("IMU_Pitch", RobotMap.imu.getPitch());
        SmartDashboard.putNumber("IMU_Roll", RobotMap.imu.getRoll());
        SmartDashboard.putNumber("IMU_CompassHeading", RobotMap.imu.getCompassHeading());
        SmartDashboard.putBoolean("ArmsLow", Robot.arms.getState() == Arms.kStateLow);
        SmartDashboard.putBoolean("ArmsMid", Robot.arms.getState() == Arms.kStateMid);
        SmartDashboard.putBoolean("ArmsHigh", Robot.arms.getState() == Arms.kStateHigh);
        SmartDashboard.putBoolean("ArmsUp", Robot.arms.getState() == Arms.kStateUp);
        SmartDashboard.putBoolean("AnkleReady", Robot.ankle.onTarget());
        SmartDashboard.putBoolean("LegReady", Fire.isLegReady());
        SmartDashboard.putBoolean("AimReady",true /*TODO:  Get value from drive subystem */);
        SmartDashboard.putBoolean("FOD_Enabled", true /*TODO:  Get value from drive subsystem*/);
     }
    
}
