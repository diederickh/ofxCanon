#include "ofxCanonThread.h"
ofxCanonThread::ofxCanonThread()
:times_initialized(0)
,timeout(2000)
,should_check_on(0)
,was_initialized(false)
{
	std::cout << "ofxCanonThread::ofxCanonThread()" << std::endl;
}

ofxCanonThread::~ofxCanonThread() {
	std::cout << "~~~~ ofxCanonThread." <<std::endl;
	canon.shutdown(); // we need to call this as the thread will continue as long as there are commands..
}


void ofxCanonThread::start(ofxCanonThreadCallback* pCallback) {
	std::cout << "ofxCanonThread::start()" << std::endl;
	callback = pCallback;
	thread_ptr = boost::shared_ptr<boost::thread>(
							new boost::thread(
								boost::bind(&ofxCanonThread::run, this)
				)
	);
	//thread_ptr->join();
}

void ofxCanonThread::run() {
	std::cout << "ofxCanonThread::run()" << std::endl;
	//canon.init(0, ofToDataPath("images/"));
	while(1) {
		if(ofGetElapsedTimeMillis() > should_check_on) {
			std::cout << "ofxCanonThread: check connection!" << std::endl;
			checkConnection();
			should_check_on = ofGetElapsedTimeMillis() + timeout;
			std::cout << "ofxCanonThread: will check again on: "<< should_check_on << std::endl;
		}
		else {
	//		std::cout << "ofxCanonThread: will check again on: "<< should_check_on << ", now:" << ofGetElapsedTimeMillis()<< std::endl;
		}
	//	std::cout << "ofxCanonThread....." << std::endl;
	//	ofSleepMillis(300);
		if(canon.isInitialized())
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


void ofxCanonThread::endEvf() {
	mutex_.lock();
		cout << "endEvf" << std::endl;
		canon.endEvf();
	mutex_.unlock();
}

void ofxCanonThread::checkConnection() {
	if(!canon.isInitialized() && !canon.isInitializing()) {
		std::cout << "ofxCanonThread.checkConnection(), call init()" << std::endl;
		canon.init(0, ofToDataPath("images/"));
		was_initialized = false;
	}
	else {
		std::cout << "ofxCanonThread.checkConnection(), pre onCanonInitialized()" << std::endl;
		if(!was_initialized) {
			std::cout << "ofxCanonThread.checkConnection(), onCanonInitialized()" << std::endl;
			callback->onCanonInitialized(times_initialized);
			times_initialized++;
			was_initialized = true;
		}
	}
}

ofxCanon* ofxCanonThread::getCanon() {
	return &canon;
}
