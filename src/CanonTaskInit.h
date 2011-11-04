#ifndef ROXLU_CANONTASKINITH
#define ROXLU_CANONTASKINITH

#include "CanonTask.h"
namespace roxlu {
	class CanonTaskInit : public CanonTask {
		public:
			CanonTaskInit()
				:CanonTask(TASK_INIT)
			{
			}
			
			~CanonTaskInit() {
			}
			
			virtual bool execute();
		private:
	};
} // roxlu
#endif