#ifndef ROXLU_CANONH
#define ROXLU_CANONH

#include <Poco/Thread.h>
#include <Poco/Runnable.h>

#include "CanonTaskQueue.h"
#include "CanonTaskInit.h"
#include "CanonTaskShutdown.h"
#include "CanonTaskOpenSession.h"
#include "CanonTaskCloseSession.h"
#include "CanonTaskTakePicture.h"
#include "CanonTaskDownloadPicture.h"
#include "CanonTaskGetProperty.h"
#include "CanonTaskStartEVF.h"
#include "CanonTaskDownloadEVF.h"
#include "CanonTaskEndEVF.h"
#include "CanonSDK.h"
#include "CanonEvent.h"
#include "CanonPictureEvent.h"
#include "CanonConnection.h"
#include "ofMain.h"

namespace roxlu {

	extern ofEvent<CanonEvent> canon_event_dispatcher;
	extern ofEvent<CanonPictureEvent> canon_picture_dispatcher;
	
	class Canon {
		public:
			Canon();
			~Canon();
			
			bool start();
			bool isCameraConnected();
			void takePicture();
			string getDownloadDir(); 
            void setFileName(string newFileName);
            string getFileName();
			
			bool isSessionOpen();
			bool isLiveViewActive();
			void startLiveView();
			void endLiveView();
			void drawLiveView(int x = 0, int y = 0);
            void drawLiveViewWithSize(int x, int y, int w, int h);
			ofPixels& getLivePixels();
			
			static Canon& instance();
			
			EdsUInt32 getAEMode() const					{ return prop_ae_mode; }
			EdsUInt32 getTv() const						{ return prop_tv; }
			EdsUInt32 getAv() const						{ return prop_av; }
			EdsUInt32 getIso() const					{ return prop_iso; }
			EdsUInt32 getMeteringMode() const			{ return prop_metering_mode; }
			EdsUInt32 getExposureCompensation() const	{ return prop_exposure_compensation; }
			EdsUInt32 getImageQuality() const			{ return prop_image_quality; }
			EdsUInt32 getEvfMode() const				{ return prop_evf_mode; }
			EdsUInt32 getEvfOutputDevice() const		{ return prop_evf_output_device; }
			EdsUInt32 getEvfDepthOfFieldPreview() const	{ return prop_evf_dof_preview; }
			EdsUInt32 getEvfZoom() const				{ return prop_evf_zoom; }	
			EdsPoint  getEvfZoomPosition() const		{ return prop_evf_zoom_position; }	
			EdsRect	  getEvfZoomRect() const			{ return prop_evf_zoom_rect; }	
			EdsUInt32 getEvfAFMode() const				{ return prop_evf_af_mode; }
			EdsChar *getModelName()						{ return prop_model_name; }
			EdsFocusInfo getFocusInfo()const			{ return prop_focus_info; }
			
			EdsCameraRef camera;
			EdsCameraListRef camera_list;
			
			// add new picture event listener.
			template <typename ArgumentsType, class ListenerClass>
			static void addPictureTakenListener(ListenerClass* listener	,void (ListenerClass::*listenerMethod)(ArgumentsType&))	{
				ofAddListener(canon_picture_dispatcher, listener, listenerMethod);
			}
			
			friend class CanonEventListener;
			friend class CanonTaskGetProperty;
			friend class CanonTaskDownloadEVF;
			friend class CanonConnection;
			friend class CanonTaskDownloadPicture;
			friend class CanonTaskOpenSession;
			friend class CanonTaskCloseSession;
		private:
			void initSDK(); 
			void shutdownSDK(bool isCameraOffline = false); 
			void restartSDK(); 

			void downloadTakenPicture(EdsBaseRef inRef);
			void downloadEVF();
			
			void setSessionOpen(bool isOpen);
			
			
			// add an event listener.
			template <typename ArgumentsType, class ListenerClass>
			static void addListener(ListenerClass* listener	,void (ListenerClass::*listenerMethod)(ArgumentsType&))	{
				ofAddListener(canon_event_dispatcher, listener, listenerMethod);
			}
			
			// our own event listener.
			void fireEvent(CanonEvent& ev);
			void firePictureTakenEvent(CanonPictureEvent& ev);
			void onCanonEvent(CanonEvent& ev);
		
				
			void getProperty(EdsPropertyID propID); // when opening the session the camera tells us what properties we can retrieve. (must Friend with event listener);
			void setPropertyUI32(EdsPropertyID propID, EdsUInt32 data); // must be private friend with getProperty task
			void setPropertyString(EdsPropertyID propID, EdsChar* str); // must be private friend with getProperty task
			void setPropertyFocusInfo(EdsPropertyID propID, EdsFocusInfo focusInfo); // must be private friend with getProperty task
	
			void setAEMode(EdsUInt32 value )				{ prop_ae_mode = value;}
			void setTv( EdsUInt32 value )					{ prop_tv = value;}
			void setAv( EdsUInt32 value )					{ prop_av = value;}
			void setIso( EdsUInt32 value )					{ prop_iso = value; }
			void setMeteringMode( EdsUInt32 value )			{ prop_metering_mode = value; }
			void setExposureCompensation( EdsUInt32 value)	{ prop_exposure_compensation = value; }
			void setImageQuality( EdsUInt32 value)			{ prop_image_quality = value; }
			void setEvfMode( EdsUInt32 value)				{ prop_evf_mode = value; }
			void setEvfOutputDevice( EdsUInt32 value)		{ prop_evf_output_device = value; }
			void setEvfDepthOfFieldPreview( EdsUInt32 value){ prop_evf_dof_preview = value; }
			void setEvfZoom( EdsUInt32 value)				{ prop_evf_zoom = value; }
			void setEvfZoomPosition( EdsPoint value)		{ prop_evf_zoom_position = value; }
			void setEvfZoomRect( EdsRect value)				{ prop_evf_zoom_rect = value; }
			void setModelName(EdsChar *modelName)			{ strcpy(prop_model_name, modelName); }
			void setEvfAFMode( EdsUInt32 value)				{ prop_evf_af_mode = value; }
			void setFocusInfo( EdsFocusInfo value)			{ prop_focus_info = value; }

			CanonConnection connection;
			CanonTaskQueue queue;
			Poco::Thread queue_thread;
			Poco::Thread connection_thread;
			static Canon* instance_;
			bool live_view_active;
			bool live_view_requested;
			bool has_new_live_image;
			bool session_open;
            string file_name;
			ofBuffer live_buffer;
			ofTexture live_texture;
			ofPixels live_pixels;
			
			// model
			EdsUInt32 prop_ae_mode;
			EdsUInt32 prop_av;
			EdsUInt32 prop_tv;
			EdsUInt32 prop_iso;
			EdsUInt32 prop_metering_mode;
			EdsUInt32 prop_exposure_compensation;
			EdsUInt32 prop_image_quality;
			EdsUInt32 prop_available_shot;
			EdsUInt32 prop_evf_mode;
			EdsUInt32 prop_evf_output_device;
			EdsUInt32 prop_evf_dof_preview;
			EdsUInt32 prop_evf_zoom;
			EdsPoint  prop_evf_zoom_position;
			EdsRect	  prop_evf_zoom_rect;;
			EdsUInt32 prop_evf_af_mode;
			EdsFocusInfo prop_focus_info;
			EdsChar prop_model_name[EDS_MAX_NAME];
	};
} // roxlu
#endif