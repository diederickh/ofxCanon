#include "ofxCanonConnection.h"

ofxCanonConnection::ofxCanonConnection(
	ofxCanon& rCanon
	,int nCamID
	,string sDownloadDir
	,float fTimeOut
):canon(rCanon)
,cam_id(nCamID)
//,timer(io)
,timeout(fTimeOut)
,was_initialized(false)
,times_initialized(0)
,should_check_on(0)
,download_dir(sDownloadDir)
{
	std::cout << "dldir " << download_dir << std::endl;
	//setup();
}

ofxCanonConnection::~ofxCanonConnection() {
	std::cout << ">>>> ~ofxCanonConnection" << std::endl;
}

/*
void ofxCanonConnection::setup() {
	std::cout << "Starting connection timer" << std::endl;
	timer.expires_from_now(boost::posix_time::seconds(timeout));
	timer.async_wait(
				boost::bind(
						&ofxCanonConnection::timerCallback
						,this
						,boost::asio::placeholders::error
				)
	);
}
*/

void ofxCanonConnection::update() {
	if(ofGetElapsedTimeMillis() > should_check_on) {
		checkConnection();
		should_check_on = ofGetElapsedTimeMillis() + timeout;
	}
}

void ofxCanonConnection::start(ofxCanonConnectionCallback* rCallback) {
	callback = rCallback;
	should_check_on = ofGetElapsedTimeMillis();
//	boost::thread tmp(boost::bind(&boost::asio::io_service::run, boost::ref(io)));
}
void ofxCanonConnection::checkConnection() {
//void ofxCanonConnection::timerCallback(const boost::system::error_code& rError) {
	if(!canon.isInitialized() && !canon.isInitializing()) {
		std::cout << "init with : " << download_dir << std::endl;
		canon.init(cam_id, download_dir);
		was_initialized = false;

	}
	else {
		if(!was_initialized) {
			callback->onCanonInitialized(times_initialized);
			times_initialized++;
			was_initialized = true;
		}
	}
//	setup();
}
