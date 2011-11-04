#include "Canon.h"

namespace roxlu {

ofEvent<CanonEvent> canon_event_dispatcher;
ofEvent<CanonPictureEvent> canon_picture_dispatcher;
Canon* Canon::instance_ = NULL;

Canon::Canon() 
:camera(NULL)
,camera_list(NULL)
,live_view_active(false)
,has_new_live_image(false)
,connection(this)
,session_open(false)
,live_view_requested(false)
{
	queue.setCanon(this);
	instance_ = this;
	memset(&prop_focus_info, 0, sizeof(prop_focus_info));
	addListener(this, &Canon::onCanonEvent);
}

Canon::~Canon() {
	shutdownSDK();
	queue.stop();
	queue_thread.join();
	
}

Canon& Canon::instance() {
	return *instance_;
}

void Canon::takePicture() {
	queue.addTask(new CanonTaskTakePicture());
}

void Canon::downloadTakenPicture(EdsBaseRef inRef) {
	queue.addTask(new CanonTaskDownloadPicture(inRef));	
}

bool Canon::start() {
	queue_thread.start(queue);
	connection_thread.start(connection);
	initSDK();
}

void Canon::initSDK() {
	if(camera != NULL) {
		printf("Canon: error, cannot initialize SDK as camera is not yet released\n");
		return;
	}
	queue.addTask(new CanonTaskInit());
	queue.addTask(new CanonTaskOpenSession());
}

void Canon::restartSDK() {
	queue.addTask(new CanonTaskCloseSession());
	queue.addTask(new CanonTaskShutdown());
	initSDK();
}

void Canon::shutdownSDK(bool isCameraOffline) {
	if(camera == NULL) {
		printf("Canon: error, it seems the camera is already released/shutdown.\n");
		return;
	}
	
	if(isCameraOffline) {
		printf("Canon: camera is offline........\n");
		queue.empty();
		EdsRelease(camera);
		printf("Canon: released camera: %p\n", camera);
		camera = NULL;
		live_view_active = false;
	}
	else {
	 	if(live_view_active) {
			queue.addTask(new CanonTaskEndEVF());
			live_view_active = false;
		}
		queue.addTask(new CanonTaskCloseSession());
	}
	
	// close sdk.
	queue.addTask(new CanonTaskShutdown());
}

bool Canon::isCameraConnected() {
	return camera != NULL;
}

void Canon::startLiveView() {
	live_view_requested = true;
	queue.addTask(new CanonTaskStartEVF());
}

void Canon::downloadEVF() {
	queue.addTask(new CanonTaskDownloadEVF());
}

void Canon::endLiveView() {
	live_view_requested = false;
	queue.addTask(new CanonTaskEndEVF());
}

ofPixels& Canon::getLivePixels() {
	return live_pixels;
}

string Canon::getDownloadDir() {
	return ofToDataPath("./",true);
}

void Canon::getProperty(EdsPropertyID propID) {
	queue.addTask(new CanonTaskGetProperty(propID));
}

void Canon::setPropertyUI32(EdsPropertyID propID, EdsUInt32 value) {
	switch(propID) 	{
		case kEdsPropID_AEMode:					setAEMode(value);					break;
		case kEdsPropID_Tv:						setTv(value);						break;		               
		case kEdsPropID_Av:						setAv(value);						break;           	  
		case kEdsPropID_ISOSpeed:				setIso(value);						break;       
		case kEdsPropID_MeteringMode:			setMeteringMode(value);				break;       
		case kEdsPropID_ExposureCompensation:	setExposureCompensation(value);		break;
		case kEdsPropID_ImageQuality:			setImageQuality(value);				break;
		case kEdsPropID_Evf_Mode:				setEvfMode(value);					break;
		case kEdsPropID_Evf_OutputDevice:		setEvfOutputDevice(value);			break;
		case kEdsPropID_Evf_DepthOfFieldPreview:setEvfDepthOfFieldPreview(value);	break;	
		case kEdsPropID_Evf_AFMode:				setEvfAFMode(value);				break;
		case kEdsPropID_AvailableShots: {
			printf("Canon: There are shots left on camera: %d - %p\n", (int)value, camera);
			break;
		};
	}
}

void Canon::setPropertyString(EdsPropertyID propID, EdsChar* str) {
	switch(propID) {
		case kEdsPropID_ProductName: setModelName(str); break;
	}

}

void Canon::setPropertyFocusInfo(EdsPropertyID propID, EdsFocusInfo info) {
	switch(propID) {
			case kEdsPropID_FocusInfo: setFocusInfo(info);  break;
	}
}

void Canon::drawLiveView(int x, int y) {
	if(has_new_live_image) {
		if(live_texture.getWidth() != live_pixels.getWidth()
			|| live_texture.getHeight() != live_pixels.getHeight()
		)
		{
			live_texture.allocate(live_pixels.getWidth(), live_pixels.getHeight(), GL_RGB8);
		}
		live_texture.loadData(live_pixels);
		has_new_live_image = false;
	}
	live_texture.draw(x,y);
}

void Canon::onCanonEvent(CanonEvent& ev) {
	if(ev.name == "evf_data_changed") {
		EdsUInt32 length;
		unsigned char* image_data;

		EvfDataSet* evf_data = static_cast<EvfDataSet*>(ev.data);
		EdsGetLength(evf_data->stream, &length);
		EdsGetPointer(evf_data->stream, (EdsVoid**)&image_data);
		
		live_buffer.set((char*)image_data, length);
		ofLoadImage(live_pixels, live_buffer);
		has_new_live_image = true;

		downloadEVF();
	}
	
	// the flow how we setup EVF is correct, but a bit nasty. What we do, is
	// change the "kEdsPropID_Evf_OutputDevice" to PC. This is done in 
	// CanonTaskStartEVF. Then the async call is made to update the property 
	// value on the Canon device. when it's changed we fire an event in 
	// CanonTaskGetProperty and handle this here.
	else if(ev.name == "property_changed") {
		
		EdsInt32 prop_id = *static_cast<EdsInt32*>(ev.data);
		if(prop_id == kEdsPropID_Evf_OutputDevice) {
			EdsUInt32 device = getEvfOutputDevice();
			if(!live_view_active && (device & kEdsEvfOutputDevice_PC) != 0) {
				printf("Start downloading EVF\n");
				live_view_active = true;
				downloadEVF();
			}
			
			if(live_view_active && (device & kEdsEvfOutputDevice_PC) == 0) {
				printf("Canon: live view deactivated.\n");
				live_view_active = false; 
			}
		}
	}
}

void Canon::fireEvent(CanonEvent& ev) {
	ofNotifyEvent(canon_event_dispatcher, ev);
}

void Canon::firePictureTakenEvent(CanonPictureEvent& ev) {
	ofNotifyEvent(canon_picture_dispatcher, ev);
}

void Canon::setSessionOpen(bool isOpen) {
	session_open = isOpen;
}

bool Canon::isSessionOpen() {
	return session_open;
}

bool Canon::isLiveViewActive() {
	return live_view_requested;
}

}; // roxlu