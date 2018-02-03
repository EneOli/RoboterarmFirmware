#include "CTaskQueue.hpp" //Include Classdeclaration

//BEGIN Update()
void CTaskQueue::Update()
{
	//Check every task in queue
	for (int i = 0; i < queue.Size(); i++)
	{
		if (queue[i]->check())			//	if it was time to end, we will set the responsible pointer to null, 
		{								//	so that it will be removed in the next check.
			queue.change(i, nullptr);
		}
	}

	queue.checkptr(); // check, if we have nullptrs, that should be removed from queue
}
//END Update()

//BEGIN add(CRoboTask *task)
void CTaskQueue::add(CRoboTask *task)
{
	queue.Push_Back(task); // Add new task to queue
}
//END add(CRoboTask *task)



