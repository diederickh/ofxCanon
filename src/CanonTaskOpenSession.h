#ifndef ROXLU_CANONTASKOPENSESSIONH
#define ROXLU_CANONTASKOPENSESSIONH

#include "CanonTask.h"

namespace roxlu {
	class CanonTaskOpenSession : public CanonTask {
		public:
			
			CanonTaskOpenSession()
				:CanonTask(TASK_OPEN_SESSION) 
			{
			}
			
			~CanonTaskOpenSession() {
			}
			
			virtual bool execute();
		private:
			void unlock();
	};
}; // roxlu
#endif
