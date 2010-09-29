#ifndef OFXCANONCAMERAEVENTLISTENERH
#define OFXCANONCAMERAEVENTLISTENERH

#include "EDSDK.h"
#include "ofxCanonController.h"
#include "ofxCanonDebug.h"
#include "ofxLog.h"
class ofxCanonCameraEventListener {
public:

	static EdsError EDSCALLBACK handleObjectEvent(
		EdsUInt32		inEvent
		,EdsBaseRef		inRef
		,EdsVoid*		inContext
	)
	{

		OFXLOG("ofxCanon: CAMERA_EVENT: handleObjectEvent: "
				<< ofxCanonEventToString(inEvent)
        );

		//ofxCanonController* controller = (ofxCanonController *)inContext;
		ofxCanonController* controller = static_cast<ofxCanonController*>(inContext);
		if(controller == NULL)
            return EDS_ERR_OK;

		switch(inEvent) {
			case kEdsObjectEvent_DirItemRequestTransfer:
				OFXLOG("ofxCanon: (eventlistener): fire download event.");
				fireEvent(controller, "download", inRef);
				break;
			default: {
				//cout << "got event!" << std::endl;
				if(inRef != NULL)
					EdsRelease(inRef);
				break;
			}
		}
		return EDS_ERR_OK;
	}

	static EdsError EDSCALLBACK handlePropertyEvent(
		EdsUInt32		inEvent
		,EdsUInt32		inPropertyID
		,EdsUInt32		inParam
		,EdsVoid* 		inContext
	)
	{
        OFXLOG("ofxCanon: CAMERA_EVENT: handlePropertyEvent: "
				<< inPropertyID << " "
				<< ofxCanonEventToString(inEvent, 0, inPropertyID)
        );
		//ofxCanonController* controller = (ofxCanonController*)inContext;
		ofxCanonController* controller = static_cast<ofxCanonController*>(inContext);
        if(controller == NULL)
            return EDS_ERR_OK;

		switch(inEvent) {
			case kEdsPropertyEvent_PropertyChanged:
				// @todo Do we need to handle this?
				fireEvent(controller, "get_property", &inPropertyID);
				break;

			case kEdsPropertyEvent_PropertyDescChanged:
				// @todo Do we need to handle this? (update the model?)
				break;
			default:break;
		};
		return EDS_ERR_OK;
	}

	static EdsError EDSCALLBACK handleStateEvent(
		EdsUInt32			inEvent
		,EdsUInt32			inParam
		,EdsVoid*			inContext
	)
	{

        OFXLOG("ofxCanon: CAMERA_EVENT: handleStateEvent: "
				<< ofxCanonEventToString(inEvent, inParam)
        );

		//ofxCanonController* controller = (ofxCanonController*)inContext;
		ofxCanonController* controller = static_cast<ofxCanonController*>(inContext);
		if(controller == NULL)
            return EDS_ERR_OK;

		switch(inEvent) {
			case kEdsStateEvent_WillSoonShutDown: {
				fireEvent(controller, "keep_alive");
				break;
			}
			case kEdsStateEvent_Shutdown: {
				fireEvent(controller, "shutdown");
				break;
			}
			case kEdsStateEvent_InternalError: {
				fireEvent(controller, "shutdown");
				break;
			}
		};
		return EDS_ERR_OK;
	}

private:
	static void fireEvent(
		ofxActionListener* pListener
		,std::string sCommand
		,void* pArg = 0
	)
	{
		ofxActionEvent event(sCommand, pArg);
		pListener->actionPerformed(event);

	}
};
#endif
