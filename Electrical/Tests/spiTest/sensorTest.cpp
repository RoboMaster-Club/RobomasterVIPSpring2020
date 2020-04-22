#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdint.h>

#define LINEAR_ACCEL_RANGE 2 // These are the ranges +/-. for example the range of the linear acceleration is -2 to 2 g
#define GYRO_RANGE 2000

// This program gets acceleration data from the LSM6DS33 accelorometer and prints it out
int main(void)
{
	const int stmPin = 0; // GPIO 0 on raspberry pi, does not correspond to the physical pin 0

	unsigned char data[7]; // holds the data that is sent to and from on SPI
	float linearAccel[3]; // holds the linear acceleration
	float angularAccel[3]; // holds the angular acceleration

	float calcLinearAccel(int16_t, int);
	float calcGyro(int16_t, int);
	int16_t twosComp2ByteToSignedInt(unsigned char *);

	// init wiringPi
	wiringPiSetup();
	// init SPI at channel 0 at 25 mHz clock speed
	wiringPiSPISetup(0, 25000000);
	
	// set the stm32 slave select pin as output and set high
	pinMode(stmPin, OUTPUT);
	digitalWrite(stmPin, HIGH);

	// set up the linear accelerometer
	data[0] = 0b00010000; // write mode to register 0x10 CTRL1_XL
	data[1] = 0b01010000; // set range to 2, 400 Hz, normal mode
	digitalWrite(stmPin, LOW);
	wiringPiSPIDataRW(0, data, 2);
	digitalWrite(stmPin, HIGH);
	delay(20);

	// set up gyro accelerometer
	data[0] = 0b00010001; // write mode to register 0x11 CTRL2_XL
	data[1] = 0b01011100; // set range to 2000, gyro full scale mode off, normal mode
	digitalWrite(stmPin, LOW);
	wiringPiSPIDataRW(0, data, 2);
	digitalWrite(stmPin, HIGH);
	delay(20);
	
	// get the linear acceleration
	data[0] = 0b10101000; // read mode to register 0x28
	digitalWrite(stmPin, LOW);
	wiringPiSPIDataRW(0, data, 7); // although the register holds 6 bytes of acceleration data, 7 bytes are transfered (includes the register address)
	digitalWrite(stmPin, HIGH);
	
	// calculate the linear accel from the data
	linearAccel[0] = calcLinearAccel(twosComp2ByteToSignedInt(&data[1]), LINEAR_ACCEL_RANGE);
	linearAccel[1] = calcLinearAccel(twosComp2ByteToSignedInt(&data[3]), LINEAR_ACCEL_RANGE);
	linearAccel[2] = calcLinearAccel(twosComp2ByteToSignedInt(&data[5]), LINEAR_ACCEL_RANGE);

	// get the gyro acceleration
	data[0] = 0b10100010; // read mode to register 0x22
	digitalWrite(stmPin, LOW);
	wiringPiSPIDataRW(0, data, 7); // although the register holds 6 bytes of acceleration data, 7 bytes are transfered (includes the register address)
	digitalWrite(stmPin, HIGH);

	// calculate the angular accel from the data
	angularAccel[0] = calcGyro(twosComp2ByteToSignedInt(&data[1]), GYRO_RANGE);
	angularAccel[1] = calcGyro(twosComp2ByteToSignedInt(&data[3]), GYRO_RANGE);
	angularAccel[2] = calcGyro(twosComp2ByteToSignedInt(&data[5]), GYRO_RANGE);

	// print linear and angular accel
	printf("%f %f %f\n", linearAccel[0], linearAccel[1], linearAccel[2]);
	printf("%f %f %f\n", angularAccel[0], angularAccel[1], angularAccel[2]);

	return 0;
}

// converts the data to a signed int
int16_t twosComp2ByteToSignedInt(unsigned char * input)
{
	if (input == NULL) return -1;
	return (int16_t)((signed char) input[1] << 8 |input[0]);
}

// from adafruit LSM6DS33 Library
float calcLinearAccel(int16_t twosCompAdjustedInput, int accelConvertionRatio)
{
	return (float)twosCompAdjustedInput * 0.061 * (accelConvertionRatio >> 1) / 1000;
}

// from adafruit LSM6DS33 Library
float calcGyro(int16_t twosCompAdjustedInput, int gyroRange)
{
	uint8_t gyroRangeDivisor = gyroRange / 125;
	if (gyroRange == 245)
	{
		gyroRangeDivisor = 2;
	}
	float output = (float)twosCompAdjustedInput * 4.375 * gyroRangeDivisor / 1000;
	return output;
}
