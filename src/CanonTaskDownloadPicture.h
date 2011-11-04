#ifndef ROXLU_CANONTASKDOWNLOADPICTUREH
#define ROXLU_CANONTASKDOWNLOADPICTUREH

#include "CanonTask.h"

namespace roxlu {
	class CanonTaskDownloadPicture : public CanonTask {
		public:
			
			CanonTaskDownloadPicture(EdsDirectoryItemRef dirItem)
				:dir_item(dirItem)
				,CanonTask(TASK_DOWNLOAD_PICTURE) 
				
			{
			}
			
			~CanonTaskDownloadPicture() {
			}
			
			virtual bool execute();
			
		private:
			EdsDirectoryItemRef dir_item;
			
			static EdsError EDSCALLBACK progressFunc (
						 EdsUInt32	inPercent
						,EdsVoid*	inContext
						,EdsBool*	outCancel
			);
	
	};
}; // roxlu
#endif
