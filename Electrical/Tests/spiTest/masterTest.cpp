#include <wiringPi.h>
#include <wiringPiSPI.h>

int main(void)
{
	const int stmPin = 4;
	unsigned char dataOn[1];
	unsigned char dataOff[1];

	// init wiringPi
	wiringPiSetup();
	// init SPI at channel 0 at 25 mHz clock speed
	wiringPiSPISetup(0, 25000000);
	
	// set the stm32 slave select pin as output and set high
	pinMode(stmPin, OUTPUT);
	digitalWrite(stmPin, HIGH);

	// turn led on stm32 on and off 10 times
	for (int i = 0; i < 10; i++)
	{
		// data values are set every loop because the wiringPiSPI funciton writes the data and then overwrites it with what is read from the stm32
		*dataOn = 0b11111111;
		*dataOff = 0b00000000;

		// pull low to select stm32 and wait so that the stm32 is listening
		digitalWrite(stmPin, LOW);
		// wiringPi also has a delay function like arduino
		delay(10);

		// send the data on channel zero and read 1 byte (reading 0 doesnt work)
		wiringPiSPIDataRW(0, dataOn, 1);
		digitalWrite(stmPin, HIGH);
		delay(50);

		digitalWrite(stmPin, LOW);
		delay(10);

		wiringPiSPIDataRW(0, dataOff, 1);
		digitalWrite(stmPin, HIGH);
		delay(50);
	}
	return 0;
}

