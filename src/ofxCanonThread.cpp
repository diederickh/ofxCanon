#include "ofxCanonThread.h"
ofxCanonThread::ofxCanonThread()
:times_initialized(0)
,timeout(3000)
,should_check_on(0)
,was_initialized(false)
{
}

ofxCanonThread::~ofxCanonThread() {
	std::cout << "~~~~ ofxCanonThread." <<std::endl;
}


void ofxCanonThread::start(ofxCanonThreadCallback* pCallback) {
	callback = pCallback;
	thread_ptr = boost::shared_ptr<boost::thread>(
							new boost::thread(
								boost::bind(&ofxCanonThread::run, shared_from_this()	)
							)
	);
}

void ofxCanonThread::run() {
	//canon.init(0, ofToDataPath("images/"));
	while(1) {
		if(ofGetElapsedTimeMillis() > should_check_on) {
			checkConnection();
			should_check_on = ofGetElapsedTimeMillis() + timeout;
		}
		canon.update();
	}
}

void ofxCanonThread::addActionSource(ofxActionSource* pSource) {
	mutex_.lock();
		pSource->addActionListener(canon.controller);
	mutex_.unlock();
}
void ofxCanonThread::addModelObserver(ofxObserver* pObserver) {
	mutex_.lock();
		canon.model->addObserver(pObserver);
	mutex_.unlock();
}

void ofxCanonThread::setDownloadDir(string sDir) {
	mutex_.lock();
		canon.model->setDownloadDir(sDir);
	mutex_.unlock();
}

void ofxCanonThread::startEvf() {
	mutex_.lock();
		cout << "startedEvf" << std::endl;
		canon.startEvf();
	mutex_.unlock();
}

void ofxCanonThread::checkConnection() {
	if(!canon.isInitialized() && !canon.isInitializing()) {
		canon.init(0, ofToDataPath("images/"));
		was_initialized = false;
	}
	else {
		if(!was_initialized) {
			callback->onCanonInitialized(times_initialized);
			times_initialized++;
			was_initialized = true;
		}
	}
}

ofxCanon* ofxCanonThread::getCanon() {
	return &canon;
}
