#ifndef OFXCANONDOWNLOADEVFH
#define OFXCANONDOWNLOADEVFH

#include "ofxCanonCommand.h"
#include "ofxObservableEvent.h"
#include "ofxCanonDebug.h"

typedef struct _EVF_DATASET
{
	EdsStreamRef	stream; // JPEG stream.
	EdsUInt32		zoom;
	EdsRect			zoomRect;
	EdsPoint		imagePosition;
	EdsUInt32		histogram[256 * 4]; //(YRGB) YRGBYRGBYRGBYRGB....
	EdsSize			sizeJpegLarge;
}EVF_DATASET;


class ofxCanonCommandDownloadEvf : public ofxCanonCommand {
public:
	ofxCanonCommandDownloadEvf(std::string sName, ofxCanonModel* pModel)
		:ofxCanonCommand(sName,pModel)
	{
	}

	virtual bool execute() {
		EdsError err = EDS_ERR_OK;
		EdsEvfImageRef evf_image = NULL;
		EdsStreamRef stream = NULL;
		EdsUInt32 buffer_size = 2 * 1024 * 1024;
	std::cout << "downloadEvf+++++++++++++++++++++++++++++\n";
		// Exit unless during live view
		if ((model->getEvfOutputDevice() & kEdsEvfOutputDevice_PC) == 0) {
			//cout << "CANON: Don't download anymore as we're ready." << std::endl;
			return true;
		}

		err = EdsCreateMemoryStream(buffer_size, &stream);

		if(err == EDS_ERR_OK)
			err = EdsCreateEvfImageRef(stream, &evf_image);

		if(err == EDS_ERR_OK)
			err = EdsDownloadEvfImage(model->getCamera(), evf_image);

		if(err == EDS_ERR_OK) {
			EVF_DATASET data_set = {0};
			data_set.stream = stream;
			//ofxObservableEvent e("evf_data_changed", &data_set);
			//model->notifyObservers(&e);

			// @todo do we need to get all these specs?
			// Get magnification ratio (x1, x5 or x10)
			/*
			EdsGetPropertyData(
							evf_image
							,kEdsPropID_Evf_Zoom
							,0
							,sizeof(data_set.zoom)
							,&data_set.zoom
			);

			// Get position of image data (when enlarging)
			EdsGetPropertyData(
							evf_image
							,kEdsPropID_Evf_ImagePosition
							,0
							,sizeof(data_set.imagePosition)
							,&data_set.imagePosition
			);

			// Get histogram (RGBY).
			EdsGetPropertyData(
							evf_image
							,kEdsPropID_Evf_Histogram
							,0
							,sizeof(data_set.histogram)
							,data_set.histogram
			);

			// Get rectangle of the focus border.
			EdsGetPropertyData(
							evf_image
							,kEdsPropID_Evf_ZoomRect
							,0
							,sizeof(data_set.zoomRect)
							, &data_set.zoomRect
			);

			// Get the size as a reference of the coordinates of rectangle of the focus border.
			EdsGetPropertyData(
							evf_image
							,kEdsPropID_Evf_CoordinateSystem
							,0
							,sizeof(data_set.sizeJpegLarge)
							,&data_set.sizeJpegLarge
			);

			model->setEvfZoom(data_set.zoom);
			model->setEvfZoomPosition(data_set.zoomRect.point);
			model->setEvfZoomRect(data_set.zoomRect);
			*/
			if(err == EDS_ERR_OK) {
				cout << "in ofxCanonCommandDownloadEvf: downloaded! " << std::endl;
				ofxObservableEvent e("evf_data_changed", &data_set);
				model->notifyObservers(&e);
			}
		}

		if(stream != NULL) {
			EdsRelease(stream);
			stream = NULL;
		}


		if(evf_image != NULL) {
			EdsRelease(evf_image);
			evf_image = NULL;
		}


		// Show error:
		if(err != EDS_ERR_OK) {
			cout << "ERROR: in ofxCanonCommandDownloadEvf " << ofxCanonErrorToString(err) << std::endl;
			if(err == EDS_ERR_INTERNAL_ERROR) {
				ofxObservableEvent e("internal_error");
				model->notifyObservers(&e);
			}
			else if(err == EDS_ERR_OBJECT_NOTREADY) {
				return false;
			}
		}
		return true;
	}
};
#endif
