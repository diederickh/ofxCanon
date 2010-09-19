#ifndef OFXCANONCOMMANDKEEPALIVEH
#define OFXCANONCOMMANDKEEPALIVEH

#include "ofxCanonCommand.h"

class ofxCanonCommandKeepAlive : public ofxCanonCommand {
public:
	ofxCanonCommandKeepAlive(
		std::string sName
		,ofxCanonModel* pModel
	):ofxCanonCommand(sName, pModel)
	{
	}
	
	virtual bool execute() {
		cout << "Keep alive!";
		EdsError err = EDS_ERR_OK;
		if(err == EDS_ERR_OK) {
			err = EdsSendStatusCommand(
				 model->getCamera()
				,kEdsCameraCommand_ExtendShutDownTimer
				,0
			);
		}
		
		
		// Show error:
		if(err != EDS_ERR_OK) {
			cout << "ERROR: " << err << std::endl;
		}
		else {
			cout << "CANON: Successfully updated the keep-alive time" << std::endl;
		}
		return true;
	}
};
#endif