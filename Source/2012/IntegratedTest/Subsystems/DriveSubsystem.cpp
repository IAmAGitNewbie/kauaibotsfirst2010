#include "DriveSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/Drive.h"
#include <math.h>

static SEM_ID cAutoRotateSemaphore = semBCreate (SEM_Q_PRIORITY, SEM_FULL);

#define DEGREES_IN_A_CIRCLE     360
const float cDefaultLowGearRatio = .15;

DriveSubsystem::DriveSubsystem() : 
        PIDSubsystem(   "DriveSubsystem",
                                        Preferences::GetInstance()->GetDouble("DriveAutoRotate_P",0.024),
                                        Preferences::GetInstance()->GetDouble("DriveAutoRotate_I",0.0012),
                                        Preferences::GetInstance()->GetDouble("DriveAutoRotate_D",0.00) ),
        drive(  LEFT_FRONT_CAN_ADDRESS,
                        RIGHT_FRONT_CAN_ADDRESS,
                        LEFT_REAR_CAN_ADDRESS,
                        RIGHT_REAR_CAN_ADDRESS,
                        CANJaguar::kSpeed,
                        Preferences::GetInstance()->GetInt("DriveMaxRPMs", DEFAULT_MAX_RPMS) ),
        frontRanger(FRONT_RANGEFINDER_CHANNEL),
        rightRanger(RIGHT_RANGEFINDER_CHANNEL),
        rearRanger(REAR_RANGEFINDER_CHANNEL),
        leftRanger(LEFT_RANGEFINDER_CHANNEL),
        frontEdgeFinder(DRIVE_FRONT_EDGEFINDER_CHANNEL),
        rightEdgeFinder(DRIVE_RIGHT_EDGEFINDER_CHANNEL),
        rearEdgeFinder(DRIVE_REAR_EDGEFINDER_CHANNEL),
        leftEdgeFinder(DRIVE_LEFT_EDGEFINDER_CHANNEL)
#ifndef USE_MINIIMU9AHRS
        ,yaw(DRIVE_YAW_GYRO_CHANNEL),
        pitch(DRIVE_PITCH_GYRO_CHANNEL),
        accelerometer(ACCELEROMETER_DSC_MODULE)
#endif
{       
        m_UpdateDashboardCount = 0;
        m_UpdateDashboardRate = 4;
        m_LowGearRatio = Preferences::GetInstance()->GetFloat("DriveLowGearRatio",cDefaultLowGearRatio);
        SetDriveGear(DriveSubsystem::kHighGear);
        InitializeSensors();
        
        // Initialize the Auto-rotation feature
        
    m_bAutoRotationMode = false;
    m_pendingAutoRotateAmount = 0.0;
    
    GetPIDController()->SetInputRange(0, DEGREES_IN_A_CIRCLE);  // NOTE:  Used to be -360 to 360
    GetPIDController()->SetContinuous(true);                                    // TODO:  Review this
    
    double dPIDOutputRange = Preferences::GetInstance()->GetDouble("DriveMaxAutoRotateSpeed", .85);
    
    GetPIDController()->SetOutputRange((dPIDOutputRange*-1), dPIDOutputRange);    // TODO:  Depends upon speed v. voltage mode
    // TODO:  Review this  
    // Tolerance (15.0 = 15%) of the allowable error
    // in the input range.
    //
    // So given a 360 degree input range, a one degree of tolerance
    // would be 1/(360/100)in the PIDController's calculation of OnTarget()
    double dToleranceInDegrees = Preferences::GetInstance()->GetDouble("DriveAutoRotateToleranceInDegrees", 1.0);
    double dToleranceInPercent = dToleranceInDegrees / (double(DEGREES_IN_A_CIRCLE) / double(100));
    GetPIDController()->SetTolerance( dToleranceInPercent );     
}
    
void DriveSubsystem::InitializeSensors()
{
    // Gyroscopes
        //         
        // Gyro is initialized, including calibration, in constructor
        //         
        // Initialize sensivity of the AD22305 Gyroscope         
#ifndef USE_MINIIMU9AHRS
		yaw.SetSensitivity(.007);       
        pitch.SetSensitivity(.007);      
        yaw.Reset();
        pitch.Reset();
        accelerometer.SetEnabled(true);
#endif
}

void DriveSubsystem::InitDefaultCommand() {
        // Set the default command for a subsystem here.
        SetDefaultCommand(new Drive());
}

//
// NOTE:  If in percentVBus mode, x,y,rot are values from -1 to 1
//        If in speed mode, x,y,rot are values from -RPM_MAX to +RPM_MAX

