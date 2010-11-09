#ifndef OFXCANONCOMMANDCLOSESESSIONH
#define OFXCANONCOMMANDCLOSESESSIONH

#include "ofxCanonCommand.h"
#include "ofxCanonDebug.h"
#include "ofxLog.h"
#include "ofMain.h"
class ofxCanonCommandCloseSession : public ofxCanonCommand {
public:
	ofxCanonCommandCloseSession(std::string sName, ofxCanonModel* pModel)
		:ofxCanonCommand(sName,pModel)
	{
	}

	virtual bool execute() {
		EdsError err = EDS_ERR_OK;
		err = EdsCloseSession(model->getCamera());
		OFXLOG("ofxCanon: (command) closing session.");
		ofSleepMillis(2000);
		// Show error:
		if(err != EDS_ERR_OK) {
			std::cout << "ofxCanon - close session: ERROR: " << ofxCanonErrorToString(err) << std::endl;
        }
		model->setSessionOpen(false);
		return true;
	}
};
#endif
