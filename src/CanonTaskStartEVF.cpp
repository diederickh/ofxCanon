#include "CanonTaskStartEVF.h"
#include "Canon.h"
namespace roxlu {

bool CanonTaskStartEVF::execute() {
	if(!canon->isCameraConnected()) {
		printf("==============================\n");
		return false;
	}
	EdsError err = EDS_ERR_OK;
	EdsUInt32 evf_mode = canon->getEvfMode();
	printf("Canon: start evf, with mode: %d\n", (int)evf_mode);
	
	// Change settings because live view cannot be started when 
	// camera settings are set to "do not perform live view".
	if(evf_mode == 0) {
		evf_mode = 1;
		err = EdsSetPropertyData(canon->camera, kEdsPropID_Evf_Mode, 0, sizeof(evf_mode), &evf_mode);
	}
	
	if(err == EDS_ERR_OK) {
		EdsUInt32 device = canon->getEvfOutputDevice();
		printf("Canon: start evf output device: %d\n", (int)device);
		
		// Set pc as currenct output device.
		device |= kEdsEvfOutputDevice_PC;
		err = EdsSetPropertyData(canon->camera, kEdsPropID_Evf_OutputDevice, 0, sizeof(device), &device);
	}
	
	if(err != EDS_ERR_OK) {
		if(err == EDS_ERR_DEVICE_BUSY) {
			printf("Canon: error while starting evf.\n");
			return false;
		}
	}
	return true;
}

}; // roxlu