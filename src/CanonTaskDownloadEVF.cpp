#include "CanonTaskDownloadEVF.h"
#include "Canon.h"
//#include <jpeglib.h>
namespace roxlu {

bool CanonTaskDownloadEVF::execute() {
	EdsError err = EDS_ERR_OK;
	EdsEvfImageRef evf_image = NULL;
	EdsStreamRef stream = NULL;
	EdsUInt32 buffer_size = 2 * 1024 * 1024;

	// Exit unless during live view
	if((canon->getEvfOutputDevice() & kEdsEvfOutputDevice_PC) == 0) {
		printf("Canon: EVF output is not set to PC\n");
		return true;
	}
	
	err = EdsCreateMemoryStream(buffer_size, &stream);
	if(err == EDS_ERR_OK) {
		err = EdsCreateEvfImageRef(stream, &evf_image);
	}
	
	if(err == EDS_ERR_OK) {
		err = EdsDownloadEvfImage(canon->camera, evf_image);
	}
	
	if(err == EDS_ERR_OK) {
		EvfDataSet data_set = {0};
		data_set.stream = stream;
		CanonEvent ev("evf_data_changed", (void*)&data_set);
		canon->fireEvent(ev);
		
	}
	
	if(stream != NULL) {
		EdsRelease(stream);
	}	
	if(evf_image != NULL) {
		EdsRelease(evf_image);
	}
	
	if(err != EDS_ERR_OK) {
		// Image is not ready yet.
		if(err == EDS_ERR_OBJECT_NOTREADY) {
			printf("Canon: live view, image not yet ready.\n");
			return false;
		}
		else if(err == EDS_ERR_DEVICE_BUSY) {
			printf("Canon: live view, device is busy\n");
			return false;
		}
	}
	return true;
}

}; // roxlu