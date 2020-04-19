#include "LightDetector.h"
#include "Dart.h"

#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;
using namespace std;

int main() {
    LightDetector lightDetector;
    Dart dart;

    // define a set of positions that the dart should be at at time 0, delta, 2*delta, ... from launch
    const float delta = 0.1; // seconds
    const Point trajectory[] = {Point(0, 0, 0), Point(1, 1, 1), Point(2, 2, 2), Point(3, 3, 3)};

    auto timeStart = chrono::steady_clock::now();

    while (true) {
        // get time difference in seconds
        auto timeCurr = chrono::steady_clock::now(); 
        float timeDiff = (float) chrono::duration_cast<chrono::milliseconds>(timeCurr - timeStart).count() / 1000;

        int index = timeDiff / delta; // calc index of the predefined trajectory position

        if (index > trajectory.size()) { //dart should be in first half of flight
            dart.setFinsFromTrajectory(trajectory[index]);
            dart.sendFinPos();
        }
        else { // dart should be in second half of flight
        	Point2f center;
            bool ret = lightDetector.getLightPosition(center);

            if (ret) { // if light was found
                dart.setFinsFromLight(center);
                dart.sendFinPos();
            }
        }
	}

	return 0;
}
