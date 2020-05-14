#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define BNO055ADDR 0x28

// This program communicates the raspberry pi to the BNO055 absolute angle sensor
// The program sets up the sensor and then gets the euler angles and converts them to degrees

int main(void)
{
	uint8_t config[1]; // stores the data for setup and configuration
	uint8_t euler[6]; // stores the raw euler angles from the sensor

	int16_t anglesLSB[3]; // stores the euler angles in LSB

	double angles[3]; // stores the euler angles in degrees

	// connect I2C to the device
	bno = wiringPiI2CSetup(BNO055ADDR);

	// reset the BNO055 by sending 0x20 to the system trigger register 0x3F
	*config = 0x20;
	wiringPiI2CWriteReg8(bno, 0x3F, *config);
	delay(1000); // wait for one second while sensor reboots

	// set to normal power mode by sending 0x00 to the power mode register 0x3E
	// I am pretty sure this is not needed
	*config = 0x00;
	wiringPiI2CWriteReg8(bno, 0x3E, *config);
	delay(50);

	// set trigger register back to normal (I am pretty sure this is not needed as well)
	*config = 0x00;
	wiringPiI2CWriteReg8(bno, 0x3F, *config);
	delay(50);

	// set operating mode to NDOF (outputs euler angles) 0x0C -> 0x3D
	*config = 0x0C;
	wiringPiI2CWriteReg8(bno, 0x3D, *config);
	delay(50);

	// infinite loop for getting data
	while(1)
	{
		// read x, y, and z euler registers
		euler[0] = wiringPiI2CReadReg16(bno, 0x1A);
		euler[2] = wiringPiI2CReadReg16(bno, 0x1C);
		euler[4] = wiringPiI2CReadReg16(bno, 0x1E);

		// convert raw data to angles in LSB
		anglesLSB[0] = ((int16_t) euler[0]) | (((int16_t) euler[1]) << 8);
		anglesLSB[1] = ((int16_t) euler[2]) | (((int16_t) euler[3]) << 8);
		anglesLSB[2] = ((int16_t) euler[4]) | (((int16_t) euler[5]) << 8);

		// convert from LSB to degrees
		angles[0] = ((double) anglesLSB[0]) / 16.0;
		angles[1] = ((double) anglesLSB[1]) / 16.0;
		angles[2] = ((double) anglesLSB[2]) / 16.0;

		// print angles
		printf("X: %0.2f Y: %0.2f Z: %0.2f", angles[0], angles[1], angles[2]);
	}
	return;
}




