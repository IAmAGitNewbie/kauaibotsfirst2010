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
    
import com.kauailabs.nav6.frc.BufferingSerialPort;
import com.kauailabs.nav6.frc.IMUAdvanced;
import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.camera.AxisCamera;
import edu.wpi.first.wpilibj.can.*;

import edu.wpi.first.wpilibj.livewindow.LiveWindow;
import edu.wpi.first.wpilibj.util.UncleanStatusException;
import edu.wpi.first.wpilibj.visa.VisaException;
import java.util.Vector;
import org.usfirst.frc2465.Robot.subsystems.ProximitySensor;
import org.usfirst.frc2465.Robot.subsystems.UltrasonicSensor;

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
public class RobotMap {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    public static CANJaguar driveLeftFrontSC;
    public static CANJaguar driveLeftRearSC;
    public static CANJaguar driveRightFrontSC;
    public static CANJaguar driveRightRearSC;
    public static RobotDrive driveRobotDrive;
    public static DigitalInput legLatched;
    public static DigitalInput legReady;
    public static DigitalInput triggerReady;
    public static SpeedController legSC;
    public static SpeedController tensionerLeftSC;
    public static DigitalInput tensionerLeftMin;
    public static DigitalInput tensionerLeftMax;
    public static AnalogChannel tensionerSensor;
    public static Relay legTriggerMotorRelay;
    public static SpeedController armsSC;
    public static DigitalInput armsMin;
    public static DigitalInput armsMax;
    public static AnalogChannel armsSensor;
    public static UltrasonicSensor wallRangerSensor;
    public static ProximitySensor ballRangerSensor;
    public static ProximitySensor ballPresentSensor;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    public static BufferingSerialPort serialPort;
    public static IMUAdvanced imu;
    public static AxisCamera camera;          // the axis camera object (connected to the switch)

    public static void init() {
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
        
        try { 
            driveLeftFrontSC = new CANJaguar(3);
        } catch (CANTimeoutException ex) {
            // This exception occurs if the Jaguar cannot be 
            // reached on the CAN Bus
            ex.printStackTrace();
        } catch (UncleanStatusException ex) {
            // This exception occurs in case of 
            // communication error with the CAN Bridge
            ex.printStackTrace();
        }
        
        try { 
            driveLeftRearSC = new CANJaguar(4);
        } catch (CANTimeoutException ex) {
            ex.printStackTrace();
        } catch (UncleanStatusException ex) {
            ex.printStackTrace();
        }
	
        
        try { 
            driveRightFrontSC = new CANJaguar(2);
        } catch (CANTimeoutException ex) {
            ex.printStackTrace();
        } catch (UncleanStatusException ex) {
            ex.printStackTrace();
        }
	
        
        try { 
            driveRightRearSC = new CANJaguar(5);
        } catch (CANTimeoutException ex) {
            ex.printStackTrace();
        } catch (UncleanStatusException ex) {
            ex.printStackTrace();
        }

        try {
        driveRobotDrive = new RobotDrive(driveLeftFrontSC, driveLeftRearSC,
              driveRightFrontSC, driveRightRearSC);
            driveRobotDrive.setSafetyEnabled(false);
            driveRobotDrive.setExpiration(0.1);
            driveRobotDrive.setSensitivity(0.5);
            driveRobotDrive.setMaxOutput(1.0);        
        } catch(NullPointerException ex) {
            System.out.println("WARNING:  COuld not initialize drive system!");
        }
        
        legLatched = new DigitalInput(1, 11);
	LiveWindow.addSensor("Leg", "Latched", legLatched);
        
        legReady = new DigitalInput(1, 5);
	LiveWindow.addSensor("Leg", "Ready", legReady);
        
        triggerReady = new DigitalInput(1, 6);
	LiveWindow.addSensor("Leg", "TriggerReady", triggerReady);        
        
        legSC = new Talon(1, 4);
	LiveWindow.addActuator("Leg", "LegMotor", (Talon)legSC);
        
        tensionerLeftSC = new Talon(1, 1);
	LiveWindow.addActuator("Tensioner", "LeftSC", (Talon) tensionerLeftSC);
        
        tensionerLeftMin = new DigitalInput(1, 3);
	LiveWindow.addSensor("Tensioner", "LeftMin", tensionerLeftMin);
        
        tensionerLeftMax = new DigitalInput(1, 4);
	LiveWindow.addSensor("Tensioner", "LeftMax", tensionerLeftMax);
        
        tensionerSensor = new AnalogChannel(1, 2);
	LiveWindow.addSensor("Tensioner", "LeftDistance", tensionerSensor);
        
        legTriggerMotorRelay = new Relay(1, 3);
        legTriggerMotorRelay.setDirection (Relay.Direction.kBoth);

	LiveWindow.addActuator("Leg", "TriggerMotorRelay", legTriggerMotorRelay);
        
        armsSC = new Talon(1, 3);
	LiveWindow.addActuator("Arms", "SC", (Talon) armsSC);
        
        armsMin = new DigitalInput(1, 7);
	LiveWindow.addSensor("Arms", "Min", armsMin);
        
        armsMax = new DigitalInput(1, 8);
	LiveWindow.addSensor("Arms", "Max", armsMax);
        
        armsSensor = new AnalogChannel(1, 4);
	LiveWindow.addSensor("Arms", "Sensor", armsSensor);
        
        wallRangerSensor = new UltrasonicSensor(1, 6);
	LiveWindow.addSensor("WallRanger", "Sensor", wallRangerSensor);
        
        ballRangerSensor = new ProximitySensor(1, 7, ProximitySensor.kLongRange);
	LiveWindow.addSensor("BallRanger", "Sensor", ballRangerSensor);
        
        ballPresentSensor = new ProximitySensor(1, 3, ProximitySensor.kShortRange);
	LiveWindow.addSensor("BallRanger", "BallPresentSensor", ballPresentSensor);
        
        // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

        try {
            serialPort = new BufferingSerialPort(57600);
            
            // You can add a second parameter to modify the 
            // update rate (in hz) from 4 to 100.  The default is 100.
            // If you need to minimize CPU load, you can set it to a
            // lower value, as shown here, depending upon your needs.
            
            // You can also use the IMUAdvanced class for advanced
            // features.

            byte update_rate_hz = 20;
            imu = new IMUAdvanced(serialPort,update_rate_hz);
        } catch (VisaException ex) {
            ex.printStackTrace();
        }
        if ( imu != null ) {
            LiveWindow.addSensor("IMU", "Gyro", imu);
        }

        //camera = AxisCamera.getInstance();
    }
}
