#include "CanonTaskInit.h"
#include "CanonSDK.h"
#include "Canon.h"
#include "CanonEventListener.h"

namespace roxlu {

// we always return true because when we return false, this task will be
// executed again and again and.... the CanonConnection will use a timer
// to restart the Canon SDK on error.

bool CanonTaskInit::execute() {
	// initialize SDK and retrieve camera list + info
	// -----------------------------------------------
	EdsError err = EDS_ERR_OK;
	err = EdsInitializeSDK();
	if(err != EDS_ERR_OK) {
		printf("Canon: error while initializing sdk.\n");
		return true;
	}
	
	err = EdsGetCameraList(&canon->camera_list);
	if(err != EDS_ERR_OK) {
		printf("Canon: error while retrieving camera list.\n");
		return true;
	}
	
	EdsUInt32 count = 0;
	err = EdsGetChildCount(canon->camera_list, &count);
	if(err != EDS_ERR_OK) {
		printf("Canon: error while retrieving camera count.\n");
		return true;
	}
	if(count == 0) {
		printf("Canon: initialized, but cannot find a camera.\n");
		return true;
	}
	printf("Canon: found:%d cameras.\n", (int)count);
		
	err = EdsGetChildAtIndex(canon->camera_list, 0, &canon->camera);
	if(err != EDS_ERR_OK) {
		printf("Canon: error while retrieving camera from camera list.\n");
		return true;
	}
	
	EdsDeviceInfo device_info;
	err = EdsGetDeviceInfo(canon->camera, &device_info);
	if(err != EDS_ERR_OK) {
		printf("Canon: error while retrieving device info.\n");
		return true;
	}
	
	// Set event listener
	// -------------------
	err = EdsSetPropertyEventHandler(canon->camera, kEdsPropertyEvent_All, CanonEventListener::handlePropertyEvent, (EdsVoid*)canon);
	if(err != EDS_ERR_OK) {
		printf("Canon: error, cannot set property event handler.\n");
		return true;
	}
	
	err = EdsSetObjectEventHandler(canon->camera, kEdsObjectEvent_All, CanonEventListener::handleObjectEvent, (EdsVoid*)canon);
	if(err != EDS_ERR_OK) {
		printf("Canon: error, cannot set object event handler.\n");
		return true;
	}	
	
	err = EdsSetCameraStateEventHandler(canon->camera, kEdsStateEvent_All, CanonEventListener::handleStateEvent, (EdsVoid*)canon);
	if(err != EDS_ERR_OK) {
		printf("Canon: error, cannot set state event handler.\n");
		return true;
	}	
	
	return true;
}

}; // roxlu
