#ifndef OFXCANONPICTUREBOXH
#define OFXCANONPICTUREBOXH

#include "ofxActionSource.h"
#include "ofxObserver.h"
#include "ofxCanon.h"
#include "ofxCanonModel.h"
#include "ofxCanonCommandDownloadEvf.h"
#include "EDSDK.h"
#include "ofMain.h"
class ofxCanon;


// I copied memoryImage to JPEGImage from Theo's code!
class JPEGImage : public ofImage{
private:
	bool flip_vertical;
	bool flip_horizontal;

public:
	JPEGImage(bool bFlipH = false, bool bFlipV = false)
		:flip_horizontal(bFlipH)
		,flip_vertical(bFlipV)
	{
	}
	
	void setFlipVertical(bool bFlip) {
		flip_vertical = bFlip;
	}
	
	void setFlipHorizontal(bool bFlip) {
		flip_horizontal = bFlip;
	}
	
    bool loadFromMemory(int bytesToRead, unsigned char * jpegBytes, int rotateMode = 0){
        FIMEMORY *hmem = NULL;

        hmem = FreeImage_OpenMemory((unsigned char*)jpegBytes, bytesToRead);
        if (hmem == NULL){
            printf("couldn't create memory handle! \n");
            return false;
        }

        //get the file type!
        FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeFromMemory(hmem);
        if( fif == -1 ){
            printf("unable to guess format", fif);
            return false;
            FreeImage_CloseMemory(hmem);
        }

        //make the image!!
        FIBITMAP * tmpBmp = FreeImage_LoadFromMemory(fif, hmem, 0);

        if( rotateMode > 0 && rotateMode < 4){
            FIBITMAP * oldBmp = tmpBmp;

            if( rotateMode == 1)tmpBmp = FreeImage_RotateClassic(tmpBmp, 90);
            if( rotateMode == 2)tmpBmp = FreeImage_RotateClassic(tmpBmp, 180);
            if( rotateMode == 3)tmpBmp = FreeImage_RotateClassic(tmpBmp, 270);

            FreeImage_Unload(oldBmp);
        }

		// @todo make this a parameter
		if(flip_vertical)
			FreeImage_FlipVertical(tmpBmp);
		if(flip_horizontal)
			FreeImage_FlipHorizontal(tmpBmp);
        putBmpIntoPixels(tmpBmp, myPixels);
        width 		= FreeImage_GetWidth(tmpBmp);
        height 		= FreeImage_GetHeight(tmpBmp);
        bpp 		= FreeImage_GetBPP(tmpBmp);

        swapRgb(myPixels);

        FreeImage_Unload(tmpBmp);
        FreeImage_CloseMemory(hmem);

        return true;
    }


    //shouldn't have to redefine this but a gcc bug means we do
    inline void	swapRgb(ofPixels &pix){
        if (pix.bitsPerPixel != 8){
            int sizePixels		= pix.width*pix.height;
            int cnt				= 0;
            unsigned char temp;
            int byteCount		= pix.bitsPerPixel/8;

            while (cnt < sizePixels){
                temp					        = pix.pixels[cnt*byteCount];
                pix.pixels[cnt*byteCount]		= pix.pixels[cnt*byteCount+2];
                pix.pixels[cnt*byteCount+2]		= temp;
                cnt++;
            }
        }
    }

};



class ofxCanonPictureBox : public ofxActionSource, public ofxObserver {
private:
	bool active;
	ofxCanon* canon;

public:
	ofImage the_img;
	int frame;
	int resized_frame;
	JPEGImage jpeg;
	unsigned char* pixels;
	bool is_drawing_paused;
	
	ofxCanonPictureBox(ofxCanon* pCanon)
		:canon(pCanon)
		,active(false)
		,pixels(NULL)
		,frame(0)
		,resized_frame(0)
		,is_drawing_paused(false)
		,jpeg(true,false)
	{

	}

	virtual void update(ofxObservable* pFrom, ofxObservableEvent *pEvent) {
		std::string event = pEvent->getEvent();
		if(event == "evf_data_changed") {
			if(!is_drawing_paused) {
				EVF_DATASET* data = static_cast<EVF_DATASET *>(pEvent->getArg());
				EdsUInt32 length;
				EdsGetLength(data->stream, &length);
				
				if(length > 0) {
					// @todo we don't really need data_size as we've got length
					unsigned char* image_data;
					EdsUInt32 data_size = length;
					EdsGetPointer(data->stream, (EdsVoid**)&image_data);
					EdsGetLength(data->stream, &data_size);
					
					if(jpeg.loadFromMemory((int)data_size, image_data,1)) {
						frame++;
						int w = jpeg.width;
						int h = jpeg.height;
						if(w > 0 && h > 0) {
						}
						}
					else {
						std::cout << "#### error while converting to image" << std::endl;
					}
				}
			}
			//std::cout << "download_evf" << std::endl;
			EdsInt32 prop_id = kEdsPropID_FocusInfo;
			fireEvent("get_property", &prop_id);
			fireEvent("download_evf");

		}
		else if(event == "property_changed") {

			EdsInt32 property_id = *static_cast<EdsInt32*>(pEvent->getArg());
			ofxCanonModel* model = (ofxCanonModel *)pFrom;
			EdsUInt32 device = model->getEvfOutputDevice();

			if(property_id == kEdsPropID_Evf_OutputDevice) {
				if(!active && (device & kEdsEvfOutputDevice_PC) != 0) {
					active = true;
					fireEvent("download_evf");
				}
				if(active && (device & kEdsEvfOutputDevice_PC) == 0) {
					active = false;
				}
			}
		}
	}

	void draw(float nX, float nY, float nWidth, float nHeight) {
		glColor3f(1.0f, 1.0f, 1.0f);
		// this is a silly thing we have to do, else the texture data
		// isn't updated and jpeg.draw() shows a black surface.
		if(resized_frame < frame) {
			jpeg.resize(jpeg.width, jpeg.height);
			//jpeg.resize(nWidth, nHeight);
			resized_frame = frame;
		}
		jpeg.draw(nX,nY, nWidth, nHeight);
	}
	void restart() {
		fireEvent("download_evf");
	}
	
	void pauseDrawing() {
		is_drawing_paused = true;
	}
	bool isDrawingPaused() {
		return is_drawing_paused;
	}
		
	bool continueDrawing() {
		is_drawing_paused = false;
	}
};




#endif
