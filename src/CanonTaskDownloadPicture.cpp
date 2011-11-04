#include "CanonTaskDownloadPicture.h"
#include "CanonPictureEvent.h"
#include "Canon.h"
namespace roxlu {

bool CanonTaskDownloadPicture::execute() {
	EdsError err = EDS_ERR_OK;
	EdsStreamRef stream = NULL;
	
	// Get info about new image.
	EdsDirectoryItemInfo dir_item_info;
	err = EdsGetDirectoryItemInfo(dir_item, &dir_item_info);
	if(err != EDS_ERR_OK) {
		printf("Canon: error while trying to get more info about image to be downloaded.\n");
	}
	
	// Created file stream to download image.
	if(err == EDS_ERR_OK) {
		string dest = Canon::instance().getDownloadDir() +dir_item_info.szFileName;
		err = EdsCreateFileStream(dest.c_str(), kEdsFileCreateDisposition_CreateAlways, kEdsAccess_ReadWrite, &stream);
	}
	if(err != EDS_ERR_OK) {
		printf("Canon: error while creating download stream.\n");	
	}
	
	// Set progress
	if(err == EDS_ERR_OK) {
		err = EdsSetProgressCallback(stream, progressFunc, kEdsProgressOption_Periodically, this);
	}
	if(err != EDS_ERR_OK) {
		printf("Canon: error while setting download progress function.\n");
	}
	
	// Download image.
	if(err == EDS_ERR_OK) {
		err = EdsDownload(dir_item, dir_item_info.size, stream);
	}
	if(err != EDS_ERR_OK) {
		printf("Canon: error while downloading item.\n");
	}
	
	// Tell we're ready.
	if(err == EDS_ERR_OK) {
		CanonPictureEvent ev(dir_item_info.szFileName);
		Canon::instance().firePictureTakenEvent(ev);
		
		err = EdsDownloadComplete(dir_item);
	}
	if(err != EDS_ERR_OK) {
		printf("Canon: error while telling we're ready with the file download.\n");
	}
	
	// Release dir item.
	if(dir_item != NULL) {
		err = EdsRelease(dir_item);
		if(err != EDS_ERR_OK) {
			printf("Canon: error releasing dir item when downloading.\n");
		}
		dir_item = NULL;
	}
	
	// Release stream
	if(stream != NULL) {
		err = EdsRelease(stream);
		if(err != EDS_ERR_OK) {
			printf("Canon: error while releasing download stream.\n");
		}
		stream = NULL;
	}
		
	return true;
}

EdsError EDSCALLBACK CanonTaskDownloadPicture::progressFunc(
								 EdsUInt32	inPercent
								,EdsVoid*	inContext
								,EdsBool*	outCancel
)
{
	printf("Canon: downloading image: %d.\n", (int)inPercent);
	return EDS_ERR_OK;
}

} // roxlu