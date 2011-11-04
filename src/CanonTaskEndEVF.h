#ifndef ROXLU_CANONTASKENDEVFH
#define ROXLU_CANONTASKENDEVFH

#include "CanonTask.h"

namespace roxlu {
	class CanonTaskEndEVF : public CanonTask {
		public:
			
			CanonTaskEndEVF()
				:CanonTask(TASK_END_EVF) 
			{
			}
			
			~CanonTaskEndEVF() {
			}
			
			virtual bool execute();
			
		
	};
}; // roxlu
#endif
