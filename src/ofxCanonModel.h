#ifndef OFXCANONMODELH
#define OFXCANONMODELH
#include <string>
#include "EDSDK.h"
#include "ofxObserver.h"

using namespace std;
class ofxCanonModel : public ofxObservable {
public:
	ofxCanonModel()
		:tv(0)
		,av(0)
		,iso(0)
		,metering_mode(0)
		,exposure_compensation(0)
		,image_quality(0)
		,evf_mode(0)
		,evf_output_device(0)
		,evf_dof(0)
		,evf_zoom(0)
		,keep_alive(true)
		,download_dir("../../../data/images/") // end with slash! (defaults for Mac app dir)
	{
		memset(&focus_info, 0, sizeof(focus_info));
	}

    ~ofxCanonModel() {
        deleteObservers();
    }

	EdsCameraRef getCamera() const			{ return  camera; }
	EdsUInt32 getEvfMode()					{ return evf_mode; }

	// Taking a picture parameter
	void setTv( EdsUInt32 nTV )							{ tv					= nTV;				}
	void setAv( EdsUInt32 nAV )							{ av					= nAV;				}
	void setIso( EdsUInt32 nISO )						{ iso					= nISO;				}
	void setMeteringMode( EdsUInt32 nMeteringMode )		{ metering_mode			= nMeteringMode;	}
	void setExposureCompensation( EdsUInt32 nExp)		{ exposure_compensation = nExp;				}
	void setImageQuality( EdsUInt32 nQuality)			{ image_quality			= nQuality;			}
	void setEvfMode( EdsUInt32 nEvfMode)				{ evf_mode				= nEvfMode;			}
	void setEvfOutputDevice( EdsUInt32 nDevice)			{ evf_output_device		= nDevice;			}
	void setEvfDepthOfFieldPreview( EdsUInt32 nDOF)		{ evf_dof				= nDOF;				}
	void setEvfZoom( EdsUInt32 nZoom)					{ evf_zoom				= nZoom;			}
	void setEvfZoomPosition( EdsPoint nPosition)		{ evf_zoom_position		= nPosition;		}
	void setEvfZoomRect( EdsRect nRect)					{ evf_zoom_rect			= nRect;			}
	void setEvfAFMode( EdsUInt32 nAFMode)				{ evf_af_mode			= nAFMode;			}
	void setFocusInfo( EdsFocusInfo oFocusInfo)			{ focus_info			= oFocusInfo;		}
	void setAEMode(EdsUInt32 nAEMode)					{ ae_mode				= nAEMode;			}
	void setKeepAlive(bool bKeepAlive)					{ keep_alive			= bKeepAlive;		}
	void setModelName(EdsChar *sModelName)				{ strcpy(model_name, sModelName);			}
	void setDownloadDir(string sDir)					{ download_dir			= sDir;				}
	void setCamera(EdsCameraRef oCamera)				{ camera				= oCamera;			}
	void setSessionOpen(bool bIsSessionOpen)			{ session_open			= bIsSessionOpen;	}
	void setEvfFlip(bool bFlipH, bool bFlipV)			{
		flip_evf_vertical = bFlipV;
		flip_evf_horizontal = bFlipH;
	}

	// Taking a picture parameter
	EdsUInt32 getAEMode() const							{ return ae_mode;				}
	EdsUInt32 getTv() const								{ return tv;					}
	EdsUInt32 getAv() const								{ return av;					}
	EdsUInt32 getIso() const							{ return iso;					}
	EdsUInt32 getMeteringMode() const					{ return metering_mode;			}
	EdsUInt32 getExposureCompensation() const			{ return exposure_compensation; }
	EdsUInt32 getImageQuality() const					{ return image_quality;			}
	EdsUInt32 getEvfMode() const						{ return evf_mode;				}
	EdsUInt32 getEvfOutputDevice() const				{ return evf_output_device;		}
	EdsUInt32 getEvfDepthOfFieldPreview() const			{ return evf_dof;				}
	EdsUInt32 getEvfZoom() const						{ return evf_zoom;				}
	EdsPoint  getEvfZoomPosition() const				{ return evf_zoom_position;		}
	EdsRect	  getEvfZoomRect() const					{ return evf_zoom_rect;			}
	EdsUInt32 getEvfAFMode() const						{ return evf_af_mode;			}
	EdsFocusInfo getFocusInfo()const					{ return focus_info;			}
	EdsChar	*getModelName()								{ return model_name;			}
	bool	getKeepAlive()	const						{ return keep_alive;			}
	string	getDownloadDir() const						{ return download_dir;			}
	bool	isSessionOpen() const						{ return session_open;			}
	bool	flipEvfHorizontal()	const					{ return flip_evf_horizontal;	}
	bool	flipEvfVertical() const						{ return flip_evf_vertical;		}


	void setPropertyUint32(EdsUInt32 nPropertyID, EdsUInt32 nValue) {
		switch(nPropertyID) {
			case kEdsPropID_AEMode:					setAEMode(nValue);					break;
			case kEdsPropID_Tv:						setTv(nValue);						break;
			case kEdsPropID_Av:						setAv(nValue);						break;
			case kEdsPropID_ISOSpeed:				setIso(nValue);						break;
			case kEdsPropID_MeteringMode:			setMeteringMode(nValue);			break;
			case kEdsPropID_ExposureCompensation:	setExposureCompensation(nValue);	break;
			case kEdsPropID_ImageQuality:			setImageQuality(nValue);			break;
			case kEdsPropID_Evf_Mode:				setEvfMode(nValue);					break;
			case kEdsPropID_Evf_OutputDevice:		setEvfOutputDevice(nValue);			break;
			case kEdsPropID_Evf_DepthOfFieldPreview:setEvfDepthOfFieldPreview(nValue);	break;
			case kEdsPropID_Evf_AFMode:				setEvfAFMode(nValue);				break;
		}
	}

	void setPropertyString(EdsUInt32 nPropertyID, EdsChar* pStr) {
		/*
		switch(nPropertyID) {
			case kEdsPropID_ProductName:			setModelName(pStr);					break;
		}
		*/
	}

	void setPropertyFocusInfo(EdsUInt32 nPropertyID, EdsFocusInfo oInfo) {
		switch(nPropertyID) {
			case kEdsPropID_FocusInfo:				setFocusInfo(oInfo);				break;
		}
	}

private:

	string			download_dir;
	bool			keep_alive; // when set to true the controller should add  a keep alive command when we receive a shutdown event.
	EdsCameraRef	camera;
	EdsUInt32		ae_mode;
	EdsUInt32		tv;
	EdsUInt32		av;
	EdsUInt32		iso;
	EdsUInt32		metering_mode;
	EdsUInt32		exposure_compensation;
	EdsUInt32		image_quality;
	EdsUInt32		evf_mode;
	EdsUInt32		evf_output_device;
	EdsUInt32		evf_dof;
	EdsUInt32		evf_zoom;
	EdsPoint		evf_zoom_position;
	EdsRect			evf_zoom_rect;
	EdsUInt32		evf_af_mode;
	EdsFocusInfo	focus_info;
	EdsChar*		model_name;
	bool			session_open;
	bool			flip_evf_horizontal;
	bool			flip_evf_vertical;

};
#endif
