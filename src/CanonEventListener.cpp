#include "CanonEventListener.h"
#include "CanonDebug.h"
#include "Canon.h"

namespace roxlu {

EdsError EDSCALLBACK CanonEventListener::handleObjectEvent(
							 EdsUInt32 inEvent
							,EdsBaseRef inRef
							,EdsVoid* inContext
)
{
	printf("Canon: handleObjectEvent '%s'.\n", CanonEventToString(inEvent));
	switch(inEvent) {
		case kEdsObjectEvent_DirItemRequestTransfer: {
			Canon::instance().downloadTakenPicture(inRef);
			break;
		}
		default: {
			if(inRef != NULL) {
				EdsRelease(inRef);
			}
			break;
		}
	};
	
	//CanonEventToString(EdsUInt32 nEventID, EdsUInt32 nEventParam = 0, EdsPropertyID nPropID = 0) {
	//kEdsObjectEvent_DirItemRequestTransfer
}
		
EdsError EDSCALLBACK CanonEventListener::handlePropertyEvent(
					 EdsUInt32 inEvent
					,EdsUInt32 inPropertyID
					,EdsUInt32 inParam
					,EdsVoid* inContext
)
{
	switch(inEvent) {
		case kEdsPropertyEvent_PropertyChanged: {
			/*
			if(inPropertyID == kEdsPropID_AvailableShots) {
				EdsUInt32 data;
				err = EdsGetPropertyData(Canon::instance().camera, kEdsPropID_AvailableShots, 0, data_size	,&data);
				printf("There are a couple of images available on the cam: %d\n", (int)inParam);
			}
			*/
			Canon::instance().getProperty(inPropertyID);
			break;
		};

		default:break;
	};
	printf("Canon: handlePropertyEvent '%s'.\n", CanonPropertyToString(inPropertyID));
}

EdsError EDSCALLBACK CanonEventListener::handleStateEvent(
					 EdsUInt32 inEvent
					,EdsUInt32 inParam
					,EdsVoid* inContext
)
{
	switch(inEvent) {
		// Connection with camera lost (maybe power off?)
		case kEdsStateEvent_Shutdown: {
			Canon::instance().shutdownSDK(true);
			break;	
		}
		default:break;
	};
	printf("Canon: handleStateEvent '%s'.\n", CanonEventToString(inEvent));
}
		


}; // roxlu