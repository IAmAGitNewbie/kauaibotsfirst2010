#include "LSM303.h"
#include "Wire.h"
#include <math.h>

// Defines ////////////////////////////////////////////////////////////////

// The Arduino two-wire interface uses a 7-bit number for the address, 
// and sets the last bit correctly based on reads and writes
#define MAG_ADDRESS            (0x3C >> 1)
#define ACC_ADDRESS_SA0_A_LOW  (0x30 >> 1)
#define ACC_ADDRESS_SA0_A_HIGH (0x32 >> 1)

// NOTE from MiniIMU9AHRS Board datasheet:
//
// SAO_A - Accelerometer I�C slave address least significant bit; pulled low by default.
// Most applications can leave this pin disconnected.
//
// Thus, if this pin were to be low, the I2C GYR_ADDRESS would be (0xD0 >> 1)

// Constructors ////////////////////////////////////////////////////////////////

LSM303::LSM303(void)
{
	// These are just some values for a particular unit; it is recommended that
	// a calibration be done for your particular unit.
	m_max.x = +540; m_max.y = +500; m_max.z = 180;
	m_min.x = -520; m_min.y = -570; m_min.z = -770;
	
	_device = LSM303_DEVICE_AUTO;
	acc_address = ACC_ADDRESS_SA0_A_LOW;
}

// Public Methods //////////////////////////////////////////////////////////////

void LSM303::init(byte device, byte sa0_a)
{	
	_device = device;
	switch (_device)
	{
		case LSM303DLH_DEVICE:
		case LSM303DLM_DEVICE:
			if (sa0_a == LSM303_SA0_A_LOW)
				acc_address = ACC_ADDRESS_SA0_A_LOW;
			else if (sa0_a == LSM303_SA0_A_HIGH)
				acc_address = ACC_ADDRESS_SA0_A_HIGH;
			else
				acc_address = (detectSA0_A() == LSM303_SA0_A_HIGH) ? ACC_ADDRESS_SA0_A_HIGH : ACC_ADDRESS_SA0_A_LOW;
			break;	
		
		case LSM303DLHC_DEVICE:
			acc_address = ACC_ADDRESS_SA0_A_HIGH;
			break;
			
		default:
			// try to auto-detect device
			if (detectSA0_A() == LSM303_SA0_A_HIGH)
			{
				// if device responds on 0011001b (SA0_A is high), assume DLHC
				acc_address = ACC_ADDRESS_SA0_A_HIGH;
				_device = LSM303DLHC_DEVICE;
			}
			else
			{
				// otherwise, assume DLH or DLM (pulled low by default on Pololu boards); query magnetometer WHO_AM_I to differentiate these two
				acc_address = ACC_ADDRESS_SA0_A_LOW;
				_device = (readMagReg(LSM303_WHO_AM_I_M) == 0x3C) ? LSM303DLM_DEVICE : LSM303DLH_DEVICE;
			}
	}
}

// Turns on the LSM303's accelerometer and magnetometers and places them in normal
// mode.
void LSM303::enableDefault(void)
{
	// Enable Accelerometer
	// 0x27 = 0b00100111
	// Normal power mode, all axes enabled
	writeAccReg(LSM303_CTRL_REG1_A, 0x27);
  
	// Enable Magnetometer
	// 0x00 = 0b00000000
	// Continuous conversion mode
	writeMagReg(LSM303_MR_REG_M, 0x00);
}

// Writes an accelerometer register
void LSM303::writeAccReg(byte reg, byte value)
{
	Wire.beginTransmission(acc_address);
	Wire.write(reg);
	Wire.write(value);
	Wire.endTransmission();
}

// Reads an accelerometer register
byte LSM303::readAccReg(byte reg)
{
	byte value;
	
	Wire.beginTransmission(acc_address);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(acc_address, (byte)1);
	value = Wire.read();
	Wire.endTransmission();
	
	return value;
}

// Writes a magnetometer register
void LSM303::writeMagReg(byte reg, byte value)
{
	Wire.beginTransmission(MAG_ADDRESS);
	Wire.write(reg);
	Wire.write(value);
	Wire.endTransmission();
}

// Reads a magnetometer register
byte LSM303::readMagReg(int reg)
{
	byte value;
	
	// if dummy register address (magnetometer Y/Z), use device type to determine actual address
	if (reg < 0)
	{
		switch (reg)
		{
			case LSM303_OUT_Y_H_M:
				reg = (_device == LSM303DLH_DEVICE) ? LSM303DLH_OUT_Y_H_M : LSM303DLM_OUT_Y_H_M;
				break;
			case LSM303_OUT_Y_L_M:
				reg = (_device == LSM303DLH_DEVICE) ? LSM303DLH_OUT_Y_L_M : LSM303DLM_OUT_Y_L_M;
				break;
			case LSM303_OUT_Z_H_M:
				reg = (_device == LSM303DLH_DEVICE) ? LSM303DLH_OUT_Z_H_M : LSM303DLM_OUT_Z_H_M;
				break;
			case LSM303_OUT_Z_L_M:
				reg = (_device == LSM303DLH_DEVICE) ? LSM303DLH_OUT_Z_L_M : LSM303DLM_OUT_Z_L_M;
				break;
		}
	}
	
	Wire.beginTransmission(MAG_ADDRESS);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(MAG_ADDRESS, 1);
	value = Wire.read();
	Wire.endTransmission();
	
	return value;
}

