#include "CanonTaskShutdown.h"
#include "Canon.h"

namespace roxlu {

bool CanonTaskShutdown::execute() {
	if(canon->camera == NULL) {
		EdsTerminateSDK();
		printf("Canon: Terminated SDK.\n");
		return true; 
	}
	
	printf("Canon: shutting down sdk.\n");
	EdsRelease(canon->camera_list);
	EdsRelease(canon->camera);
	EdsTerminateSDK();
	return true;
}

} // roxlu