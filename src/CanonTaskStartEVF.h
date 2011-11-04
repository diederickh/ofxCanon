#ifndef ROXLU_CANONTASKSTARTEVFH
#define ROXLU_CANONTASKSTARTEVFH

#include "CanonTask.h"

namespace roxlu {
	class CanonTaskStartEVF : public CanonTask {
		public:
			
			CanonTaskStartEVF()
				:CanonTask(TASK_START_EVF) 
			{
			}
			
			~CanonTaskStartEVF() {
			}
			
			virtual bool execute();
			
		
	};
}; // roxlu
#endif
