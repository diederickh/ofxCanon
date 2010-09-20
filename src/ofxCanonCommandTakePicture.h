#ifndef OFXCANONCOMMANDTAKEPICTUREH
#define OFXCANONCOMMANDTAKEPICTUREH

#include "ofxCanonCommand.h"
#include "ofxCanonDebug.h"
#include <windows.h>
#include <objbase.h>
class ofxCanonCommandTakePicture : public ofxCanonCommand {
public:
	ofxCanonCommandTakePicture(std::string sName,ofxCanonModel* pModel)
		:ofxCanonCommand(sName,pModel)
	{
	}

	virtual bool execute() {

		EdsError err = EDS_ERR_OK;
		//CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );
		err = EdsSendCommand(
			model->getCamera()
			,kEdsCameraCommand_TakePicture
			,0
		);
		std::cout << "ofxCanon: (command) take picture! - SLEEP" << std::endl;
		ofSleepMillis(3000);
		std::cout << "ofxCanon: (command) take picture! - READY" << std::endl;
		//CoUninitialize();
		std::cout << "ofxCanon: (command) take picture!" << std::endl;
		// Show error:
		if(err != EDS_ERR_OK) {
			cout << "ERROR: " << ofxCanonErrorToString(err) << std::endl;
			if(err == EDS_ERR_DEVICE_BUSY)
				cout << "ERR_MSG: Device is busy\n";
			 // when we return false we keep on trying until it works;
			 // sometimes this is not helpfull (i.e. when shutting down the
			 // camera)
			//return false;
		}

		//HANDLE hThread = (HANDLE)_beginthread(&ofxCanonCommandTakePicture::threadProc, 0, model->getCamera());
		// Block until finished
		//::WaitForSingleObject( hThread, INFINITE );
		return true;
	}
	static void threadProc(void* rCamRef) {
		/*
		EdsCameraRef camera = (EdsCameraRef)rCamRef;
		CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );
		EdsSendCommand(camera, kEdsCameraCommand_TakePicture, 0);
		CoUninitialize();
		*/
		//_endthread();
	}
};
#endif
