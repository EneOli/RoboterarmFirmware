#include "CDebugger.hpp"
#include "CTaskQueue.hpp"

void CDebugger::setDebugState(bool debug)
{
	useDebug = debug;
}

void CDebugger::debugPrint(String text, bool useHardMode)
{
	if (useDebug)
    if(useHardMode)
    {
       if(hardMode)
		      Serial.print(text);
    }
    else
    Serial.print(text);
         
}

void CDebugger::debugPrintln(String text, bool useHardMode)
{
  if (useDebug)
    if(useHardMode)
    {
       if(hardMode)
          Serial.println(text);
    }
    else
    Serial.println(text);
         
}

void CDebugger::Debug(String cmd)
{
	if (useDebug)
	{
     if(cmd == "DEBUG RUN")
     {
        if(CTaskQueue::Get()->getSize() == 0)
        {
          Serial.println("-----------------Motor Selbsttest ueber digitalWrite-----------------");
          Serial.println("Starte Selbstest.");
          for(int i = 1; i<= 10; i++)
          {
            Serial.print("Test Motor ");
            Serial.println(i);
            digitalWrite(i+1, LOW);
            delay(1000);
            digitalWrite(i+1, HIGH);
          }
          Serial.println("---------------END Motor Selbsttest ueber digitalWrite--------------");
          delay(1000);
        }else
          Serial.println("Bitte warte, bis alles Motoren zum Stillstand gekommen sind!");
     }

     else if(cmd.substring(6, 10) == "MODE")
     {
        if(cmd.substring(11, 17) == "HARD")
        {
        hardMode = true;
        Serial.println("Debugmode auf HARD gesetzt");
        delay(1000);
        }

        else if(cmd.substring(11, 15) == "EASY")
        {
        hardMode = false;
        Serial.println("Debugmode auf EASY gesetzt");
        }
     }
	}
}
