#ifndef OFXCANONCOMMANDENDEFH
#define OFXCANONCOMMANDENDEFH

#include "ofxCanonCommand.h"
#include "ofMain.h"

class ofxCanonCommandEndEvf : public ofxCanonCommand {
public:
	ofxCanonCommandEndEvf(std::string sName, ofxCanonModel* pModel)
		:ofxCanonCommand(sName,pModel)
	{
	}

	virtual bool execute() {
		EdsError err = EDS_ERR_OK;

		// Do nothing when remote live view has already ended.
		EdsUInt32 device = model->getEvfOutputDevice();
		if( (device & kEdsEvfOutputDevice_PC) == 0)
			return true;

		EdsUInt32 dof = model->getEvfDepthOfFieldPreview();
		if (dof != 0) {
			dof = 0;
			err = EdsSetPropertyData(
				model->getCamera()
				,kEdsPropID_Evf_DepthOfFieldPreview
				,0
				,sizeof(dof)
				,&dof
			);

			// Standby because commands are not accepted for awhile when the depth of field has been released.
			if(err == EDS_ERR_OK) {
				ofSleepMillis(500);
			}
		}

		// Change output device
		if (err == EDS_ERR_OK) {
			device &= ~kEdsEvfOutputDevice_PC;
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
				//cout << "ERROR: Device is busy" << std::endl;
			}
			else {
				//cout << "ERROR: in ofxCanonCommandEndEvf " << err << std::endl;
			}
			// retry untill successful.
			return false;
		}
		return true;
	}
};
#endif
