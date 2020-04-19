#include "Fin.h"
#include "PIDController.h"

#include <opencv2/opencv.hpp> //Point2f, Point3f
#include <wiringPiSPI.h>
#include <stdint.h> //int8_t

#ifndef _DART_H
#define _DART_H

class Dart {
public:
    Dart() {
        leftElevator = Fin();
        rightElevator = Fin();
        rudder = Fin();

        // PID controllers for the first half of the dart flight
        trajectoryPitchController = PIDController(0, 0.1, 0, 0.01, true);
        trajectoryYawController = PIDController(0, 0.1, 0, 0.01);

        // PID controllers for the second half of the dart flight
        lightPitchController = PIDController(0, 0.1, 0, 0.01, true);
        lightYawController = PIDController(0, 0.1, 0, 0.01);

        Point3f currPos; // current position of the dart

        stmPin = 4;
        channel = 0;

        // init wiringPi
        wiringPiSetup();
        // init SPI at channel 0 at 25 mHz clock speed
        wiringPiSPISetup(0, 25000000);

        // set the stm32 slave select pin as output and set high
	    pinMode(stmPin, OUTPUT);
	    digitalWrite(stmPin, HIGH);
    }

    /*
     * During the second half of the dart's flight, calculates the fin angles 
     * to steer the dart towards the guiding light with PID control
     * 
     * @param center The image position of the guiding light (zero centered)
     */
    void setFinsFromLight(Point2f center) {
        int8_t pitchOutput = (int8_t) pitchController.step(center.y);
        int8_t yawOutput = (int8_t) yawController.step(center.x);

        leftElevator.setPos(pitchOutput);
        rightElevator.setPos(pitchOutput);
        rudder.setPos(yawOutput);
    }

    /*
     * During the first half of the dart's flight, stcalculates the fin angles 
     * to steer the dart towards the predefined dart trajectory with PID control
     * 
     * Assumes that the y axis represents the vertical distance, the x axis represents
     * the forward distance, and the z axis represents the left and right distance
     * 
     * @param point the 3d point in space that the dart should steer towards
     */
    void setFinsFromTrajectory(Point3f point) {
        trajectoryPitchController.setTarget(point.y);
        trajectoryYawController.setTarget(point.z);

        int8_t pitchOutput = (int8_t) trajectoryPitchController.step(center.y);
        int8_t yawOutput = (int8_t) trajectoryYawController.step(center.z);

        leftElevator.setPos(pitchOutput);
        rightElevator.setPos(pitchOutput);
        rudder.setPos(yawOutput);
    }

    /*
     * Send the fin angles to the stm32 over SPI
     */
    void sendFinPos() {
        // pull low to select stm32 and wait so that the stm32 is listening
        digitalWrite(stmPin, LOW);
        delay(10);

        // send the data on channel zero and read 3 bytes (reading 0 doesnt work)
        wiringPiSPIDataRW(channel, buffer, 3);
        digitalWrite(stmPin, HIGH);
    }

private:
    Fin leftElevator;
    Fin rightElevator;
    Fin rudder;

    PIDController pitchControlle;
    PIDController yawController;

    int8_t buffer[3];
    int stmPin, channel;
};

#endif