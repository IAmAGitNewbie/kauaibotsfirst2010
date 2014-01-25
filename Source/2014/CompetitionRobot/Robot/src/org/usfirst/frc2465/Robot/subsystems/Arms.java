// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// Java from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.
package org.usfirst.frc2465.Robot.subsystems;
import org.usfirst.frc2465.Robot.RobotMap;
import org.usfirst.frc2465.Robot.commands.*;
import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.command.Subsystem;
/**
 *
 */
public class Arms extends Subsystem {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    SpeedController leftElbowSC = RobotMap.armsLeftElbowSC;
    DigitalInput leftElbowMin = RobotMap.armsLeftElbowMin;
    DigitalInput leftElbowMax = RobotMap.armsLeftElbowMax;
    AnalogChannel leftElbowSensor = RobotMap.armsLeftElbowSensor;
    SpeedController rightElbowSC = RobotMap.armsRightElbowSC;
    DigitalInput rightElbowMin = RobotMap.armsRightElbowMin;
    DigitalInput rightElbowMax = RobotMap.armsRightElbowMax;
    AnalogChannel rightElbowSensor = RobotMap.armsRightElbowSensor;
    DoubleSolenoid shoulderSolenoid = RobotMap.armsShoulderSolenoid;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    
    // Put methods for controlling this subsystem
    // here. Call these from Commands.
    public void initDefaultCommand() {
        shoulderSolenoid.startLiveWindowMode();
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    }
    public void openShoulder() {
        shoulderSolenoid.set(DoubleSolenoid.Value.kReverse);
    }
    public void closeShoulder() {
        shoulderSolenoid.set(DoubleSolenoid.Value.kForward);
    }
    public void raiseToTop() {
        
    }
    public void goToMiddle() {
        
    }
    public void lowerToBottom() {
    
}
}