#include "Fin.h"
#include "PIDController.h"
#include "LightDetector.h"

#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;
using namespace std;

int main() {
    LightDetector lightDetector;

    Fin leftElevator;
    Fin rightElevator;
    Fin rudder;

    PIDController yawController(0, 0.1, 0, 0.01);
    PIDController pitchController(0, 0.1, 0, 0.01, true);

    while (true) {
		Point2f center;

		//auto start = chrono::steady_clock::now(); 
        bool ret = lightDetector.getLightPosition(center);
		//auto end = chrono::steady_clock::now(); 
		//cout << (double) chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000000 << endl;


        if (ret) { //if light found
			double yawOutput = yawController.step(center.x);
		    double pitchOutput = pitchController.step(center.y);

			//cout << center.x << ", " << center.y << ", " << yawOutput << ", " << pitchOutput << endl;

			rudder.setPos(yawOutput);
            leftElevator.setPos(pitchOutput);
            rightElevator.setPos(pitchOutput);
		}
	}

	return 0;
}
