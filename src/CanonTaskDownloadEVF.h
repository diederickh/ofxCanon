#ifndef ROXLU_CANONTASKDOWNLOADEVFH
#define ROXLU_CANONTASKDOWNLOADEVFH

#include "CanonTask.h"

namespace roxlu {

	struct EvfDataSet {
		EdsStreamRef	stream; // JPEG stream.
		EdsUInt32		zoom;
		EdsRect			zoom_rect;
		EdsPoint		image_position;
		EdsUInt32		histogram[256 * 4]; //(YRGB) YRGBYRGBYRGBYRGB....
		EdsSize			size_jpeg_large;
	};

	class CanonTaskDownloadEVF : public CanonTask {
		public:
			
			CanonTaskDownloadEVF()
				:CanonTask(TASK_DOWNLOAD_EVF) 
			{
			}
			
			~CanonTaskDownloadEVF() {
			}
			
			virtual bool execute();
			
		
	};
}; // roxlu
#endif
