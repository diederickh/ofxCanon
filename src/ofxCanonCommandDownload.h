#ifndef OFXCANONCOMMANDOWNLOADH
#define OFXCANONCOMMANDOWNLOADH

#include "ofxCanonCommand.h"
#include "ofxCanonDebug.h"
#include "EDSDK.h"
#include "ofMain.h"

class ofxCanonCommandDownload : public ofxCanonCommand {
private:
	EdsDirectoryItemRef dir_item;

public:
	ofxCanonCommandDownload(
					std::string sName
					,ofxCanonModel* pModel
					,EdsDirectoryItemRef oDirItem

		):dir_item(oDirItem)
		,ofxCanonCommand(sName,pModel)
	{
	}

	virtual ~ofxCanonCommandDownload() {
		if(dir_item != NULL) {
			EdsRelease(dir_item);
			dir_item = NULL;
		}
	}

	virtual bool execute() {
		EdsError err = EDS_ERR_OK;
		EdsStreamRef stream = NULL;
		EdsDirectoryItemInfo dir_item_info;
		err = EdsGetDirectoryItemInfo(dir_item, &dir_item_info);
		std::cout << "ofxCanon: (command), download picture." << std::endl;
		if(err == EDS_ERR_OK) {
			// @todo notify download start event
		}

		string filename = dir_item_info.szFileName;

		// Make the filestream at the forwarding destination (default to PC)
		if(err == EDS_ERR_OK) {
			// @todo check if the download directory exist.
			//string dir = ofToDataPath( "images/" );
			string dir = model->getDownloadDir();
			cout << "DOWNLOAD TO: " << dir << std::endl;
			dir = dir + dir_item_info.szFileName;
			const char* dest = dir.c_str();
			cout << "SAVE DEST: "<< dest << std::endl;
			err = EdsCreateFileStream(
				dest
				,kEdsFileCreateDisposition_CreateAlways
				,kEdsAccess_ReadWrite
				,&stream
			);
		}

		// Set progress
		if(err == EDS_ERR_OK) {
			err = EdsSetProgressCallback(
				 stream
				,ProgressFunc
				,kEdsProgressOption_Periodically
				,this
			);
		}

		// Download image
		if(err == EDS_ERR_OK)
			err = EdsDownload(dir_item, dir_item_info.size, stream);

		// Forwarding completion
		if (err == EDS_ERR_OK)
			err = EdsDownloadComplete(dir_item);

		// Release item.
		if(dir_item != NULL) {
			err = EdsRelease(dir_item);
			dir_item = NULL;
		}

		// Release stream
		if (stream != NULL) {
			err = EdsRelease(stream);
			stream = NULL;
		}

		// Show error:
		if(err != EDS_ERR_OK) {
			cout << "ERROR: " << ofxCanonErrorToString(err) << std::endl;
			if(err == EDS_ERR_DEVICE_BUSY)
				cout << "ERR_MSG: Device is busy\n";
		}
		else {
			ofxObservableEvent e("download_complete", &filename);
			model->notifyObservers(&e);
		}

		return true;
	}

private:

	static EdsError EDSCALLBACK ProgressFunc (
						EdsUInt32	inPercent,
						EdsVoid *	inContext,
						EdsBool	*	outCancel
						)
	{
		// @todo, uncomment this code?
		//ofxCommand *command = (ofxCommand *)inContext;
		//printf(">>> downloading: %i\n", inPercent);
		//CameraEvent e("ProgressReport", &inPercent);
		//command->getCameraModel()->notifyObservers(&e);
		return EDS_ERR_OK;
	}

	// @todo implement progress func
};
#endif
