#ifndef ROXLU_CANONTASKTAKEPICTUREH
#define ROXLU_CANONTASKTAKEPICTUREH

#include "CanonTask.h"

namespace roxlu {
	class CanonTaskTakePicture : public CanonTask {
		public:
			
			CanonTaskTakePicture()
				:CanonTask(TASK_TAKE_PICTURE) 
			{
			}
			
			~CanonTaskTakePicture() {
			}
			
			virtual bool execute();
	};
}; // roxlu
#endif
