#include "CanonTaskTakePicture.h"
#include "CanonSDK.h"
#include "Canon.h"

namespace roxlu {

bool CanonTaskTakePicture::execute() {
	EdsError err = EDS_ERR_OK;
	
	// @todo cameras older then 30D we need to lock the interface.
	
	err = EdsSendCommand(canon->camera, kEdsCameraCommand_TakePicture, 0);
	if(err != EDS_ERR_OK) {
		printf("Canon: error while sending take picture command '%s'.\n", CanonErrorToString(err));
		if(err == EDS_ERR_DEVICE_BUSY) {
			return false;
		}
	}
	return true;
}

} // roxlu