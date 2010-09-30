#ifndef OFXCANONCOMMANDTAKEPICTUREH
#define OFXCANONCOMMANDTAKEPICTUREH

#include "ofxCanonCommand.h"
#include "ofxCanonDebug.h"
#include "ofxLog.h"
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
        OFXLOG("ofxCanon: (command) take picture!");
        //boost::shared_ptr<ofxObservableEvent> e(new ofxObservableEvent("take_picture"));
        ofxObservableEvent e("take_picture");
		model->notifyObservers(e);

		//ofxObservableEvent e("take_picture");
		//model->notifyObservers(&e);

		if(err != EDS_ERR_OK) {
			OFXLOG("ERROR: " << ofxCanonErrorToString(err));
			//if(err == EDS_ERR_DEVICE_BUSY)
			//	cout << "ERR_MSG: Device is busy\n";
			 // when we return false we keep on trying until it works;
			 // sometimes this is not helpfull (i.e. when shutting down the
			 // camera)
			//return false;
		}
		return true;
	}
};
#endif
