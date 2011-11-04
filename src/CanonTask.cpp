#include "CanonTask.h"
#include "Canon.h"
namespace roxlu {

CanonTask::CanonTask(int taskID) 
:canon(NULL)
,task_id(taskID)
{
}

CanonTask::~CanonTask() {

}

void CanonTask::setCanon(Canon* can) {
	canon = can;
}


} // roxlu