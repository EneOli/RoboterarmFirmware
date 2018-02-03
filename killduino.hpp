//Author: Oliver Enes

//Includeguards
#ifndef _KILLDUINO_H
#define _KILLDUINO_H

//Wichtige Header fuer unsere Zwecke
#include <avr/sleep.h>
#include <avr/wdt.h>

//BEGIN killArduino

//BoardIsUno: wenn dieser Parameter auf "true" gestzt wird, werden alle Ports des Uno, aber nur des Unos auf "INPUT" und "LOW" gestzt.
//useExperimental wenn dieser Parameter auf true gesetzt wird, wird eine experementale Funktion zur Deaktivierung des Watchdogs genutzt.
void killArduino(bool BoardIsUno = false, bool useExperimental = false)
{
	//Ports des Arduino Uno auf "INPUT" und "LOW" setzen.
	if (BoardIsUno)
	{
		DDRC = 0;
		DDRB = 0;
		DDRD = 0;

		MCUCR |= _BV(PUD);
	}


	//Watchdog deaktivieren
	if (useExperimental)
		wdt_disable();


	//Sleepmode deaktivieren
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	//Das Sleepbyte setzen.
	sleep_enable();
	//Alle Interrupts beenden
	cli();
	//Hauptprozessor schlafen legen
	sleep_cpu();
}
//END killArduino
#endif



