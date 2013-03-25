// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.




#include "Tilter.h"
#include "../Robot.h"
#include "../Robotmap.h"
#include <math.h>


Tilter::Tilter(double p,double i,double d) : PIDSubsystem("Tilter",p,i,d) {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	height_sensor = RobotMap::tilterheight_sensor;
	motor = RobotMap::tiltermotor;
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}
    
void Tilter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new SetShooterTiltAngleDegrees());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	//SetDefaultCommand(new SetShooterTiltAngleDegrees());
}

void Tilter::UsePIDOutput(double output){
	motor->Set(-output);
}

double Tilter::ReturnPIDInput(){
	double theta,X;
	X=height_sensor->GetDistanceMM();
	X=X*0.0393701;//converts mm to inches
	theta = atan2((TILTER_HEIGHT_INCHES+X),TILTER_BASELINE_INCHES);
	theta=theta*(180.0/3.1415926);
	return theta;
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

