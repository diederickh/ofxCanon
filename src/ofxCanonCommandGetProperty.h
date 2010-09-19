#ifndef OFXCANONCOMMANDGETPROPERTYH
#define OFXCANONCOMMANDGETPROPERTYH

#include "ofxCanonCommand.h"
#include "ofMain.h"
#include "ofxObservableEvent.h"
#include "ofxCanonDebug.h"

// @todo sometimes the "get focus info" property gets into a loop!

class ofxCanonCommandGetProperty : public ofxCanonCommand {
private:
	EdsPropertyID property;
	
public:
	ofxCanonCommandGetProperty(
			std::string sName
			,ofxCanonModel* pModel
			,EdsPropertyID nPropertyID
	):ofxCanonCommand(sName,pModel)
	,property(nPropertyID)
	{
		//std::cout << "Created get_property command" << std::endl;
	}
	
	virtual bool execute() {
		EdsError err = EDS_ERR_OK;
		
		bool locked = false;
		err = EdsSendStatusCommand(model->getCamera(), kEdsCameraStatusCommand_UILock, 0);
		if(err == EDS_ERR_OK) {
			locked = true;
		}
		
		err = getProperty(property);
						
		if(locked) {
			EdsSendStatusCommand(model->getCamera(), kEdsCameraStatusCommand_UIUnLock, 0);
		}
						
		// retry when busy.												
		if(err != EDS_ERR_OK) {
			if ( (err & EDS_ERRORID_MASK) == EDS_ERR_DEVICE_BUSY ) {
				std::cout << "Device is busy!!" << std::endl;
				//return false;				
			}
		}
	//	std::string prop = ofxCanonPropertyToString(property);
	//	std::cout << "Get property: " << prop << std::endl;

		return true;
	}
	
private:	
		EdsError getProperty(EdsPropertyID nPropertyID) {
		EdsError err = EDS_ERR_OK;
		EdsDataType	data_type = kEdsDataType_Unknown;
		EdsUInt32 data_size = 0;


		if(nPropertyID == kEdsPropID_Unknown) {
			//If unknown is returned for the property ID , the required 
			// property must be retrieved again
			if(err == EDS_ERR_OK) err = getProperty(kEdsPropID_AEMode);
			if(err == EDS_ERR_OK) err = getProperty(kEdsPropID_Tv);
			if(err == EDS_ERR_OK) err = getProperty(kEdsPropID_Av);
			if(err == EDS_ERR_OK) err = getProperty(kEdsPropID_ISOSpeed);
			if(err == EDS_ERR_OK) err = getProperty(kEdsPropID_MeteringMode);
			if(err == EDS_ERR_OK) err = getProperty(kEdsPropID_ExposureCompensation);
			if(err == EDS_ERR_OK) err = getProperty(kEdsPropID_ImageQuality);
			return err;
		}
	
		//Acquisition of the property size
		if(err == EDS_ERR_OK) {
			err = EdsGetPropertySize(
						model->getCamera()
						,nPropertyID
						,0
						,&data_type
						,&data_size 
			);
		}

		if(err == EDS_ERR_OK) {
			
			if(data_type == kEdsDataType_UInt32)	{
				EdsUInt32 data;
		
				//Acquisition of the property
				err = EdsGetPropertyData(
										model->getCamera()
										,nPropertyID
										,0
										,data_size
										,&data);

				//Acquired property value is set
				if(err == EDS_ERR_OK) {
					model->setPropertyUint32(nPropertyID, data);
				}
			}
			
			if(data_type == kEdsDataType_String)	{
				EdsChar str[EDS_MAX_NAME];
				//Acquisition of the property
				err = EdsGetPropertyData(
										model->getCamera()
										,nPropertyID
										,0
										,data_size
										,str);

				//Acquired property value is set
				if(err == EDS_ERR_OK) {
					model->setPropertyString(nPropertyID, str);
				}			
			}
			
			if(data_type == kEdsDataType_FocusInfo){
				EdsFocusInfo focus_info;
				//Acquisition of the property
				err = EdsGetPropertyData(
										model->getCamera()
										,nPropertyID
										,0
										,data_size
										,&focus_info);

				//Acquired property value is set
				if(err == EDS_ERR_OK) {
					model->setFocusInfo(focus_info);
				}
					
			}
		}

		//Update notification
		if(err == EDS_ERR_OK) {
			ofxObservableEvent e("property_changed", &nPropertyID);
			model->notifyObservers(&e);
		}
		else {
			// @todo maybe remove this completely, commented this because all
			// custom functions give an error.
			/*
			std::string prop = ofxCanonPropertyToString(nPropertyID);
			std::string message = ofxCanonErrorToString(err);
			cout << "ERROR_PROP:" << prop <<  " message: " << message << std::endl;
			*/
		}
		return err;
	}
};
#endif