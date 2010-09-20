#ifndef OFXCANONDEBUGH
#define OFXCANONDEBUGH

#include "EDSDK.h"
#include <string>
inline const char* ofxCanonPropertyToString(EdsPropertyID nPropID);
inline const char* ofxCanonEventToString(EdsUInt32 nEventID, EdsUInt32 nEventParam = 0, EdsPropertyID nPropID = 0) {
	switch(nEventID) {
		case kEdsStateEvent_Shutdown:					return "Camera disconnected";
		case kEdsObjectEvent_DirItemCreated:			return "Directory item created";
		case kEdsObjectEvent_DirItemRemoved:			return "Directory item removed";
		case kEdsObjectEvent_DirItemInfoChanged:		return "Directory item changed";
		case kEdsObjectEvent_DirItemContentChanged:		return "Header information of directory item changed";
		case kEdsObjectEvent_VolumeInfoChanged:			return "Changes in the volume information of recording media";
		case kEdsObjectEvent_VolumeUpdateItems:			return "Notification of requests to update volume information";
		case kEdsObjectEvent_FolderUpdateItems:			return "Notification of requests to update folder information";
		case kEdsObjectEvent_DirItemRequestTransfer:	return "Notification of file transfer requests";
		case kEdsObjectEvent_DirItemRequestTransferDT:	return "Notification of direct transfer requests";
		case kEdsObjectEvent_DirItemCancelTransferDT:	return "Notification of requests to cancel direct transfer";
		case kEdsStateEvent_WillSoonShutDown:			return "Notification of warnings when the camera will shut off";
		case kEdsStateEvent_ShutDownTimerUpdate:		return "Notification that the camera will remain on for a longer period";
		case kEdsStateEvent_CaptureError:				return "Notification of remote release failure";
		case kEdsStateEvent_BulbExposureTime:			return "Notifies of the exposure time during bulb shooting.";
		case kEdsStateEvent_InternalError:				return "Notification of internal SDK errors";


		case kEdsStateEvent_JobStatusChanged: {
			if(nEventParam == 1) {
				return "Notification of changes in job states: there are objects to be transferred";
			}
			else if(nEventParam == 0) {
				return "Notification of changes in job states: NO tranfsers available";
			}

		}

		case kEdsPropertyEvent_PropertyChanged: {
			std::string prop_msg = ofxCanonPropertyToString(nPropID);
			std::string msg = "Property changed >> " +prop_msg;
			return msg.c_str();
		}

		case kEdsPropertyEvent_PropertyDescChanged: {
			return "Property description changed";
		}

		default:break;
	};
	return "Unknown";
}

