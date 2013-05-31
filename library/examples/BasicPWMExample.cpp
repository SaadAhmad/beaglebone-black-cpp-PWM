/*
 * BasicPWM.cpp
 *
 *	Example of basic PWM usage and fading an LED. Also shows how periods should be changed
 *
 *  Created on: May 29, 2013
 *      Author: Saad Ahmad ( http://www.saadahmad.ca )
 */

#include "PWM.h"
#include <ctime>
#include <string>

int main()
{
	const int delayMS = 50;
	const long periodNS = 2 * MILLISECONDS_TO_NANOSECONDS;
	PWM::Pin pinA("P8_13", periodNS); // Since both pins share the same channel, they're periods must be the same
	PWM::Pin pinB("P8_19", periodNS);

	std::cout << PWM::GetCapeManagerSlot("P8_13") << std::endl;

	// Enable both only after we have set the periods properly.
	// Otherwise we will have conflicts since each pin will try to set its own period and conflict with the others
	pinA.Enable();
	pinB.Enable();

	std::cout << "Pins Setup and ready to go!" << std::endl;

	for (int i = 0; i < 100; i++)
	{
		std::clock_t startTime = std::clock();
		while (((clock() - startTime) * 1000.0 / CLOCKS_PER_SEC) < delayMS)
		{
			pinA.SetDutyPercent(float(i) / 100);
			pinB.SetDutyPercent(1 - float(i) / 100);
		}

	}

	// Release the pins so they are disabled and so that we can also reset their periods
	// Note if you just call Disable() then you cant change the period as both channels will be treated as in use
	pinA.Release();
	pinB.Release();

	std::cout << "Setting new periods " << std::endl;

	pinA.SetPeriodNS(periodNS * 2);
  std::cout << "New period for Pin A set" << std::endl;

	pinB.SetPeriodNS(periodNS * 2);
	std::cout << "New period for Pin B set" << std::endl;

	// Once the periods have been set we can start again
	pinA.Enable();
	std::cout << "Enabled pin A" << std::endl;

	pinB.Enable();
	std::cout << "Enabled pin B" << std::endl;

	for (int i = 0; i < 100; i++)
	{
		std::clock_t startTime = std::clock();
		while (((clock() - startTime) * 1000.0 / CLOCKS_PER_SEC) < delayMS)
		{
			pinA.SetDutyPercent(float(i) / 100);
			pinB.SetDutyPercent(1 - float(i) / 100);
		}
	}

	std::cout << "Done everything. Quiting now!" << std::endl;
}

