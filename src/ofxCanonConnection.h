#ifndef OFXCANONCONNECTIONH
#define OFXCANONCONNECTIONH

#undef check
#include <iostream>
/*
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
*/
#include "ofxCanon.h"
#include "ofMain.h"

class ofxCanonConnectionCallback {
public:
	virtual void onCanonInitialized(int nTimesCalled = 0) = 0;
};

//class ofxCanonConnection : public boost::enable_shared_from_this<ofxCanonConnection>{
class ofxCanonConnection {
public:
	ofxCanonConnection(ofxCanon& rCanon, int nCamID, float fTimeOut = 5.0f);
	~ofxCanonConnection();
	void start(ofxCanonConnectionCallback* rCallback);
	void update();
	void checkConnection();
	/*
	void setup();

	void timerCallback(const boost::system::error_code& rError);
	*/
private:
	//boost::shared_ptr<boost::thread> thread_;
	int times_initialized;
	bool was_initialized;
	int cam_id;
	int should_check_on;
	
	float timeout;
//	boost::asio::io_service io;
//	boost::asio::deadline_timer timer;
//	boost::mutex mutex;
	ofxCanon& canon;
	ofxCanonConnectionCallback* callback;
};
#endif