/*
 * ServoExample.cpp
 *
 *	Example of PWM used to control servos via an esc
 *
 *  Created on: May 29, 2013
 *      Author: Saad Ahmad ( http://www.saadahmad.ca )
 * 		Modified: Mike Lewis ( http://alphalem.com )
 */

#include <string>
#include "../PWM.h"
#include "../Motor.h"
#include <ctime>
#include <cstdlib>

const float MIN_SPEED = 0;
const float CTR_SPEED = 90;
const float MAX_SPEED = 180;
const int MIN_SERVO_PULSE_TIME = 750;
const int MAX_SERVO_PULSE_TIME = 2250;
const std::string PIN_SERVO_RIGHT("P8_13");
const std::string PIN_SERVO_LEFT("P9_14");

ServoControl servoControls[] = {
	ServoControl(PIN_SERVO_LEFT, CTR_SPEED, MIN_SPEED, MAX_SPEED),
	ServoControl(PIN_SERVO_RIGHT, CTR_SPEED, MIN_SPEED, MAX_SPEED)
};


#include <signal.h>

// Stop all the motors when we interrupt the program so they don't keep going
void sig_handler(int signum) {
	for (unsigned int i = 0; i < 2; i++) {
		ServoControl& servo = servoControls[i];
		servo.SetAngle(90);
		servo.UpdatePWMSignal();
	}

	exit(signum);
}

void servo_test(int angle)
{
	std::clock_t startTime = std::clock();
	while (((clock() - startTime) * 1000.0 / CLOCKS_PER_SEC) < 500) {
		for (int iServo = 0; iServo < 2; iServo++) {
			ServoControl& servo = servoControls[iServo];
			// Offset the motors a bit
			servo.SetAngle(angle);
			servo.UpdatePWMSignal();
		}
	}
}

int main() {
	signal(SIGINT, sig_handler);
	signal(SIGSEGV, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGHUP, sig_handler);
	signal(SIGABRT, sig_handler);

	for (int i = 0; i < 2; i++) {
		servoControls[i].Enable();
	}

	while (true) {
		// Increase by 10 degrees (CW) each time
		for (int i = 90; i < 180; i += 5) {
			servo_test(i);
		}
		
		// Decrease by 10 degrees (CCW) each time
		for (int i = 180; i > 90; i -= 5) {
			servo_test(i);
		}
		
		// Decrease by 10 degrees (CCW) each time
		for (int i = 90; i > 0; i -= 5) {
			servo_test(i);
		}
		
		// Increase by 10 degrees (CW) each time
		for (int i = 0; i < 90; i += 5) {
			servo_test(i);
		}
	}
}