void DriveSubsystem::DoMecanum( float vX, float vY, float vRot )
{
        if ( m_DriveGear == DriveSubsystem::kLowGear )
        {
                vX              = vX   * m_LowGearRatio;
                vY              = vY   * m_LowGearRatio;
                vRot    		= vRot * m_LowGearRatio;
        }
        
    if ( m_bAutoRotationMode )         
    {                 
        vRot = ThreadSafeGetAutoRotateMotorOutputValue();                 
        vRot *= -1;     // Invert value before sending to the output.                                  
        //printf("AutoRotate:  %f [Error:  %f] %s\n",(double)vRot, (double)GetPIDController()->GetError(), GetPIDController()->OnTarget() ? "On Target" : "");
    }
        
        drive.DoMecanum( vX, vY, vRot );
        
        // Periodically update the dashboard w/sensors
        int iIteration = ( m_UpdateDashboardCount % m_UpdateDashboardRate );
        UpdateDashboardWithSensors(iIteration);
        m_UpdateDashboardCount++;
}
CANJaguar::ControlMode DriveSubsystem::GetControlMode()
{
        return drive.GetMode();
}

void DriveSubsystem::SetControlMode( CANJaguar::ControlMode newMode )
{
        drive.SetMode( newMode );
}

void DriveSubsystem::GetEulerAnglesDegrees( double& pitchAngle, double& rollAngle, double& yawAngle)
{
#ifndef USE_MINIIMU9AHRS
        yawAngle        = ClipGyroAngle(yaw.GetAngle());
        pitchAngle      = ClipGyroAngle(pitch.GetAngle());
        rollAngle		= 0.0;
#else        
        imu.GetEulerAnglesDegrees(pitchAngle,rollAngle,yawAngle);
#endif
}

void DriveSubsystem::GetDeltaEulerAnglesDegrees( double& pitchAngle, double& rollAngle, double& yawAngle)
{
#ifndef USE_MINIIMU9AHRS
        yawAngle        = 0;
        pitchAngle      = 0;
        rollAngle		= 0;
#else        
        imu.GetDeltaEulerAnglesDegrees(pitchAngle,rollAngle,yawAngle);
#endif	
}
void DriveSubsystem::GetAngularVelocityDegreesPerSec( double& x, double& y, double& z)
{
#ifndef USE_MINIIMU9AHRS
	x = y = z = 0.0;
#else
	imu.GetAngularVelocityDegreesPerSec( x, y, z );
#endif
}

void DriveSubsystem::GetRangesInches( double& frontRange, double& rightRange, double& rearRange, double& leftRange )
{
        frontRange      = frontRanger.GetRangeInches();
        rightRange      = rightRanger.GetRangeInches();
        rearRange       = rearRanger.GetRangeInches();
        leftRange       = leftRanger.GetRangeInches();
}

void DriveSubsystem::GetEdges( bool &frontEdge, bool& rightEdge, bool& rearEdge, bool& leftEdge)
{
        frontEdge       = (frontEdgeFinder.Get() != 0);
        rightEdge       = (rightEdgeFinder.Get() != 0);
        rearEdge        = (rearEdgeFinder.Get() != 0);
        leftEdge        = (leftEdgeFinder.Get() != 0);
}

double DriveSubsystem::ClipGyroAngle( double dInputAngle )
{
        // The angle from the Gyro is continuous, that is can go beyond 
        // 360 degrees. The DriveSubystem wants a continuous angle-space that
        // wraps at 0 degrees.
        
        double dOutputAngle = 0.0;
        
    if ( dInputAngle >= double(DEGREES_IN_A_CIRCLE) )         
    {                 
        int divisor = (int)(dInputAngle / (double)DEGREES_IN_A_CIRCLE);
        dOutputAngle = dInputAngle - (divisor * DEGREES_IN_A_CIRCLE);         
    }         
    else if ( dInputAngle <= double(-DEGREES_IN_A_CIRCLE) )         
    {                 
        int divisor = (int)(dInputAngle / (double)-DEGREES_IN_A_CIRCLE);                 
        dOutputAngle = dInputAngle + (divisor * DEGREES_IN_A_CIRCLE);                     
    }   
    return dOutputAngle;
}

double DriveSubsystem::ReturnPIDInput()
{
	double pitchAngle, rollAngle, yawAngle;
	GetEulerAnglesDegrees(pitchAngle,rollAngle,yawAngle);
    return ClipGyroAngle( yawAngle );
}

