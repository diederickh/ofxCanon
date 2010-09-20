#ifndef OFXCANONTHREADH
#define OFXCANONTHREADH

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include <boost/enable_shared_from_this.hpp>
#include "ofxCanon.h"
#include "ofMain.h"
#include "ofxCommand.h"

class ofxCanonThreadCallback {
public:
	virtual void onCanonInitialized(int nTimesCalled = 0) = 0;
};


class ofxCanonThread : public boost::enable_shared_from_this<ofxCanonThread>{
public:
	typedef boost::shared_ptr<ofxCanonThread> pointer;
	ofxCanonThread();
	~ofxCanonThread();

	void start(ofxCanonThreadCallback* pCallback);
	void run();
	ofxCanon* getCanon();
	void checkConnection();
	void addActionSource(ofxActionSource* pSource);
	void addModelObserver(ofxObserver* pObserver);
	void setDownloadDir(string sDir);
	void startEvf();

private:
	ofxCanon canon;
	ofxCanonThreadCallback* callback;
	boost::shared_ptr<boost::thread> thread_ptr;
	int times_initialized;
	int should_check_on;
	bool was_initialized;
	int timeout;
	boost::mutex mutex_;
};

#endif
