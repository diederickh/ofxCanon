#include "ofxCanonConnection.h"
#include "ofxLog.h"

ofxCanonConnection::ofxCanonConnection(
	ofxCanon& rCanon
	,int nCamID
	,string sDownloadDir
	,float fTimeOut
):canon(rCanon)
,cam_id(nCamID)
,timeout(fTimeOut)
,was_initialized(false)
,times_initialized(0)
,should_check_on(0)
,download_dir(sDownloadDir)
{
}

ofxCanonConnection::~ofxCanonConnection() {
    OFXLOG("~~~~ ofxCanonConnection()");
	//std::cout << ">>>> ~ofxCanonConnection" << std::endl;
}

void ofxCanonConnection::update() {
	if(ofGetElapsedTimeMillis() > should_check_on) {
        OFXLOG("ofxCanonConnection: update -> go and check connection.");
		checkConnection();
		should_check_on = ofGetElapsedTimeMillis() + timeout;
	}
}

void ofxCanonConnection::start(ofxCanonConnectionCallback* rCallback) {
	callback = rCallback;
	should_check_on = ofGetElapsedTimeMillis();
}

void ofxCanonConnection::checkConnection() {
	if(!canon.isInitialized() && !canon.isInitializing()) {
	    OFXLOG("ofxCanonConnection: call canon.init()");
		canon.init(cam_id, download_dir);
		was_initialized = false;
	}
	else {
		if(!was_initialized) {
		    OFXLOG("ofxCanonConnection: call onCanonInitialized");
			callback->onCanonInitialized(times_initialized);
			times_initialized++;
			was_initialized = true;
		}
	}
}