// NOTE:  This method is invoked by the PID controller, and occurs on a 
// timer interrupt - thus any variables it accesses needs to be 
// made thread-safe.

void DriveSubsystem::UsePIDOutput( double dOutputValue )
{
        ThreadSafeSetAutoMotorOutputValue( dOutputValue );
}

float DriveSubsystem::ThreadSafeGetAutoRotateMotorOutputValue() 
{         
        Synchronized sync(cAutoRotateSemaphore);         
        float autoRotateAmount = m_pendingAutoRotateAmount;         
        return autoRotateAmount; 
}  

void DriveSubsystem::ThreadSafeSetAutoMotorOutputValue( float rotOutput ) 
{         
        Synchronized sync(cAutoRotateSemaphore);         
        m_pendingAutoRotateAmount = rotOutput; 
}  

void DriveSubsystem::SetAutoRotationMode( bool bEnable, double dTargetAngle ) 
{         
        if ( bEnable != m_bAutoRotationMode )         
        {                 
                m_bAutoRotationMode = bEnable;                 
                ThreadSafeSetAutoMotorOutputValue(0);     // Always reset rotation amount                  
                
                if ( bEnable )
                {
                        GetPIDController()->SetSetpoint(dTargetAngle);
                        GetPIDController()->Enable();
                }
                else
                {
                        // TODO:  Review this:  is it preferable to invoke Reset() or Disable() on the 
                        // PID Controller?
                        GetPIDController()->Reset();
                }
        } 
}  

bool DriveSubsystem::GetAutoRotationMode() 
{         
        return m_bAutoRotationMode; 
}

bool DriveSubsystem::GetAutoRotationTargetReadings( bool& bOnTarget, double& dSetPoint, double& dAngularError )
{
        if ( !m_bAutoRotationMode ) return false;
        
        bOnTarget = GetPIDController()->OnTarget();
        dSetPoint = GetPIDController()->GetSetpoint();
        dAngularError = GetPIDController()->GetError();
        return true;
}

void DriveSubsystem::SetDriveGear( DriveSubsystem::DriveGear gear )
{
        m_DriveGear = gear;
}

DriveSubsystem::DriveGear DriveSubsystem::GetDriveGear()
{
        return m_DriveGear;
}

void DriveSubsystem::UpdateDashboardWithSensors( int iIteration )
{
        SmartDashboard *pDashboard = SmartDashboard::GetInstance();
        if ( pDashboard )
        {
        	if ( iIteration == 0 )
        	{
            	double pitch, roll, yaw;
            	pitch = roll = yaw = 0.0;
            	GetEulerAnglesDegrees( pitch, roll, yaw );
                //pDashboard->PutDouble(  "YawAngle",             yaw);
                
            	pDashboard->PutDouble(  "PitchAngle",           pitch);
                pDashboard->PutDouble(  "RollAngle",            roll);

                double deltaPitch, deltaRoll, deltaYaw;
                GetDeltaEulerAnglesDegrees( deltaPitch, deltaRoll, deltaYaw );
                
            	pDashboard->PutDouble(  "DeltaPitchAngle",           deltaPitch);
                pDashboard->PutDouble(  "DeltaRollAngle",            deltaRoll);                
 
                double velX, velY, velZ;
                GetAngularVelocityDegreesPerSec( velX, velY, velZ );
                
                pDashboard->PutDouble(	"AngVelX",					velX );
                pDashboard->PutDouble(	"AngVelY",					velY );
                
                /*
                pDashboard->PutDouble(  "FrontRange",           frontRanger.GetRangeInches());
                pDashboard->PutDouble(  "RightRange",           rightRanger.GetRangeInches());
                pDashboard->PutDouble(  "RearRange",            rearRanger.GetRangeInches());
                pDashboard->PutDouble(  "LeftRange",            leftRanger.GetRangeInches());
                */
                
                /*
                pDashboard->PutBoolean( "FrontEdge",            (frontEdgeFinder.Get() != 0));
                pDashboard->PutBoolean( "RightEdge",            (rightEdgeFinder.Get() != 0));
                pDashboard->PutBoolean( "RearEdge",             (rearEdgeFinder.Get() != 0));
                pDashboard->PutBoolean( "LeftEdge",             (leftEdgeFinder.Get() != 0));
                */
                
                /*if ( iIteration == 0 )
                {
					pDashboard->PutDouble(  "MotorAmps_FL",         drive.FrontLeftMotor().GetOutputCurrent());     
					pDashboard->PutDouble(  "MotorAmps_FR",         drive.FrontRightMotor().GetOutputCurrent());    
					pDashboard->PutDouble(  "MotorAmps_RR",         drive.RearRightMotor().GetOutputCurrent());     
					pDashboard->PutDouble(  "MotorAmps_RL",         drive.RearLeftMotor().GetOutputCurrent());      
					pDashboard->PutDouble(  "WheelRPM_FL",          drive.FrontLeftMotor().GetSpeed());     
					pDashboard->PutDouble(  "WheelRPM_FR",          drive.FrontRightMotor().GetSpeed());    
					pDashboard->PutDouble(  "WheelRPM_RR",          drive.RearRightMotor().GetSpeed());     
					pDashboard->PutDouble(  "WheelRPM_RL",          drive.RearLeftMotor().GetSpeed());      
                }*/
                
                /*double accelX, accelY, accelZ = 0;
                GetAccelerationGs( accelX, accelY, accelZ );
                pDashboard->PutDouble(  "Acceleration_X",       accelX);
                pDashboard->PutDouble(  "Acceleration_Y",       accelY);
                pDashboard->PutDouble(  "Acceleration_Z",       accelZ);*/
        	}
        }
}