// Reads the 3 accelerometer channels and stores them in vector a
void LSM303::readAcc(void)
{
	Wire.beginTransmission(acc_address);
	// assert the MSB of the address to get the accelerometer 
	// to do slave-transmit subaddress updating.
	Wire.write(LSM303_OUT_X_L_A | (1 << 7)); 
	Wire.endTransmission();
	Wire.requestFrom(acc_address, (byte)6);

	while (Wire.available() < 6);
	
	byte xla = Wire.read();
	byte xha = Wire.read();
	byte yla = Wire.read();
	byte yha = Wire.read();
	byte zla = Wire.read();
	byte zha = Wire.read();

	short x = ( ( ( (unsigned short)xha) << 8 ) | (((unsigned short)xla) & 0x00FF));
	short y = ( ( ( (unsigned short)yha) << 8 ) | (((unsigned short)yla) & 0x00FF));
	short z = ( ( ( (unsigned short)zha) << 8 ) | (((unsigned short)zla) & 0x00FF));
	
	x /= 16;
	y /= 16;
	z /= 16;
	
	/*
	short x = short( ( ((unsigned short)(xha) << 8) | (unsigned short(xla) & 0x00FF) ) >> 4 );
	short y = short( ( (unsigned short(yha) << 8) | (unsigned short(yla) & 0x00FF) ) >> 4 );
	short z = short( ( (unsigned short(zha) << 8) | (unsigned short(zla) & 0x00FF) ) >> 4 );
*/
	a.x = x;  // Convert to float, including sign-extension
	a.y = y;  // Convert to float, including sign-extension
	a.z = z;  // Convert to float, including sign-extension
}

// Reads the 3 magnetometer channels and stores them in vector m
void LSM303::readMag(void)
{
	Wire.beginTransmission(MAG_ADDRESS);
	Wire.write(LSM303_OUT_X_H_M);
	Wire.endTransmission();
	Wire.requestFrom(MAG_ADDRESS, 6);

	while (Wire.available() < 6);

	byte xhm = Wire.read();
	byte xlm = Wire.read();
	
	byte yhm, ylm, zhm, zlm;
	
	if (_device == LSM303DLH_DEVICE)
	{
		// DLH: register address for Y comes before Z
		yhm = Wire.read();
		ylm = Wire.read();
		zhm = Wire.read();
		zlm = Wire.read();
	}
	else
	{
		// DLM, DLHC: register address for Z comes before Y
		zhm = Wire.read();
		zlm = Wire.read();
		yhm = Wire.read();
		ylm = Wire.read();

	}

	short x = ( ( ( (unsigned short)xhm) << 8 ) | (((unsigned short)xlm) & 0x00FF));
	short y = ( ( ( (unsigned short)yhm) << 8 ) | (((unsigned short)ylm) & 0x00FF));
	short z = ( ( ( (unsigned short)zhm) << 8 ) | (((unsigned short)zlm) & 0x00FF));
	
	m.x = x;	// Convert to float, including sign-extension
	m.y = y;	// Convert to float, including sign-extension
	m.z = z;	// Convert to float, including sign-extension
}

// Reads all 6 channels of the LSM303 and stores them in the object variables
void LSM303::read(void)
{
	readAcc();
	readMag();
}

// Returns the number of degrees from the -Y axis that it
// is pointing.
int LSM303::heading(void)
{
	return heading((vector){0,-1,0});
}

// Returns the number of degrees from the From vector projected into
// the horizontal plane is away from north.
// 
// Description of heading algorithm: 
// Shift and scale the magnetic reading based on calibration data to
// to find the North vector. Use the acceleration readings to
// determine the Down vector. The cross product of North and Down
// vectors is East. The vectors East and North form a basis for the
// horizontal plane. The From vector is projected into the horizontal
// plane and the angle between the projected vector and north is
// returned.
int LSM303::heading(vector from)
{
    // shift and scale
    m.x = (m.x - m_min.x) / (m_max.x - m_min.x) * 2 - 1.0;
    m.y = (m.y - m_min.y) / (m_max.y - m_min.y) * 2 - 1.0;
    m.z = (m.z - m_min.z) / (m_max.z - m_min.z) * 2 - 1.0;

    vector temp_a = a;
    // normalize
    vector_normalize(&temp_a);
    //vector_normalize(&m);

    // compute E and N
    vector E;
    vector N;
    vector_cross(&m, &temp_a, &E);
    vector_normalize(&E);
    vector_cross(&temp_a, &E, &N);
	
    // compute heading
    double headingFloatingPoint = atan2(vector_dot(&E, &from), vector_dot(&N, &from)) * double((double(180) / M_PI));
    int heading = int(customround(headingFloatingPoint));
    if (heading < 0) heading += 360;
	return heading;
}

void LSM303::vector_cross(const vector *a,const vector *b, vector *out)
{
  out->x = a->y*b->z - a->z*b->y;
  out->y = a->z*b->x - a->x*b->z;
  out->z = a->x*b->y - a->y*b->x;
}

float LSM303::vector_dot(const vector *a,const vector *b)
{
  return a->x*b->x+a->y*b->y+a->z*b->z;
}

void LSM303::vector_normalize(vector *a)
{
  float mag = sqrt(vector_dot(a,a));
  a->x /= mag;
  a->y /= mag;
  a->z /= mag;
}

// Private Methods //////////////////////////////////////////////////////////////

byte LSM303::detectSA0_A(void)
{
	Wire.beginTransmission(ACC_ADDRESS_SA0_A_LOW);
	Wire.write(LSM303_CTRL_REG1_A);
	Wire.endTransmission();
	Wire.requestFrom(ACC_ADDRESS_SA0_A_LOW, 1);
	if (Wire.available())
	{
		Wire.read();
		return LSM303_SA0_A_LOW;
	}
	else
		return LSM303_SA0_A_HIGH;
}
