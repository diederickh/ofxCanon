#ifndef OFXCANONH
#define OFXCANONH

#include "EDSDK.h"
#include "EDSDKErrors.h"
#include "EDSDKTypes.h"

#include "ofxCommandPattern.h"
#include "ofxCanonModel.h"
#include "ofxCanonController.h"
#include "ofxCanonCameraEventListener.h"
#include "ofxCanonPictureBox.h"
#include "ofxCanonConnection.h"
#include "ofxThread.h"
#include "ofxObserver.h"
#include <map>
#include <string>

//class ofxCanon : public ofxThread, public ofxObserver {
class ofxCanon : public ofxObserver {
public:
	ofxCanonModel* model;
	ofxCanonController* controller;
	ofxCanonPictureBox* picture_box;
	ofxCanon();
	~ofxCanon();
	void update();
	//virtual void threadedFunction();
	bool init(int nCameraID, string sDownloadDir);
	bool isInitializing();
	void shutdown();
	void draw(float nX, float nY, float nWidth, float nHeight);
	void takePicture();
	void startEvf();
	void endEvf();
	bool isInitialized();
	void resetInit();
	virtual void update(ofxObservable* pFrom, ofxObservableEvent *pEvent);
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