void DriveSubsystem::GetMotorCurrentAmps( double& frontLeft, double& frontRight, double& rearRight, double& rearLeft )
{
        frontLeft       = drive.FrontLeftMotor().GetOutputCurrent();
        frontRight      = drive.FrontRightMotor().GetOutputCurrent();
        rearRight       = drive.RearRightMotor().GetOutputCurrent();
        rearLeft        = drive.RearLeftMotor().GetOutputCurrent();     
}

void DriveSubsystem::GetWheelSpeedsRPM( double& frontLeft, double& frontRight, double& rearRight, double& rearLeft )
{
        frontLeft       = drive.FrontLeftMotor().GetSpeed();
        frontRight      = drive.FrontRightMotor().GetSpeed();
        rearRight       = drive.RearRightMotor().GetSpeed();
        rearLeft        = drive.RearLeftMotor().GetSpeed();
}

void DriveSubsystem::GetAccelerationGs( double& accelX, double& accelY, double& accelZ )
{
#ifndef USE_MINIIMU9AHRS
	accelerometer.GetAccelGs( accelX, accelY, accelZ );
#else
	imu.GetAccelGs( accelX, accelY, accelZ );
#endif
}

void DriveSubsystem::ResetSensors()
{
#ifndef USE_MINIIMU9AHRS	
        accelerometer.SetEnabled(false);
        accelerometer.Calibrate();
        accelerometer.SetEnabled(true);
        ResetGyros();
#else
#endif
}

void DriveSubsystem::ResetGyros()
{
#ifndef USE_MINIIMU9AHRS	
    yaw.Reset();
    pitch.Reset();	
#else
#endif
}

double DriveSubsystem::GetSecondsToTravelLinearDistance( bool x, double distanceInches, double RPMs )
{
	double wheelCircumference = double(3.1415926) * wheelDiameter;
    if ( x )
	{	
		// Side-to-side motion takes twice the time as forward-reverse, due to
		// the offsetting forces required to mecanum.
		return (double(60) / ((wheelCircumference * RPMs) / fabs(distanceInches))) * 2;
	}
	else
	{
		return (double(60) / ((wheelCircumference * RPMs) / fabs(distanceInches)));		
	}
}

void DriveSubsystem::GetWheelVelocitiesRatio( float& x, float& y, float& rot )
{
	double frontLeftRPM;
	double frontRightRPM;
	double rearRightRPM;
	double rearLeftRPM;
	
	GetWheelSpeedsRPM( frontLeftRPM, frontRightRPM, rearRightRPM, rearLeftRPM );
	
	// convert wheel speeds in RPMs to a ratio
	double maxRPMs = GetSpeedModeMaxRPMs();
	
	// Note that Mecanum drive uses order:  FL, FR, RL, RR - a different order than this class.
	float driveSpeeds[4];
	driveSpeeds[0] = frontLeftRPM/maxRPMs;
	driveSpeeds[1] = frontRightRPM/maxRPMs;
	driveSpeeds[2] = rearLeftRPM/maxRPMs;
	driveSpeeds[3] = rearRightRPM/maxRPMs;
	
	// Run the forward kinematics to derive the x, y and rot velocities (ratios)
	float velocities[3];
	drive.MecanumDriveFwdKinematics( driveSpeeds, velocities );
	
    x = velocities[0];
	y = velocities[1];
	rot = velocities[2];
}

