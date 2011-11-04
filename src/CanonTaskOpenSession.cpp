#include "CanonTaskOpenSession.h"
#include "Canon.h"

namespace roxlu {

// we always return true because when we return false, this task will be
// executed again and again and.... the CanonConnection will use a timer
// to restart the Canon SDK on error.

bool CanonTaskOpenSession::execute() {
	EdsError err = EDS_ERR_OK;
	
	// open the session.
	err = EdsOpenSession(canon->camera);
	if(err != EDS_ERR_OK) {
		printf("Canon: error opening session '%s'.", CanonErrorToString(err));
		return true;
	}
	
	// make sure files are saved on PC
	EdsUInt32 save_to = kEdsSaveTo_Host;
	err = EdsSetPropertyData(canon->camera, kEdsPropID_SaveTo, 0, sizeof(save_to), &save_to);
	if(err != EDS_ERR_OK) {
		printf("Canon: error while setting PC as host for images.\n");
		return true;
	}
	
	
	// Lock UI
	bool locked = false;
	err = EdsSendStatusCommand(canon->camera, kEdsCameraStatusCommand_UILock, 0);
	if(err == EDS_ERR_OK) {
		locked = true;
	}

	// opened session, so we can start the live view
	canon->setSessionOpen(true);
	
	EdsCapacity capacity = {0x7FFFFFFF, 0x1000, 1};
	err = EdsSetCapacity(canon->camera, capacity);
	if(err != EDS_ERR_OK){
		printf("Canon: error while setting capacity.\n");
		if(locked) {
			unlock();
		}
		return true;
	}
	 
	return true;
}

void CanonTaskOpenSession::unlock() {
	EdsError err = EdsSendStatusCommand(canon->camera, kEdsCameraStatusCommand_UIUnLock, 0);
	if(err != EDS_ERR_OK) {
		printf("Canon: error while trying to unlock the camera.\n");
	}
}

}; // roxlu