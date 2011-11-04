#include "CanonTaskEndEVF.h"
#include "Canon.h"

namespace roxlu {

bool CanonTaskEndEVF::execute() {
	EdsError err = EDS_ERR_OK;
	EdsUInt32 device = canon->getEvfOutputDevice();
	printf("Canon: End EVF\n");
	
	// already ended.
	if ((device & kEdsEvfOutputDevice_PC) == 0) {
		return true;
	}
	
	// change the output device
	device &= ~kEdsEvfOutputDevice_PC;
	err = EdsSetPropertyData(canon->camera, kEdsPropID_Evf_OutputDevice, 0, sizeof(device), &device);
	
	if(err != EDS_ERR_OK) {
		if(err == EDS_ERR_DEVICE_BUSY) {
			return false;
		}
		return false;
	}
	return true;
}

}; // roxlu