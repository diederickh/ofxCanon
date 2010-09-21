#ifndef OFXCANONCONNECTIONH
#define OFXCANONCONNECTIONH

#include <iostream>
#include "ofxCanon.h"
#include "ofMain.h"

class ofxCanonConnectionCallback {
public:
	virtual void onCanonInitialized(int nTimesCalled = 0) = 0;
};

/**
 * The ofxCanonConnection is used to check if the camera is still connected,
 * and if not, it tries to reinitialize the EDSDK and conection.
 *
 */
class ofxCanonConnection {
public:
	ofxCanonConnection(ofxCanon& rCanon, int nCamID, string sDownloadDir, float fTimeOut = 5.0f);
	~ofxCanonConnection();
	void start(ofxCanonConnectionCallback* rCallback);
	void update();
	void checkConnection();

private:
	int times_initialized;
	bool was_initialized;
	int cam_id;
	int should_check_on;
	string download_dir;
	float timeout;
	ofxCanon& canon;
	ofxCanonConnectionCallback* callback;
};
#endif
