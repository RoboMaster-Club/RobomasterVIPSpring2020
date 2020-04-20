#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>

#ifndef _LIGHT_DETECTOR_H
#define _LIGHT_DETECTOR_H 

using namespace cv;
using namespace std;

class LightDetector {
public:
	LightDetector() {
		/*
		VideoCapture cap;
		cap.open(0);

		cap.set(CV_CAP_PROP_BRIGHTNESS, 0);
		cap.set(CV_CAP_PROP_CONTRAST, 32);
		cap.set(CV_CAP_PROP_SATURATION, 32);
		cap.set(CV_CAP_PROP_GAIN, 0);
		cap.set(CV_CAP_PROP_EXPOSURE, 0);
		*/

		//green light range
		lower = Scalar(50, 140, 0);
		upper = Scalar(94, 255, 156);
	}

    /*
     * Gets the current image from the dart's camera and uses OpenCV to
	 * find the position of the guiding light in the image.
     * 
     * @param centerResult Reference to the variable that will contain
	 * position of the guiding light in the image if the guiding light
	 * is found. If the light is not found, the centerResult will contain
	 * non-meaningful data.
	 *
	 * @returns True if the guiding light was found, false if not.
     */
	bool getLightPosition(Point2f& centerResult) {
		Mat frame, hsv, mask, kernel;
		vector<vector<Point>> contours;
  		vector<Vec4i> hierarchy;
		
		frame = imread("light.png");
		//cap(frame);

		cvtColor(frame, hsv, CV_BGR2HSV);

		// Thresholding
		inRange(hsv, lower, upper, mask);

		// Morphology
		kernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
		morphologyEx(mask, mask, MORPH_CLOSE, kernel);

		// Fit Circles
		findContours(mask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		float maxRadius = -1;
		float radius;
		Point2f center;
		vector<Point> contour_poly;

		for (int i = 0; i < contours.size(); i++) {
			approxPolyDP(contours[i], contour_poly, 3, true);
			minEnclosingCircle(contour_poly, center, radius);

			if (radius > maxRadius) {
				centerResult = center;
				maxRadius = radius;
			}
		}

		//return light coordinates centered at 0, 0
		//left is neg, right is pos, up is pos, down is neg
		int width = frame.cols;
		int height = frame.rows;
		centerResult = Point2f(-1 * (width/2 - centerResult.x), height/2 - centerResult.y);

		return contours.size() != 0; //true if light was found
	}

private:
	Scalar lower, upper;
};

#endif
