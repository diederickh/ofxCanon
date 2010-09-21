#ifndef OFXCANONH
#define OFXCANONH

#include "EDSDK.h"
#include "EDSDKErrors.h"
#include "EDSDKTypes.h"

#include "ofxCanonDebug.h"
#include "ofxCommandPattern.h"
#include "ofxCanonModel.h"
#include "ofxCanonController.h"
#include "ofxCanonCameraEventListener.h"
#include "ofxCanonPictureBox.h"
#include "ofxCanonConnection.h"

#include "ofxObserver.h"
#include <map>
#include <string>

class ofxCanon : public ofxObserver {
public:
	ofxCanonModel* model;
	ofxCanonController* controller;
	ofxCanonPictureBox* picture_box;
	ofxCanon();
	~ofxCanon();
	void update();

	bool init(int nCameraID, string sDownloadDir);
	bool isInitializing();
	void shutdown();
	void draw(float nX, float nY, float nWidth, float nHeight);
	virtual void update(ofxObservable* pFrom, ofxObservableEvent *pEvent);
	void takePicture();
	void startEvf();
	void endEvf();
	bool isInitialized();
	void resetInit();
	void closeSession();
	bool openSession();

protected:
	bool initialized;
	bool is_sdk_loaded;
	bool is_initializing;
	bool evf_started;

	void setupActionSources();
	void setupObserver();
	void addActionSource(std::string sCommand);
	bool performAction(std::string sCommand);
	std::map<std::string,ofxActionSource*> action_sources;
};
#endif
