#include <iostream>
#include <chrono>

#ifndef _PID_CONTROLLER_H
#define _PID_CONTROLLER_H

using namespace std;

class PIDController {
public:
	PIDController(float target, float p, float i, float d, bool reversed=false) {
		this->target = target;

		//to reverse output
		if (reversed)
			this->reversedValue = -1;
		else
			this->reversedValue = 1;

		this->kp = p; //porportional constant
		this->ki = i; //integral constant
		this->kd = d; //derivitive constant

		this->integralPrev = 0;
		this->errorPrev = 0;
		this->timePrev = chrono::steady_clock::now();
	}

	float step(float input) {
		float error = this->target - input;

		//get time difference in seconds
		auto timeCurr = chrono::steady_clock::now(); 
		float delta = (float) chrono::duration_cast<chrono::milliseconds>(timeCurr - this->timePrev).count() / 1000;
		
		float integral = this->integralPrev + error * delta;
		float derivitive;
		if (delta != 0)
			derivitive = (error - this->errorPrev) / delta;
		else
			derivitive = this->errorPrev;

		this->errorPrev = error;
		this->integralPrev = integral;
		this->timePrev = chrono::steady_clock::now();

		return this->reversedValue * (this->kp*error + this->ki*integral + this->kd*derivitive);
	}

	void setTarget(float value) {
		target = value;
	}

	float getTarget() {
		return target;
	}

private:
	float target;
	float integralPrev, errorPrev;
	chrono::steady_clock::time_point timePrev;
	float kp, ki, kd;
	int reversedValue;
};

#endif
