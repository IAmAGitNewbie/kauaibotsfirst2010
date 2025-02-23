#ifndef __constants_h__
#define __constants_h__

///////////////////////////////////////////////////////////f
// Robot-specific measurements (in units of inches)
///////////////////////////////////////////////////////////
//WHARRGARBL
const float cWidth                      = 19.0;                                 // Distance between left/right wheels
const float cLength                     = 22.25;                                // Distance btwn front/back wheels
const float wheelDiameter       = 8.0;                                  // Per AndyMark Specs
const float wheelRadius         = wheelDiameter / 2;

/////////////////////////////////////////////////////////////////////////////////////
// Movement Modifiers
/////////////////////////////////////////////////////////////////////////////////////
#define ROTATE_DIRECTION -1
#define DRIVE_DIRECTION -1
/////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
// Dashboard Constants 
/////////////////////////////////////////////////////////////////////////////////////

#define Dashboard_Status                        "Status"                        // Type:  String
#define Dashboard_Joystick1_X           "Joystick1_X"           // Type:  double
#define Dashboard_Joystick1_Y           "Joystick1_Y"           // Type:  double
#define Dashboard_Joystick1_Twist       "Joystick1_Twist"       // Type:  double
#define FrontLeftEncoderSpeed       "FrontLeftEncoder"
#define FrontRightEncoderSpeed      "FrontRightEncoder"
#define RearLeftEncoderSpeed        "RearLeftEncoder"
#define RearRightEncoderSpeed       "RearRightEncoder"
#define FrontLeftMotorFaults            "FrontLeftFaults"
#define FrontRightMotorFaults           "FrontRightFaults"
#define RearLeftMotorFaults                     "RearLeftFaults"
#define RearRightMotorFaults            "RearRightFaults"
#define FrontLeftMotorSetting           "FrontLeftSetting"
#define FrontRightMotorSetting          "FrontRightSetting"
#define RearLeftMotorSetting            "RearLeftSetting"
#define RearRightMotorSetting           "RearRightSetting"
#define FrontLeftMotorP                         "FrontLeftMotorP"
#define FrontRightMotorP                        "FrontRightMotorP"
#define RearLeftMotorP                          "RearLeftMotorP"
#define RearRightMotorP                         "RearRightMotorP"

/////////////////////////////////////////////////////////////////////////////////////
// Mecanum Constants
/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// Proportional translation vs. Rotation
//
// For the same motor speed, the distance of translation and distance of rotation
// are not the same, due to the proportions of the wheel radius, and the 
// distance between front/back and left/right wheels.
//////////////////////////////////////////////////////////

const float cRotK = ((cWidth + cLength)/2) / wheelRadius;               // Rotational Coefficient

//////////////////////////////////////////////////////////
// Forward and Inverse Kinematics Matrices
//
// As document on p. 523 of Omnidirectional Mobile Robot - Design and Implementation
// (Ioan Doroftei, Victor Grosu and Veaceslav Spinu).
//
// A nominal value of 1 is used for translational motion.  
//
// NOTE:  These matrices assume the roller direction of each wheel points to the
// center of the robot.
// The AndyMark documentation indicates an alternative configuration, where each wheel's
// Axis points to the center of the robot.  This alternative configuration modifies the
// Matrices below by swapping the front and rear wheels.
//////////////////////////////////////////////////////////

const int WHEEL_FRONTLEFT       = 2;
const int WHEEL_FRONTRIGHT      = 3;
const int WHEEL_REARLEFT        = 4;
const int WHEEL_REARRIGHT       = 5;

const int VX    = 0;
const int VY    = 1;
const int VROT  = 2;

#define ROLLERS_ROTATE_TO_ROBOT_CENTER 1

const float invMatrix[4][3] = 
{ 
#ifdef ROLLERS_ROTATE_TO_ROBOT_CENTER
        {  -1, 1,  cRotK },
        {   1, 1, -cRotK },
        {   1, 1,  cRotK },
        {  -1, 1, -cRotK },
#else
        {   1, 1,  cRotK },
        {  -1, 1, -cRotK },
        {  -1, 1,  cRotK },
        {   1, 1, -cRotK },
#endif
};
/////////////////////////////////////////////////////////////////////////////////////

#endif
