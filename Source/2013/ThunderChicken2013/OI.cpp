// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.


#include "OI.h"
#include "RobotMap.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/ZeroYaw.h"
#include "Commands/FODEnableDisable.h"
#include "Commands/LowerAllHooks.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/AutoDrive.h"
#include "Commands/AutoFire.h"
#include "Commands/AutoTilt.h"
#include "Commands/DeployChute.h"
#include "Commands/DisableShooterDriveControl.h"
#include "Commands/EnableShooterDriveControl.h"
#include "Commands/FireFrisbee.h"
#include "Commands/LowerRearClimberHook.h"
#include "Commands/RaiseRearClimberHook.h"
#include "Commands/SetShooterRPM.h"
#include "Commands/SetShooterTiltAngleDegrees.h"
#include "Commands/UndeployChute.h"
#include "Commands/FireAtWill.h"
#include "Commands/AutoRev.h"
#include "Joystick.h"

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
	// Process operator interface input here.
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

	driver_joystick = new Joystick(1);	
	shooter_joystick = new Joystick(2);

	// Driver Joystick Command Mapping
	
	disable_shooter_drive_control = new JoystickButton(driver_joystick, 1);
	disable_shooter_drive_control->WhenReleased(new DisableShooterDriveControl());
	enable_shooter_drive_control = new JoystickButton(driver_joystick, 1);
	enable_shooter_drive_control->WhenPressed(new EnableShooterDriveControl());
     
	rear_climber_hook_up = new JoystickButton(driver_joystick, 4);
	rear_climber_hook_up->WhenPressed(new RaiseRearClimberHook());
	rear_climber_hook_down = new JoystickButton(driver_joystick, 2);
	rear_climber_hook_down->WhenPressed(new LowerRearClimberHook());
	
	// Shooter Joystick Command Mapping
	
	fire_frisbee = new JoystickButton(shooter_joystick, 1);
	fire_frisbee->WhenPressed(new FireFrisbee());

	pyramid_prep = new JoystickButton(shooter_joystick, 7);
	pyramid_prep->WhileHeld(new FireAtWill(Pyramid));
	mid_prep = new JoystickButton(shooter_joystick, 8);
	mid_prep->WhileHeld(new FireAtWill(Midcourt));
	long_prep =  new JoystickButton(shooter_joystick, 9);
	long_prep->WhileHeld(new FireAtWill(Backcourt));
	
	shooter_100_percent = new JoystickButton(shooter_joystick,5);
	shooter_100_percent->WhileHeld(new AutoRev(1.0));
	shooter_75_percent = new JoystickButton(shooter_joystick,3);
	shooter_75_percent->WhileHeld(new AutoRev(.75));

	/* 5 is 100%*/
	/* 3 is 75%*/
	

        // SmartDashboard Buttons
	/*SmartDashboard::PutData("FireFrisbee", new FireFrisbee());

	SmartDashboard::PutData("DeployChute", new DeployChute());

	SmartDashboard::PutData("UndeployChute", new UndeployChute());

	SmartDashboard::PutData("SetShooterRPM", new SetShooterRPM());

	SmartDashboard::PutData("SetShooterTiltAngleDegrees", new SetShooterTiltAngleDegrees());

	SmartDashboard::PutData("RaiseRearClimberHook", new RaiseRearClimberHook());

	SmartDashboard::PutData("LowerRearClimberHook", new LowerRearClimberHook());

	SmartDashboard::PutData("EnableShooterDriveControl", new EnableShooterDriveControl());

	SmartDashboard::PutData("DisableShooterDriveControl", new DisableShooterDriveControl());

	SmartDashboard::PutData("AutonomousCommand", new AutonomousCommand());
	*/
        // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

Joystick* OI::getshooter_joystick() {
	return shooter_joystick;
}

Joystick* OI::getdriver_joystick() {
	return driver_joystick;
}

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
