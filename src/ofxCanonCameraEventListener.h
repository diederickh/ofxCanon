#ifndef OFXCANONCAMERAEVENTLISTENERH
#define OFXCANONCAMERAEVENTLISTENERH

#include "EDSDK.h"
#include "ofxCanonController.h"
#include "ofxCanonDebug.h"

class ofxCanonCameraEventListener {
public:

	static EdsError EDSCALLBACK handleObjectEvent(
		EdsUInt32		inEvent
		,EdsBaseRef		inRef
		,EdsVoid*		inContext
	)
	{

		cout	<< "CAMERA_EVENT: handleObjectEvent: "
				<< ofxCanonEventToString(inEvent)
				<< std::endl;

		ofxCanonController* controller = (ofxCanonController *)inContext;
		switch(inEvent) {
			case kEdsObjectEvent_DirItemRequestTransfer:
				std::cout << "ofxCanon: (eventlistener): fire download event" << std::endl;
				fireEvent(controller, "download", inRef);
				break;
			default: {
				cout << "got event!" << std::endl;
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

		cout	<< "CAMERA_EVENT: handlePropertyEvent: "
				<< inPropertyID << " "
				<< ofxCanonEventToString(inEvent, 0, inPropertyID)
				<< std::endl;

		ofxCanonController* controller = (ofxCanonController*)inContext;

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


		cout	<< "CAMERA_EVENT: handleStateEvent: "
				<< ofxCanonEventToString(inEvent, inParam)
				<< std::endl;

		ofxCanonController* controller = (ofxCanonController*)inContext;
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
