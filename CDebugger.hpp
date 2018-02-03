#ifndef _CDEBUGGER_HPP
#define _CDEBUGGER_HPP
#include "Singleton.hpp"

#include <Arduino.h>

class CDebugger : public TSingleton<CDebugger>
{
public:
	void setDebugState(bool debug);
	void debugPrint(String text, bool useHardMode = false);
	void debugPrintln(String text, bool useHardMode = false);
	void Debug(String cmd);

private:
	bool useDebug = false;
  bool hardMode = false;
};

#endif
