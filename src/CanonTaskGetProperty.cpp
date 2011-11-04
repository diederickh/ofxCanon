#include "CanonTaskGetProperty.h"
#include "Canon.h"

namespace roxlu {

bool CanonTaskGetProperty::execute() {
	EdsError err = EDS_ERR_OK;
	
	err = getProperty(property_id);

	if(err != EDS_ERR_OK) {
		printf("Canon: error while retrieving property.\n");
		if((err & EDS_ERRORID_MASK) == EDS_ERR_DEVICE_BUSY ) {
			return false;
		}
		
		
	}
	return true;
}

EdsError CanonTaskGetProperty::getProperty(EdsPropertyID propID) {
	EdsError err = EDS_ERR_OK;
	EdsDataType data_type = kEdsDataType_Unknown;
	EdsUInt32 data_size = 0;
	
	if(propID == kEdsPropID_Unknown) {
		// If unknown is returned, the requied property must be retrieved again.
		if(err == EDS_ERR_OK) err = getProperty(kEdsPropID_AEMode);
		if(err == EDS_ERR_OK) err = getProperty(kEdsPropID_Tv);
		if(err == EDS_ERR_OK) err = getProperty(kEdsPropID_Av);
		if(err == EDS_ERR_OK) err = getProperty(kEdsPropID_ISOSpeed);
		if(err == EDS_ERR_OK) err = getProperty(kEdsPropID_MeteringMode);
		if(err == EDS_ERR_OK) err = getProperty(kEdsPropID_ExposureCompensation);
		if(err == EDS_ERR_OK) err = getProperty(kEdsPropID_ImageQuality);
		return err;
	}
	
	// Get size of property.
	if(err == EDS_ERR_OK) {
		err = EdsGetPropertySize(
			Canon::instance().camera
			,propID
			,0
			,&data_type
			,&data_size
		);
	}
	
	if(err == EDS_ERR_OK) {
		// set UI32
		if(data_type == kEdsDataType_UInt32) {
			EdsUInt32 data;
			err = EdsGetPropertyData(Canon::instance().camera, propID, 0, data_size	,&data);
			if(err == EDS_ERR_OK) {
				printf("Canon: set property (ui32): %d.\n", (int)propID);
				Canon::instance().setPropertyUI32(propID, data);
			}
			else {
				printf("Canon: error while retrieving ui32 property '%s'.\n", CanonErrorToString(err));
			}
		}
		
		// set string
		else if(data_type == kEdsDataType_String) {
			EdsChar str[EDS_MAX_NAME];
			err = EdsGetPropertyData(Canon::instance().camera, propID, 0, data_size, str);
			if(err == EDS_ERR_OK) {
				printf("Canon: set property (string): %s\n", str);
				Canon::instance().setPropertyString(propID, str);
			}
			else {
				printf("Canon: error while retrieving string property.\n");
			}
		}
		
		// focus info
		else if(data_type == kEdsDataType_FocusInfo) {
			EdsFocusInfo focus_info;
			err = EdsGetPropertyData(Canon::instance().camera, propID, 0, data_size, &focus_info);
			if(err == EDS_ERR_OK) {
				printf("Canon: set property (focus info)\n");
				Canon::instance().setPropertyFocusInfo(propID, focus_info);
			}
			else {
				printf("Canon: error while retrieving string property.\n");
			}

		}
	}
	
	
	if(err == EDS_ERR_OK) {
		CanonEvent ev("property_changed", &propID);
		canon->fireEvent(ev);
	}

	
	return err;
}


}; // roxlu
