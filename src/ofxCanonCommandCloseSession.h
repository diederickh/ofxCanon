#ifndef OFXCANONCOMMANDCLOSESESSIONH
#define OFXCANONCOMMANDCLOSESESSIONH

#include "ofxCanonCommand.h"
#include "ofxCanonDebug.h"

class ofxCanonCommandCloseSession : public ofxCanonCommand {
public:
	ofxCanonCommandCloseSession(std::string sName, ofxCanonModel* pModel)
		:ofxCanonCommand(sName,pModel)
	{
	}
	
	virtual bool execute() {
		EdsError err = EDS_ERR_OK;
		err = EdsCloseSession(model->getCamera());
		std::cout << "ofxCanon: closing session." << std::endl;
		// Show error:
		if(err != EDS_ERR_OK) {
			cout << "ERROR: " << ofxCanonErrorToString(err) << std::endl;
		}
		model->setSessionOpen(false);
		return true;
	}
};
#endif