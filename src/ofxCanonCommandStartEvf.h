#ifndef OFXCANONCOMMANDSTARTEVFH
#define OFXCANONCOMMANDSTARTEVFH
#include "ofxCanonCommand.h"
#include "ofxCanonDebug.h"

class ofxCanonCommandStartEvf : public ofxCanonCommand {

public:

	ofxCanonCommandStartEvf(std::string sName,ofxCanonModel* pModel)
		:ofxCanonCommand(sName, pModel)
	{
	}
	
	virtual bool execute() {
		EdsError err = EDS_ERR_OK;
		EdsUInt32 evf_mode = model->getEvfMode();
		cout << "ofxCanon: (command) execute startEVF" << std::endl;
		// Change settings because live view cannot be started when 
		// camera settings are set to "do not perform live view"
		if(evf_mode == 0) {
			evf_mode = 1;
			err = EdsSetPropertyData(
								model->getCamera()
								,kEdsPropID_Evf_Mode
								,0
								,sizeof(evf_mode)
								,&evf_mode
			);
		}
		
		// Add PC as output device
		if (err == EDS_ERR_OK) {
			EdsUInt32 device = model->getEvfOutputDevice();
			device |= kEdsEvfOutputDevice_PC;
			err = EdsSetPropertyData(
								model->getCamera()
								,kEdsPropID_Evf_OutputDevice
								,0
								,sizeof(device)
								,&device
			);
			
		}
		
		// Show error:
		if(err != EDS_ERR_OK) {
			if(err == EDS_ERR_DEVICE_BUSY) {
				cout << "ERROR: Device is busy" << std::endl;
				return false;
			}
			else {
				cout << "ERROR: in ofxCanonCommandStartEvf " <<  ofxCanonErrorToString(err) << std::endl;
				
			}
		}
		cout << "ofxCanon: (command) started EVF" << std::endl;
		return true;
	}
};
#endif