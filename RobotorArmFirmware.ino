//Include Header
#include "killduino.hpp"
#include "CRoboTask.hpp"
#include "CTaskQueue.hpp"
#include "CDebugger.hpp"

//global variables
String BefehlString;	//	raw command
int MotorNr;	//	Motor number
String Richtung;	//	Direction L v R
bool useTime;	// do we use time?
int timeMs = -1;	// waiting time in Millisecunds, initalized with -1
int winkel = -1;	// waiting time with winkelratio, initalized with -1
//CTaskQueue queue; // Task queue // replaced with Singleton

//BEGIN setup()
void setup()
{
	Serial.begin(9600); //Serial communication
	Serial.println("Serielle Verbindung hergestellt."); // success message

	//Initialize pins and set to HIGH
	for (int i = 2; i <= 11; i++)
	{
		pinMode(i, OUTPUT);
		digitalWrite(i, HIGH);
	}

}
//END setup()

//BEGIN loop()
void loop()
{
	Serial.println("Guten Tag! Wie lautet dein Befehl?");	//	print welcome message
	while (BefehlString != "ENDE")	// run, until command "ende"
	{
    //clean everything
		BefehlString = "";	//set the command back
    CDebugger::Get()->debugPrintln("command buffer cleared", true);
    MotorNr = -1;
    CDebugger::Get()->debugPrintln("MotorNr cleared", true);
    Richtung = "None";
    CDebugger::Get()->debugPrintln("Richtung cleared", true);
    useTime = false;
    CDebugger::Get()->debugPrintln("useTime cleared", true);
    timeMs = -1;
    CDebugger::Get()->debugPrintln("timeMs cleared", true);
    winkel = -1;
    CDebugger::Get()->debugPrintln("winkel cleared", true);

		if (Serial.available()) //Process user input
		{
			BefehlString = Serial.readString(); // save user input
			BefehlString.toUpperCase(); //convert to UperCase for easier process
			if (BefehlString == "ENDE") continue;
			if (BefehlString == "DEBUG")
			{
				CDebugger::Get()->setDebugState(true);
        Serial.println("\n----------Debugging------------");
				Serial.println("Debugging aktiviert.");
        Serial.println("Ab sofort stehen neue Befehle zur Verfuegung!");
				Serial.println("Achtung, diese Funktion ist nur für Entwickler!");
				delay(2000);
        continue;
			}
			else if (BefehlString == "DEBUG END")
			{
				CDebugger::Get()->setDebugState(false);
				Serial.println("Debugging deaktiviert");
        continue;
			}
     else if (BefehlString.substring(0, 5) == "DEBUG")
     {
      CDebugger::Get()->Debug(BefehlString);
      continue;
     }
			//output raw command
			Serial.print("Eingabe: ");
			Serial.println(BefehlString);
      if(BefehlString.substring(0,1) == "M")
      {
			MotorNr = BefehlString.substring(1, 2).toInt(); // get MotorNr from command and convert to int
			Richtung = BefehlString.substring(3, 4);	//	get Direction from command

			//set time and create new CRoboTask
			if (BefehlString.substring(5, 6) == "T") // If the user wants to use the time
			{
				timeMs = BefehlString.substring(6, 20).toInt(); // save time in variable
				useTime = true;	// set useTime to true
				CTaskQueue::Get()->add(new CRoboTask(MotorNr, Richtung, useTime, timeMs)); //add new CRoboTask to queue
        CDebugger::Get()->debugPrintln("Added new Task(M " + String(MotorNr) + " " + Richtung + " T" + String(timeMs) + ")"); // Debug print
			} 
			else if (BefehlString.substring(5, 6) == "W") // if the user wants to use the angle
			{
				winkel = BefehlString.substring(6, 20).toInt(); // convert ans save the angle in variable
				useTime = false;	//set useTime to false
				CTaskQueue::Get()->add(new CRoboTask(MotorNr, Richtung, useTime, winkel)); //add new CRoboTask to queue
        CDebugger::Get()->debugPrintln("Added new Task(M " + String(MotorNr) + " " + Richtung + " W" + String(winkel) + ")"); // Debug print
			}
      }else
      {
        Serial.println("Befehl nicht bekannt!");
        continue;
      }

			//print evaluated command
			Serial.print("Motor: ");
			Serial.println(MotorNr);
			Serial.print("Richtung: ");
			Serial.println(Richtung);
			Serial.print("Zeit: ");
			Serial.println(timeMs);
			Serial.print("Winkel: ");
			Serial.println(winkel);
      Serial.print("Zeit: (1 = Ja/ 0 = Nein): ");
			Serial.println(useTime);

		}
		CTaskQueue::Get()->Update(); // Update queue every loop
		CDebugger::Get()->debugPrintln("Task queue updated!", true);

	}
	//print goodbye message
	Serial.println("Deaktiviere jetzt den Arduino und die zentrale Prozessoreinheit....");
	Serial.println("Auf Wiedersehen!");
	delay(500);
	killArduino(true, true); // set the arduino in deep sleep mode
}
//END loop()


