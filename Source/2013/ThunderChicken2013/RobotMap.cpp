// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.

#include "Robot.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
Servo* RobotMap::cameraazimuth_servo = NULL;
Servo* RobotMap::cameraelevation_servo = NULL;
SpeedController* RobotMap::shootermotor = NULL;
DoubleSolenoid* RobotMap::magazinetrigger = NULL;
DoubleSolenoid* RobotMap::magazinelifter = NULL;
ProximitySensor* RobotMap::rearhookheight_sensor = NULL;
Compressor* RobotMap::pneumaticscompressor = NULL;
ProximitySensor* RobotMap::tilterheight_sensor = NULL;
SpeedController* RobotMap::tiltermotor = NULL;
SpeedController* RobotMap::climberfront_winch_motor = NULL;
SpeedController* RobotMap::climberrear_winch_motor = NULL;
SpeedController* RobotMap::swerveDriveSystemleft_front_steer_motor = NULL;
AngleSensor* RobotMap::swerveDriveSystemleft_front_angle_sensor = NULL;
PIDController* RobotMap::swerveDriveSystemleft_front_steer = NULL;
Encoder* RobotMap::swerveDriveSystemleft_front_rpm_sensor = NULL;
SpeedController* RobotMap::swerveDriveSystemleft_front_drive_motor = NULL;
PIDController* RobotMap::swerveDriveSystemleft_front_drive = NULL;
SpeedController* RobotMap::swerveDriveSystemright_front_steer_motor = NULL;
AngleSensor* RobotMap::swerveDriveSystemright_front_angle_sensor = NULL;
PIDController* RobotMap::swerveDriveSystemright_front_steer = NULL;
Encoder* RobotMap::swerveDriveSystemright_front_rpm_sensor = NULL;
SpeedController* RobotMap::swerveDriveSystemright_front_drive_motor = NULL;
PIDController* RobotMap::swerveDriveSystemright_front_drive = NULL;
SpeedController* RobotMap::swerveDriveSystemleft_back_steer_motor = NULL;
AngleSensor* RobotMap::swerveDriveSystemleft_back_angle_sensor = NULL;
PIDController* RobotMap::swerveDriveSystemleft_back_steer = NULL;
Encoder* RobotMap::swerveDriveSystemleft_back_rpm_sensor = NULL;
SpeedController* RobotMap::swerveDriveSystemleft_back_drive_motor = NULL;
PIDController* RobotMap::swerveDriveSystemleft_back_drive = NULL;
SpeedController* RobotMap::swerveDriveSystemright_back_steer_motor = NULL;
AngleSensor* RobotMap::swerveDriveSystemright_back_angle_sensor = NULL;
PIDController* RobotMap::swerveDriveSystemright_back_steer = NULL;
SpeedController* RobotMap::swerveDriveSystemright_back_drive_motor = NULL;
Encoder* RobotMap::swerveDriveSystemright_back_rpm_sensor = NULL;
PIDController* RobotMap::swerveDriveSystemright_back_drive = NULL;
SerialPort *RobotMap::imu_serial_port = NULL;
Solenoid* RobotMap::front_climber_solenoid = NULL;
IMU *RobotMap::imu = NULL;
double RobotMap::tilter_p = 0;
double RobotMap::tilter_i = 0;
double RobotMap::tilter_d = 0;

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {

	Preferences *prefs = Preferences::GetInstance();
	
	tilter_p  = prefs->GetDouble("Tilt_P", .5);
	tilter_i = prefs->GetDouble("Tilt_I", 0.0);
	tilter_d = prefs->GetDouble("Tilt_D", 0.0);
	
	double steer_P = prefs->GetDouble("Steer_P", .022);/*.02);*/
	double steer_I = prefs->GetDouble("Steer_I", .000);/*0.002);*/
	double steer_D = prefs->GetDouble("Steer_D", .006);/*0.001);*/
	
	double drive_P = prefs->GetDouble("Drive_P", 1.0);
	double drive_I = prefs->GetDouble("Drive_I", 0.0);
	double drive_D = prefs->GetDouble("Drive_D", 0.0);
	double drive_F = prefs->GetDouble("Drive_F", 0.0);
	
	double steer_L_F_offset_angle = prefs->GetDouble("L_F_Steer_Offset_Angle", -126.0);
	double steer_L_B_offset_angle = prefs->GetDouble("L_B_Steer_Offset_Angle", -70.0);
	double steer_R_F_offset_angle = prefs->GetDouble("R_F_Steer_Offset_Angle", 170.0);
	double steer_R_B_offset_angle = prefs->GetDouble("R_B_Steer_Offset_Angle", -140.0);	

	prefs->PutDouble("L_F_Steer_Offset_Angle", steer_L_F_offset_angle);
	prefs->PutDouble("L_B_Steer_Offset_Angle", steer_L_B_offset_angle);
	prefs->PutDouble("R_F_Steer_Offset_Angle", steer_R_F_offset_angle);
	prefs->PutDouble("R_B_Steer_Offset_Angle", steer_R_B_offset_angle);
	
	prefs->Save();
	
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	LiveWindow* lw = LiveWindow::GetInstance();

	cameraazimuth_servo = new Servo(1, 5);
	lw->AddActuator("Camera", "azimuth_servo", cameraazimuth_servo);
	
	cameraelevation_servo = new Servo(1, 6);
	lw->AddActuator("Camera", "elevation_servo", cameraelevation_servo);
	
	shootermotor = new Jaguar(2, 1);
	lw->AddActuator("Shooter", "motor", (Jaguar*) shootermotor);
	
	magazinetrigger = new DoubleSolenoid(1, 1, 2); 
	lw->AddActuator("Magizine", "trigger", magazinetrigger);
	
	magazinelifter = new DoubleSolenoid(1, 3, 4);      
	lw->AddActuator("Magizine", "lifter", magazinelifter);
	
	rearhookheight_sensor = new ProximitySensor(1, 2, ProximitySensor::kShortRange);
	lw->AddSensor("Climber", "fronthook_height_sensor", rearhookheight_sensor);
	
	pneumaticscompressor = new Compressor(2, 1, 2, 1);
	pneumaticscompressor->Start();
	
	tilterheight_sensor = new ProximitySensor(1, 1, ProximitySensor::kShortRange);
	lw->AddSensor("Tilter", "height_sensor", tilterheight_sensor);
	
	tiltermotor = new Jaguar(2, 4);
	lw->AddActuator("Tilter", "motor", (Jaguar*) tiltermotor);
	
	climberfront_winch_motor = new Jaguar(2, 2);
	lw->AddActuator("Climber", "front_winch_motor", (Jaguar*) climberfront_winch_motor);
	
	climberrear_winch_motor = new Jaguar(2, 3);
	lw->AddActuator("Climber", "rear_winch_motor", (Jaguar*) climberrear_winch_motor);
	
	/* Swerve Drive Left Front */
	
	swerveDriveSystemleft_front_steer_motor = new Talon(1, 9);
	lw->AddActuator("SwerveDriveSystem_L_F", "steer_motor", (Talon*) swerveDriveSystemleft_front_steer_motor);
	
	swerveDriveSystemleft_front_angle_sensor = new AngleSensor(1, 12, 14, 13, steer_L_F_offset_angle);
	lw->AddSensor("SwerveDriveSystem_L_F", "angle_sensor", swerveDriveSystemleft_front_angle_sensor);
	
	swerveDriveSystemleft_front_steer = new PIDController(steer_P, steer_I, steer_D,/* F: 0.0, */ swerveDriveSystemleft_front_angle_sensor, swerveDriveSystemleft_front_steer_motor, 0.02);
	lw->AddActuator("SwerveDriveSystem_L_F", "steer_controller", swerveDriveSystemleft_front_steer);
	swerveDriveSystemleft_front_steer->SetContinuous(true); swerveDriveSystemleft_front_steer->SetAbsoluteTolerance(0.2); 
		swerveDriveSystemleft_front_steer->SetInputRange(-180.0, 180.0);
        swerveDriveSystemleft_front_steer->SetOutputRange(-1.0, 1.0);
        //swerveDriveSystemleft_front_steer->SetTolerance(1.0/360.0);
	swerveDriveSystemleft_front_rpm_sensor = new Encoder(1, 11, 1, 10, false, Encoder::k1X);
	lw->AddSensor("SwerveDriveSystem_L_F", "rpm_sensor", swerveDriveSystemleft_front_rpm_sensor);
	swerveDriveSystemleft_front_rpm_sensor->SetDistancePerPulse(1.0);
        swerveDriveSystemleft_front_rpm_sensor->SetPIDSourceParameter(Encoder::kRate);
        swerveDriveSystemleft_front_rpm_sensor->Start();
	swerveDriveSystemleft_front_drive_motor = new Talon(1, 10);
	lw->AddActuator("SwerveDriveSystem_L_F", "drive_motor", (Talon*) swerveDriveSystemleft_front_drive_motor);
	
	swerveDriveSystemleft_front_drive = new PIDController(drive_P, drive_I, drive_D, drive_F, swerveDriveSystemleft_front_rpm_sensor, swerveDriveSystemleft_front_drive_motor, 0.02);
	lw->AddActuator("SwerveDriveSystem_L_F", "drive_controller", swerveDriveSystemleft_front_drive);
	swerveDriveSystemleft_front_drive->SetContinuous(false); swerveDriveSystemleft_front_drive->SetAbsoluteTolerance(0.2); 
        swerveDriveSystemleft_front_drive->SetOutputRange(-1.0, 1.0);
        
    /* Swerve Drive Right-Front */        
        
	swerveDriveSystemright_front_steer_motor = new Talon(2, 7);
	lw->AddActuator("SwerveDriveSystem_R_F", "steer_motor", (Talon*) swerveDriveSystemright_front_steer_motor);
	
	swerveDriveSystemright_front_angle_sensor = new AngleSensor(2, 7, 9, 8, steer_R_F_offset_angle);
	lw->AddSensor("SwerveDriveSystem_R_F", "angle_sensor", swerveDriveSystemright_front_angle_sensor);
	
	swerveDriveSystemright_front_steer = new PIDController(steer_P, steer_I, steer_D,/* F: 0.0, */ swerveDriveSystemright_front_angle_sensor, swerveDriveSystemright_front_steer_motor, 0.02);
	lw->AddActuator("SwerveDriveSystem_R_F", "steer_controller", swerveDriveSystemright_front_steer);
	swerveDriveSystemright_front_steer->SetContinuous(true); swerveDriveSystemright_front_steer->SetAbsoluteTolerance(0.2); 
    	swerveDriveSystemright_front_steer->SetInputRange(-180.0, 180.0);
        swerveDriveSystemright_front_steer->SetOutputRange(-1.0, 1.0);
        //swerveDriveSystemright_front_steer->SetTolerance(1.0/360.0);
	swerveDriveSystemright_front_rpm_sensor = new Encoder(2, 6, 2, 5, false, Encoder::k1X);
	lw->AddSensor("SwerveDriveSystem_R_F", "rpm_sensor", swerveDriveSystemright_front_rpm_sensor);
	swerveDriveSystemright_front_rpm_sensor->SetDistancePerPulse(1.0);
        swerveDriveSystemright_front_rpm_sensor->SetPIDSourceParameter(Encoder::kRate);
        swerveDriveSystemright_front_rpm_sensor->Start();
	swerveDriveSystemright_front_drive_motor = new Talon(2, 8);
	lw->AddActuator("SwerveDriveSystem_R_F", "drive_motor", (Talon*) swerveDriveSystemright_front_drive_motor);
	
	swerveDriveSystemright_front_drive = new PIDController(drive_P, drive_I, drive_D, drive_F, swerveDriveSystemright_front_rpm_sensor, swerveDriveSystemright_front_drive_motor, 0.02);
	lw->AddActuator("SwerveDriveSystem_R_F", "drive_controller", swerveDriveSystemright_front_drive);
	swerveDriveSystemright_front_drive->SetContinuous(false); swerveDriveSystemright_front_drive->SetAbsoluteTolerance(0.2); 
        swerveDriveSystemright_front_drive->SetOutputRange(-1.0, 1.0);
        
    /* Swerve Drive Left Back */
        
	swerveDriveSystemleft_back_steer_motor = new Talon(1, 7);
	lw->AddActuator("SwerveDriveSystem_L_B", "steer_motor", (Talon*) swerveDriveSystemleft_back_steer_motor);
	
	swerveDriveSystemleft_back_angle_sensor = new AngleSensor(1, 7, 9, 8, steer_L_B_offset_angle);
	lw->AddSensor("SwerveDriveSystem_L_B", "angle_sensor", swerveDriveSystemleft_back_angle_sensor);
	
	swerveDriveSystemleft_back_steer = new PIDController(steer_P, steer_I, steer_D,/* F: 0.0, */ swerveDriveSystemleft_back_angle_sensor, swerveDriveSystemleft_back_steer_motor, 0.02);
	lw->AddActuator("SwerveDriveSystem_L_B", "steer_controller", swerveDriveSystemleft_back_steer);
	swerveDriveSystemleft_back_steer->SetContinuous(true); swerveDriveSystemleft_back_steer->SetAbsoluteTolerance(0.2); 
    	swerveDriveSystemleft_back_steer->SetInputRange(-180.0, 180.0);
        swerveDriveSystemleft_back_steer->SetOutputRange(-1.0, 1.0);
        //swerveDriveSystemleft_back_steer->SetTolerance(1.0/360.0);
	swerveDriveSystemleft_back_rpm_sensor = new Encoder(1, 6, 1, 5, false, Encoder::k1X);
	lw->AddSensor("SwerveDriveSystem_L_B", "rpm_sensor", swerveDriveSystemleft_back_rpm_sensor);
	swerveDriveSystemleft_back_rpm_sensor->SetDistancePerPulse(1.0);
        swerveDriveSystemleft_back_rpm_sensor->SetPIDSourceParameter(Encoder::kRate);
        swerveDriveSystemleft_back_rpm_sensor->Start();
	swerveDriveSystemleft_back_drive_motor = new Talon(1, 8);
	lw->AddActuator("SwerveDriveSystem_L_B", "drive_motor", (Talon*) swerveDriveSystemleft_back_drive_motor);
	
	swerveDriveSystemleft_back_drive = new PIDController(drive_P, drive_I, drive_D, drive_F, swerveDriveSystemleft_back_rpm_sensor, swerveDriveSystemleft_back_drive_motor, 0.02);
	lw->AddActuator("SwerveDriveSystem_L_B", "drive_controller", swerveDriveSystemleft_back_drive);
	swerveDriveSystemleft_back_drive->SetContinuous(false); swerveDriveSystemleft_back_drive->SetAbsoluteTolerance(0.2); 
        swerveDriveSystemleft_back_drive->SetOutputRange(-1.0, 1.0);
        
    /* Swerve Drive Right Back */        
        
	swerveDriveSystemright_back_steer_motor = new Talon(2, 9);
	lw->AddActuator("SwerveDriveSystem_R_B", "steer_motor", (Talon*) swerveDriveSystemright_back_steer_motor);
	
	swerveDriveSystemright_back_angle_sensor = new AngleSensor(2, 12, 14, 13, steer_R_B_offset_angle);
	lw->AddSensor("SwerveDriveSystem_R_B", "angle_sensor", swerveDriveSystemright_back_angle_sensor);
	
	swerveDriveSystemright_back_steer = new PIDController(steer_P, steer_I, steer_D,/* F: 0.0, */ swerveDriveSystemright_back_angle_sensor, swerveDriveSystemright_back_steer_motor, 0.02);
	lw->AddActuator("SwerveDriveSystem_R_B", "steer_controller", swerveDriveSystemright_back_steer);
	swerveDriveSystemright_back_steer->SetContinuous(true); swerveDriveSystemright_back_steer->SetAbsoluteTolerance(0.2); 
    	swerveDriveSystemright_back_steer->SetInputRange(-180.0, 180.0);
        swerveDriveSystemright_back_steer->SetOutputRange(-1.0, 1.0);
        //swerveDriveSystemright_back_steer->SetTolerance(1.0/360.0);
	swerveDriveSystemright_back_drive_motor = new Talon(2, 10);
	lw->AddActuator("SwerveDriveSystem_R_B", "drive_motor", (Talon*) swerveDriveSystemright_back_drive_motor);
	
	swerveDriveSystemright_back_rpm_sensor = new Encoder(2, 11, 2, 10, false, Encoder::k1X);
	lw->AddSensor("SwerveDriveSystem_R_B", "rpm_sensor", swerveDriveSystemright_back_rpm_sensor);
	swerveDriveSystemright_back_rpm_sensor->SetDistancePerPulse(1.0);
        swerveDriveSystemright_back_rpm_sensor->SetPIDSourceParameter(Encoder::kRate);
        swerveDriveSystemright_back_rpm_sensor->Start();
	swerveDriveSystemright_back_drive = new PIDController(drive_P, drive_I, drive_D, drive_F, swerveDriveSystemright_back_rpm_sensor, swerveDriveSystemright_back_drive_motor, 0.02);
	lw->AddActuator("SwerveDriveSystem_R_B", "drive_controller", swerveDriveSystemright_back_drive);
	swerveDriveSystemright_back_drive->SetContinuous(false); swerveDriveSystemright_back_drive->SetAbsoluteTolerance(0.2); 
        swerveDriveSystemright_back_drive->SetOutputRange(-1.0, 1.0);

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
        
    imu_serial_port = new SerialPort(57600);
    imu = new IMU(imu_serial_port);
    
	lw->AddSensor("SwerveDriveSystem", "Gyro", imu);
    
    front_climber_solenoid = new Solenoid(1,5);
    lw->AddSensor("Climber", "solenoid", front_climber_solenoid);    
}