inline const char* ofxCanonPropertyToString(EdsPropertyID nPropID) {
	switch(nPropID) {
		case kEdsPropID_Unknown: {
			return "Unknown property ID";
		}
		case kEdsPropID_ProductName: {
			return "Productname";
		}
		case kEdsPropID_BodyID: {
			return "Body ID";
		}
		case kEdsPropID_OwnerName: {
			return "Owner name";
		}
		case kEdsPropID_MakerName: {
			return "Make name";
		}
		case kEdsPropID_DateTime: {
			return "Date time";
		}
		case kEdsPropID_FirmwareVersion: {
			return "Firmware verion";
		}
		case kEdsPropID_BatteryLevel: {
			return "Battery level";
		}
		case kEdsPropID_CFn: {
			return "Custom function settings";
		}
		case kEdsPropID_SaveTo: {
			return "Destination where image was saved";
		}
		case kEdsPropID_CurrentStorage: {
			return "Current storage";
		}
		case kEdsPropID_CurrentFolder: {
			return "Current folder";
		}
		case kEdsPropID_MyMenu: {
			return "My menu";
		}
		case kEdsPropID_BatteryQuality: {
			return "Battery quality";
		}
		case kEdsPropID_HDDirectoryStructure: {
			return "HDD directory structure";
		}
		case kEdsPropID_ImageQuality: {
			return "Image quality";
		}
		case kEdsPropID_JpegQuality: {
			return "JPEG quality";
		}
		case kEdsPropID_Orientation: {
			return "Orientation";
		}
		case kEdsPropID_ICCProfile: {
			return "ICC profile";
		}
		case kEdsPropID_FocusInfo: {
			return "Focus info";
		}
		case kEdsPropID_DigitalExposure: {
			return "Digital exposure";
		}
		case kEdsPropID_WhiteBalance: {
			return "White balance";
		}
		case kEdsPropID_ColorTemperature: {
			return "Color temperature";
		}
		case kEdsPropID_WhiteBalanceShift: {
			return "White balance shift";
		}
		case kEdsPropID_Contrast: {
			return "Contrast";
		}
		case kEdsPropID_ColorSaturation: {
			return "Color staturation";
		}
		case kEdsPropID_ColorTone: {
			return "Color tone";
		}
		case kEdsPropID_Sharpness: {
			return "Sharpness";
		}
		case kEdsPropID_ColorSpace: {
			return "Color space";
		}
		case kEdsPropID_ToneCurve: {
			return "Tone curve";
		}
		case kEdsPropID_PhotoEffect: {
			return "Photo effect";
		}
		case kEdsPropID_FilterEffect: {
			return "Filter effect";
		}
		case kEdsPropID_ToningEffect: {
			return "Toning effect";
		}
		case kEdsPropID_ParameterSet: {
			return "Parameter set";
		}
		case kEdsPropID_ColorMatrix: {
			return "Color matrix";
		}
		case kEdsPropID_PictureStyle: {
			return "Picture style";
		}
		case kEdsPropID_PictureStyleDesc: {
			return "Picture style desc";
		}
		case kEdsPropID_ETTL2Mode: {
			return "ETTL2Mode";
		}
		case kEdsPropID_PictureStyleCaption: {
			return "Picture style caption";
		}
		case kEdsPropID_Linear: {
			return "Linear";
		}
		case kEdsPropID_ClickWBPoint: {
			return "Click WBPoint";
		}
		case kEdsPropID_WBCoeffs: {
			return "WB Coeffs";
		}
		case kEdsPropID_GPSVersionID: {
			return "GPS version ID";
		}
		case kEdsPropID_GPSLatitudeRef: {
			return "GPS latitude ref";
		}
		case kEdsPropID_GPSLatitude: {
			return "GPS latititude ";
		}
		case kEdsPropID_GPSLongitudeRef: {
			return "GPS longitude ref";
		}
		case kEdsPropID_GPSLongitude: {
			return "GPS longitude";
		}
		case kEdsPropID_GPSAltitudeRef: {
			return "GPS altitude ref";
		}
		case kEdsPropID_GPSAltitude: {
			return "GPS altitude";
		}
		case kEdsPropID_GPSTimeStamp: {
			return "GPS timestamp";
		}
		case kEdsPropID_GPSSatellites: {
			return "GPS Satellites";
		}
		case kEdsPropID_GPSStatus: {
			return "GPS status";
		}
		case kEdsPropID_GPSMapDatum: {
			return "GPS map datum";
		}
		case kEdsPropID_GPSDateStamp: {
			return "GPS Datestamp";
		}
		case kEdsPropID_AtCapture_Flag: {
			return "At capture flag";
		}
		case kEdsPropID_AEMode: {
			return "AE mode";
		}
		case kEdsPropID_DriveMode: {
			return "Drive mode";
		}
		case kEdsPropID_ISOSpeed: {
			return "ISO speed";
		}
		case kEdsPropID_MeteringMode: {
			return "Meteringmode";
		}
		case kEdsPropID_AFMode: {
			return "AF mode";
		}
		case kEdsPropID_Av: {
			return "AV";
		}
		case kEdsPropID_Tv: {
			return "TV";
		}
		case kEdsPropID_ExposureCompensation: {
			return "Exposure compensation";
		}
		case kEdsPropID_FlashCompensation: {
			return "Flash compensation";
		}
		case kEdsPropID_FocalLength: {
			return "Focal length";
		}
		case kEdsPropID_AvailableShots: {
			return "Available shots";
		}
		case kEdsPropID_Bracket: {
			return "Bracket";
		}
		case kEdsPropID_WhiteBalanceBracket: {
			return "White balance bracket";
		}
		case kEdsPropID_LensName: {
			return "Lensname";
		}
		case kEdsPropID_AEBracket: {
			return "AE bracket";
		}
		case kEdsPropID_FEBracket: {
			return "FE bracket";
		}
		case kEdsPropID_ISOBracket: {
			return "ISO bracket";
		}
		case kEdsPropID_NoiseReduction: {
			return "Noise reduction";
		}
		case kEdsPropID_FlashOn: {
			return "Flash on";
		}
		case kEdsPropID_RedEye: {
			return "Red eye";
		}
		case kEdsPropID_FlashMode: {
			return "Flash mode";
		}
		case kEdsPropID_LensStatus: {
			return "Lens status";
		}
		case kEdsPropID_Artist: {
			return "Artist";
		}
		case kEdsPropID_Copyright: {
			return "Copyright";
		}
		case kEdsPropID_DepthOfField: {
			return "Depth of field";
		}
		case kEdsPropID_EFCompensation: {
			return "EF compensation";
		}
		case kEdsPropID_Evf_OutputDevice: {
			return "Evf output device";
		}
		case kEdsPropID_Evf_Mode: {
			return "Evf mode";
		}
		case kEdsPropID_Evf_WhiteBalance: {
			return "Evf white balance";
		}
		case kEdsPropID_Evf_ColorTemperature: {
			return "Evf color temperature";
		}
		case kEdsPropID_Evf_DepthOfFieldPreview: {
			return "Evf depth of field preview";
		}
		case kEdsPropID_Evf_Zoom: {
			return "Evf zoom";
		}
		case kEdsPropID_Evf_ZoomPosition: {
			return "Evf zoom position";
		}
		case kEdsPropID_Evf_FocusAid: {
			return "Evf focus aid";
		}
		case kEdsPropID_Evf_Histogram: {
			return "Evf historgram";
		}
		case kEdsPropID_Evf_ImagePosition: {
			return "Evf image position";
		}
		case kEdsPropID_Evf_HistogramStatus: {
			return "Evf histogram status";
		}
		case kEdsPropID_Evf_AFMode: {
			return "Evf AF mode";
		}
		case kEdsPropID_Evf_CoordinateSystem: {
			return "Evf coordinate system";
		}
		case kEdsPropID_Evf_ZoomRect: {
			return "Evf zoomrect";
		}

		default:break;
	};
	return "Unkown property ID.";
}


