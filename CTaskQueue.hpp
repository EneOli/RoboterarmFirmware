//Includeguard
#ifndef _CTASKQUEUE_HPP
#define _CTASKQUEUE_HPP

//Include Headers
#include "vector.hpp"
#include "CRoboTask.hpp"
#include "Singleton.hpp"

//BEGIN class CTaskQueue
class CTaskQueue : public TSingleton<CTaskQueue>
{
public:
	void Update(); // Update() - check Tasks and end, if necessary
	void add(CRoboTask *task); // ad(CRoboTask *task) - add new task to queue
  int getSize(){return queue.Size();}
private:
	vector<CRoboTask*> queue; // private vector(Own lib), which holds all tasks
};
//END class CTaskQueue

#endif


