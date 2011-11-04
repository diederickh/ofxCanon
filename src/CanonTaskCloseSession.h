#ifndef ROXLU_CANONTASKCLOSESESSIONH
#define ROXLU_CANONTASKCLOSESESSIONH

#include "CanonTask.h"

namespace roxlu {
	class CanonTaskCloseSession : public CanonTask {
		public:
			
			CanonTaskCloseSession()
				:CanonTask(TASK_CLOSE_SESSION) 
			{
			}
			
			~CanonTaskCloseSession() {
			}
			
			virtual bool execute();
	};
}; // roxlu
#endif
