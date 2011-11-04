#ifndef ROXLU_CANON_TASKQUEUEH
#define ROXLU_CANON_TASKQUEUEH

#include <Poco/Thread.h>
#include <Poco/Runnable.h>
#include <Poco/Mutex.h>
#include <Poco/ScopedLock.h>
#include <deque>
#include "CanonTask.h"


using namespace std;
using Poco::Mutex;
using Poco::ScopedLock;

namespace roxlu {
	
	class Canon;
	
	class CanonTaskQueue : public Poco::Runnable {
		public:	
			CanonTaskQueue();
			~CanonTaskQueue();
			virtual void run();
			void addTask(CanonTask* task);
			void setCanon(Canon* can);
			void stop();
			CanonTask* takeTask();
			void empty();
		private:
			deque<CanonTask*> tasks;
			Poco::Mutex mutex;
			Canon* canon;
			bool is_stopped;
	};
}; // roxlu
#endif