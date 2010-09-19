#ifndef OFXCANONCOMMANDTAKEPICTUREH
#define OFXCANONCOMMANDTAKEPICTUREH

#include "ofxCanonCommand.h"
#include "ofxCanonDebug.h"

class ofxCanonCommandTakePicture : public ofxCanonCommand {
public:
	ofxCanonCommandTakePicture(std::string sName,ofxCanonModel* pModel)
		:ofxCanonCommand(sName,pModel)
	{
	}
	
	virtual bool execute() {
		EdsError err = EDS_ERR_OK;

		err = EdsSendCommand(
			model->getCamera()
			,kEdsCameraCommand_TakePicture
			,0
		);
		
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

		return true;
	}
};
#endif