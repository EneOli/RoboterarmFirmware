//Includeguard
#ifndef _CRoboTask_HPP
#define _CRoboTask_HPP

//Header for Arduinofunctions
#include <Arduino.h>

//BEGIN Class CRoboTask
class CRoboTask
{
public:
	CRoboTask(int MotorNr, String Direction, bool useTime, unsigned int Value); //Konstructor Prototype
	~CRoboTask();	//Destructor Prototype
	bool check();	// check() Prototype - Check, if time to deactivate

private:
	long Millis;	//Millis since konstruction
	short MotorNr; // MotorNr.
	String Direction; // Direction L v R
	long WaitTime;	//Time to wait between HIGH and LOW
};
//END Class CRoboTask

//END Includeguard
#endif
