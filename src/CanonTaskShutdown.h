#ifndef ROXLU_CANONTASKSHUTDOWNH
#define ROXLU_CANONTASKSHUTDOWNH

#include "CanonTask.h"

namespace roxlu {

	class CanonTaskShutdown : public CanonTask {
		public:
			CanonTaskShutdown()
				:CanonTask(TASK_SHUTDOWN) 
			{
			}
			
			~CanonTaskShutdown() {
			}
			
			virtual bool execute();
		private:
	};

} // roxlu
#endif