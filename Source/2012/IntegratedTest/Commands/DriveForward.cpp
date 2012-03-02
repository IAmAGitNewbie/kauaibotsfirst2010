#include "DriveForward.h"
#include <math.h>
#include "JoystickConstants.h"
#include <Timer.h>


DriveForward::DriveForward() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(drive);
}

// Called just before this Command runs the first time
void DriveForward::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void DriveForward::Execute() {
	int x=1;
	int y=-1;
	int z=1;
	drive->DoMecanum(x,y,z);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveForward::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveForward::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveForward::Interrupted() {
}