inline const char* ofxCanonErrorToString(EdsError nError) {
	switch(nError) {
		case EDS_ISSPECIFIC_MASK: {
			return "General: isspecific mask";
		}
		case EDS_COMPONENTID_MASK: {
			return "General: component id mask";
		}
		case EDS_RESERVED_MASK: {
			return "General: reserved mask";
		}
		case EDS_ERRORID_MASK: {
			return "General: error id mask";
		}
		case EDS_CMP_ID_CLIENT_COMPONENTID: {
			return "ID client";
		}
		case EDS_CMP_ID_LLSDK_COMPONENTID: {
			return "LLSDK";
		}
		case EDS_CMP_ID_HLSDK_COMPONENTID: {
			return "HLSDK";
		}
		case EDS_ERR_OK: {
			return "OK";
		}
		case EDS_ERR_UNIMPLEMENTED: {
			return "Unimplemented";
		}
		case EDS_ERR_INTERNAL_ERROR: {
			return "Internal error";
		}
		case EDS_ERR_MEM_ALLOC_FAILED: {
			return "Mem alloc failed";
		}
		case EDS_ERR_MEM_FREE_FAILED: {
			return "Mem free failed";
		}
		case EDS_ERR_OPERATION_CANCELLED: {
			return "Operation cancelled";
		}
		case EDS_ERR_INCOMPATIBLE_VERSION: {
			return "Incompatible version";
		}
		case EDS_ERR_NOT_SUPPORTED: {
			return "Not supported";
		}
		case EDS_ERR_UNEXPECTED_EXCEPTION: {
			return "Unexpected exception";
		}
		case EDS_ERR_PROTECTION_VIOLATION: {
			return "Protection violation";
		}
		case EDS_ERR_MISSING_SUBCOMPONENT: {
			return "Missing subcomponent";
		}
		case EDS_ERR_SELECTION_UNAVAILABLE: {
			return "Selection unavailable";
		}
		case EDS_ERR_FILE_IO_ERROR: {
			return "IO Error";
		}
		case EDS_ERR_FILE_TOO_MANY_OPEN: {
			return "IO Error: too many open";
		}
		case EDS_ERR_FILE_NOT_FOUND: {
			return "IO Error: not found";
		}
		case EDS_ERR_FILE_OPEN_ERROR: {
			return "IO Error: open error";
		}
		case EDS_ERR_FILE_CLOSE_ERROR: {
			return "IO Error: close error";
		}
		case EDS_ERR_FILE_SEEK_ERROR: {
			return "IO Error: seek error";
		}
		case EDS_ERR_FILE_TELL_ERROR: {
			return "IO Error: tell error";
		}
		case EDS_ERR_FILE_READ_ERROR: {
			return "IO Error: read error";
		}
		case EDS_ERR_FILE_WRITE_ERROR: {
			return "IO Error: write error";
		}
		case EDS_ERR_FILE_PERMISSION_ERROR: {
			return "IO Error: permission error";
		}
		case EDS_ERR_FILE_DISK_FULL_ERROR: {
			return "IO Error: disk full";
		}
		case EDS_ERR_FILE_ALREADY_EXISTS: {
			return "IO Error: file already exists";
		}
		case EDS_ERR_FILE_FORMAT_UNRECOGNIZED: {
			return "IO Error: file format not recognized";
		}
		case EDS_ERR_FILE_DATA_CORRUPT: {
			return "IO Error: data corrup";
		}
		case EDS_ERR_FILE_NAMING_NA: {
			return "IO Error: file naming na";
		}
		case EDS_ERR_DIR_NOT_FOUND: {
			return "Dir error: dir not found";
		}
		case EDS_ERR_DIR_IO_ERROR: {
			return "Dir error: io error";
		}
		case EDS_ERR_DIR_ENTRY_NOT_FOUND: {
			return "Dir error: entry not found";
		}
		case EDS_ERR_DIR_ENTRY_EXISTS: {
			return "'Dir error: entry exists";
		}
		case EDS_ERR_DIR_NOT_EMPTY: {
			return "Dir error: not empty";
		}
		case EDS_ERR_PROPERTIES_UNAVAILABLE: {
			return "Property: unavailable";
		}
		case EDS_ERR_PROPERTIES_MISMATCH: {
			return "Property: mismatch";
		}
		case EDS_ERR_PROPERTIES_NOT_LOADED: {
			return "Property: not loaded";
		}
		case EDS_ERR_INVALID_PARAMETER: {
			return "Invalid parameter";
		}
		case EDS_ERR_INVALID_HANDLE: {
			return "Invalid handle";
		}
		case EDS_ERR_INVALID_POINTER: {
			return "Invalid pointer";
		}
		case EDS_ERR_INVALID_INDEX: {
			return "Invalid index";
		}
		case EDS_ERR_INVALID_LENGTH: {
			return "Invalid length";
		}
		case EDS_ERR_INVALID_FN_POINTER: {
			return "Invalid function pointer";
		}
		case EDS_ERR_INVALID_SORT_FN: {
			return "Invalid sort function";
		}
		case EDS_ERR_DEVICE_NOT_FOUND: {
			return "Device not found";
		}
		case EDS_ERR_DEVICE_BUSY: {
			return "Device busy";
		}
		case EDS_ERR_DEVICE_INVALID: {
			return "Device invalide";
		}
		case EDS_ERR_DEVICE_EMERGENCY: {
			return "Device emergency";
		}
		case EDS_ERR_DEVICE_MEMORY_FULL: {
			return "Device memory full";
		}
		case EDS_ERR_DEVICE_INTERNAL_ERROR: {
			return "Device internal error";
		}
		case EDS_ERR_DEVICE_INVALID_PARAMETER: {
			return "Device invalid paramter";
		}
		case EDS_ERR_DEVICE_NO_DISK: {
			return "Device no disk";
		}
		case EDS_ERR_DEVICE_DISK_ERROR: {
			return "Device disk error";
		}
		case EDS_ERR_DEVICE_CF_GATE_CHANGED: {
			return "CF Gate changed";
		}
		case EDS_ERR_DEVICE_DIAL_CHANGED: {
			return "Device dial changed";
		}
		case EDS_ERR_DEVICE_NOT_INSTALLED: {
			return "Device not installed";
		}
		case EDS_ERR_DEVICE_STAY_AWAKE: {
			return "Device stay awake";
		}
		case EDS_ERR_DEVICE_NOT_RELEASED: {
			return "Device not released";
		}
		case EDS_ERR_STREAM_IO_ERROR: {
			return "Stream io error";
		}
		case EDS_ERR_STREAM_NOT_OPEN: {
			return "Stream not open";
		}
		case EDS_ERR_STREAM_ALREADY_OPEN: {
			return "Stream already open";
		}
		case EDS_ERR_STREAM_OPEN_ERROR: {
			return "Stream open error";
		}
		case EDS_ERR_STREAM_CLOSE_ERROR: {
			return "Stream close error";
		}
		case EDS_ERR_STREAM_SEEK_ERROR: {
			return "Stream seek error";
		}
		case EDS_ERR_STREAM_TELL_ERROR: {
			return "Stream tell error";
		}
		case EDS_ERR_STREAM_READ_ERROR: {
			return "Stream read error";
		}
		case EDS_ERR_STREAM_WRITE_ERROR: {
			return "Stream write error";
		}
		case EDS_ERR_STREAM_PERMISSION_ERROR: {
			return "Stream permission error";
		}
		case EDS_ERR_STREAM_COULDNT_BEGIN_THREAD: {
			return "Stream couldnt begin thread";
		}
		case EDS_ERR_STREAM_BAD_OPTIONS: {
			return "Stream bad options";
		}
		case EDS_ERR_STREAM_END_OF_STREAM: {
			return "Stream end of stream";
		}
		case EDS_ERR_COMM_PORT_IS_IN_USE: {
			return "Com port is in use";
		}
		case EDS_ERR_COMM_DISCONNECTED: {
			return "Comm disconnected";
		}
		case EDS_ERR_COMM_DEVICE_INCOMPATIBLE: {
			return "Com device incompatible";
		}
		case EDS_ERR_COMM_BUFFER_FULL: {
			return "Com buffer full";
		}
		case EDS_ERR_COMM_USB_BUS_ERR: {
			return "USB Bus error";
		}
		case EDS_ERR_USB_DEVICE_LOCK_ERROR: {
			return "Device lock";
		}
		case EDS_ERR_USB_DEVICE_UNLOCK_ERROR: {
			return "Device  unlock";
		}
		case EDS_ERR_STI_UNKNOWN_ERROR: {
			return "STI unknonw";
		}
		case EDS_ERR_STI_INTERNAL_ERROR: {
			return "STI internal error";
		}
		case EDS_ERR_STI_DEVICE_CREATE_ERROR: {
			return "STI create error";
		}
		case EDS_ERR_STI_DEVICE_RELEASE_ERROR: {
			return "STI device release";
		}
		case EDS_ERR_DEVICE_NOT_LAUNCHED: {
			return "Device not launched";
		}
		case EDS_ERR_ENUM_NA: {
			return "Enum NA";
		}
		case EDS_ERR_INVALID_FN_CALL: {
			return "Invalid function call";
		}
		case EDS_ERR_HANDLE_NOT_FOUND: {
			return "Handle not found";
		}
		case EDS_ERR_INVALID_ID: {
			return "Invalid ID";
		}
		case EDS_ERR_WAIT_TIMEOUT_ERROR: {
			return "Wait timeout error";
		}
		case EDS_ERR_SESSION_NOT_OPEN: {
			return "Session not open";
		}
		case EDS_ERR_INVALID_TRANSACTIONID: {
			return "Invalid transationid";
		}
		case EDS_ERR_INCOMPLETE_TRANSFER: {
			return "Incomplete transfer";
		}
		case EDS_ERR_INVALID_STRAGEID: {
			return "Invalid strage id";
		}
		case EDS_ERR_DEVICEPROP_NOT_SUPPORTED: {
			return "Device prop not supported";
		}
		case EDS_ERR_INVALID_OBJECTFORMATCODE: {
			return "Invalid object format code";
		}
		case EDS_ERR_SELF_TEST_FAILED: {
			return "Self test failed";
		}
		case EDS_ERR_PARTIAL_DELETION: {
			return "Oartial deletion";
		}
		case EDS_ERR_SPECIFICATION_BY_FORMAT_UNSUPPORTED: {
			return "Specification by format unsupported";
		}
		case EDS_ERR_NO_VALID_OBJECTINFO: {
			return "No valid object info";
		}
		case EDS_ERR_INVALID_CODE_FORMAT: {
			return "Invalid code format";
		}
		case EDS_ERR_UNKNOWN_VENDOR_CODE: {
			return "Unknown vendor code";
		}
		case EDS_ERR_CAPTURE_ALREADY_TERMINATED: {
			return "Capture already terminated";
		}
		case EDS_ERR_INVALID_PARENTOBJECT: {
			return "Invalid parent object";
		}
		case EDS_ERR_INVALID_DEVICEPROP_FORMAT: {
			return "Invalid device prop format";
		}
		case EDS_ERR_INVALID_DEVICEPROP_VALUE: {
			return "Invalid device prop value";
		}
		case EDS_ERR_SESSION_ALREADY_OPEN: {
			return "Session already open";
		}
		case EDS_ERR_TRANSACTION_CANCELLED: {
			return "Transaction cancelled";
		}
		case EDS_ERR_SPECIFICATION_OF_DESTINATION_UNSUPPORTED: {
			return "Specification of destination unsupported";
		}
		case EDS_ERR_UNKNOWN_COMMAND: {
			return "Unknown command";
		}
		case EDS_ERR_OPERATION_REFUSED: {
			return "Operation refused";
		}
		case EDS_ERR_LENS_COVER_CLOSE: {
			return "Lens cover close";
		}
		case EDS_ERR_LOW_BATTERY: {
			return "Low battery";
		}
		case EDS_ERR_OBJECT_NOTREADY: {
			return "Object not ready";
		}
		case EDS_ERR_TAKE_PICTURE_AF_NG: {
			return "Take picture AF_NG";
		}
		case EDS_ERR_TAKE_PICTURE_RESERVED: {
			return "Take picture reserverd";
		}
		case EDS_ERR_TAKE_PICTURE_MIRROR_UP_NG: {
			return "Take picture mirror up ng";
		}
		case EDS_ERR_TAKE_PICTURE_SENSOR_CLEANING_NG: {
			return "Take picture sensor cleaning ng";
		}
		case EDS_ERR_TAKE_PICTURE_SILENCE_NG: {
			return "Take picture silence ng";
		}
		case EDS_ERR_TAKE_PICTURE_NO_CARD_NG: {
			return "Take picture no card ng";
		}
		case EDS_ERR_TAKE_PICTURE_CARD_NG: {
			return "Take picture card ng";
		}
		case EDS_ERR_TAKE_PICTURE_CARD_PROTECT_NG: {
			return "Take picture card protect ng";
		}
		case EDS_ERR_TAKE_PICTURE_MOVIE_CROP_NG: {
			return "Take picture movie crop ng";
		}
		case EDS_ERR_TAKE_PICTURE_STROBO_CHARGE_NG: {
			return "Take picture strobo change ng";
		}
		case EDS_ERR_LAST_GENERIC_ERROR_PLUS_ONE: {
			return "Last generic error plus one";
		}

		default:break;
	};
	return "Unknown error.";

}

#endif
