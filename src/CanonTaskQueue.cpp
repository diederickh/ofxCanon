#include "CanonTaskQueue.h"
#include "Canon.h"
#include "ofMain.h"
namespace roxlu {

CanonTaskQueue::CanonTaskQueue() 
:is_stopped(false)
{
}

CanonTaskQueue::~CanonTaskQueue() {

}

void CanonTaskQueue::stop() {
	is_stopped = true;
}

void CanonTaskQueue::setCanon(Canon* can) {
	canon = can;
}

void CanonTaskQueue::run() {
	CanonTask* task = NULL;
	while(true) {
		task = takeTask();
		if(task != NULL) {
			if(!task->execute()) {
				addTask(task);
			}
			else {
				delete task;
			}
		}
		if(is_stopped && tasks.size() == 0) {
			break;
		}
	}
}

CanonTask* CanonTaskQueue::takeTask() {
	Mutex::ScopedLock lock(mutex);
	if(tasks.size() == 0) {
		return NULL;
	}
	CanonTask* task = tasks.front();
	tasks.pop_front();
	return task;
}

void CanonTaskQueue::addTask(CanonTask* task) {
	if(is_stopped) {
		return;
	}
	Mutex::ScopedLock lock(mutex);
	task->setCanon(canon);
	tasks.push_back(task);
}

void CanonTaskQueue::empty() {
	Mutex::ScopedLock lock(mutex);
	deque<CanonTask*>::iterator it = tasks.begin();
	while(it != tasks.end()) {
		delete *it;
		it = tasks.erase(it);
	}
}

}; // roxlu