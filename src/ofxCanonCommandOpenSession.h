#ifndef OFXCANONCOMMANDOPENSESSIONH
#define OFXCANONCOMMANDOPENSESSIONH

#include "ofxCanonCommand.h"
#include "ofxCanonDebug.h"
#include <boost/thread.hpp>
#include "ofMain.h"

class ofxCanonCommandOpenSession : public ofxCanonCommand {
public:
	ofxCanonCommandOpenSession(std::string sName, ofxCanonModel* pModel)
		:ofxCanonCommand(sName,pModel)
	{
	}

	virtual bool execute() {

		cout << "ofxCanon: (command) execute open session in threadd: " << boost::this_thread::get_id() << std::endl;
		EdsError err = EDS_ERR_OK;
		err = EdsOpenSession(model->getCamera());
		bool locked = false;

		if(err == EDS_ERR_OK) {
			// Preservation ahead is set to PC
			EdsUInt32 save_to = kEdsSaveTo_Host;
			err = EdsSetPropertyData(
				 model->getCamera()
				,kEdsPropID_SaveTo
				,0
				,sizeof(save_to)
				,&save_to
			);
		}

		// Lock UI
		if(err == EDS_ERR_OK) {
			err = EdsSendStatusCommand(
				 model->getCamera()
				,kEdsCameraStatusCommand_UILock
				,0
			);
		}

		if (EDS_ERR_OK)
			locked = true;

		if (err == EDS_ERR_OK) {
			EdsCapacity capacity = {0x7FFFFFFF, 0x1000, 1};
			err = EdsSetCapacity(model->getCamera(), capacity);
		}


		// Unlock UI
		if (locked) {
			err = EdsSendStatusCommand(
				 model->getCamera()
				,kEdsCameraStatusCommand_UIUnLock
				,0
			);
		}

		// Show error:
		if(err != EDS_ERR_OK) {
			cout << "ERROR: ofxCanonCommandOpenSession(): " << ofxCanonErrorToString(err) << " return an internal error t reset init()" << std::endl;
			ofxObservableEvent e("internal_error");
			model->notifyObservers(&e);
			return true;
			//model->setSessionOpen(false);
		}
		else {
			model->setSessionOpen(true);
		}
		ofxObservableEvent e("opened_session");
		model->notifyObservers(&e);
		cout << "Opened session..." << std::endl;
		return true;
	}
};
#endif
