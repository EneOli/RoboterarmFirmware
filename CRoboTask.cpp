#include "CRoboTask.hpp" //Include Header

//BEGIN Constructor
CRoboTask::CRoboTask(int MotorNr, String Direction, bool useTime, unsigned int Value)
{
	//Set Attributs
	this->Direction = Direction;
	this->MotorNr = MotorNr;
	int tmpWinkelRatio;

	//Activate Motor
	if (useTime) //If we use Millisecunds
	{
		//cooding + debug
		if (Direction == "L")
			digitalWrite(MotorNr + 1, LOW);
		else if (Direction == "R")
			digitalWrite(MotorNr + 1 + 5, LOW);

		WaitTime = Value; // Set waitingtime
	}

	else if (!useTime) // if we use angles
	{
		//Set angleratio
		switch (MotorNr)
		{
		case(1): tmpWinkelRatio = 80;	  break; //Motor   1
		case(2): tmpWinkelRatio = 87;	  break; //Motor   2
		case(3): tmpWinkelRatio = 77;	  break; //Motor   3
		case(4): tmpWinkelRatio = 66;	  break; //Motor   4
		case(5): tmpWinkelRatio = -1;     break; //Motor   5 --> Undefined
		}

		//Activate Motor
		if (Direction == "L")
			digitalWrite(MotorNr + 1, LOW);
		else if (Direction == "R")
			digitalWrite(MotorNr + 1 + 5, LOW);

		WaitTime = Value * tmpWinkelRatio; // Set waitingtime
	}
	//Set millis
	Millis = millis();
}
//END Constructor

//BEGIn Destructor
CRoboTask::~CRoboTask()
{
	//Deactivate motor
	if (Direction == "L")
		digitalWrite(MotorNr + 1, HIGH);
	else if (Direction == "R")
		digitalWrite(MotorNr + 1 + 5, HIGH);
}

//BEGIN check()
bool CRoboTask::check()
{
	//If we waited long enough...
	if (millis() - Millis >= WaitTime)
	{
		//Deactivate motor by Destructor
		delete this;
		return true; // Escape
	}
	else
		return false; // Escape
}
//END check()

