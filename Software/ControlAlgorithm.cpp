#include "Fin.h"
#include "PIDController.h"
#include "LightDetector.h"

#include <opencv2/opencv.hpp>
#include <chrono>
#include <wiringPiSPI.h>
#include <stdint.h> //int8_t

using namespace cv;
using namespace std;

// chip enable pin (1 or 0)
static const int CHANNEL = 1;

int main() {
    LightDetector lightDetector;

    Fin leftElevator;
    Fin rightElevator;
    Fin rudder;

    PIDController pitchController(0, 0.1, 0, 0.01, true);
    PIDController yawController(0, 0.1, 0, 0.01);

    int8_t pitchOutput, yawOutput;
    int8_t buffer[3];

    int fd = wiringPiSPISetup(CHANNEL, 500000);

    while (true) {
		Point2f center;

		//auto start = chrono::steady_clock::now(); 
        bool ret = lightDetector.getLightPosition(center);
		//auto end = chrono::steady_clock::now(); 
		//cout << (double) chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000000 << endl;

        if (ret) { //if light found
        	pitchOutput = (int8_t) pitchController.step(center.y);
			yawOutput = (int8_t) yawController.step(center.x);

			//cout << center.x << ", " << center.y << ", " << static_cast<int16_t>(yawOutput) << ", " << static_cast<int16_t>(pitchOutput) << endl;

            leftElevator.setPos(pitchOutput);
            rightElevator.setPos(pitchOutput);
			rudder.setPos(yawOutput);

            buffer[0] = leftElevator.getPos();
            buffer[1] = rightElevator.getPos();
            buffer[2] = rudder.getPos();

            wiringPiSPIDataRW(CHANNEL, buffer, 3);
		}
	}

	return 0;
}
