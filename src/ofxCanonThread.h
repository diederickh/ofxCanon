#ifndef OFXCANONTHREADH
#define OFXCANONTHREADH

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include <boost/enable_shared_from_this.hpp>
#include "ofxCanon.h"
#include "ofMain.h"
#include "ofxCommand.h"

#if defined( __WIN32__ ) || defined( _WIN32 )
	#define CANON_TARGET_WIN32_EVENTJES_UIT

	#include "windows.h"
	#include <process.h>
	#include "ofxCanonThreadSynchronized.h"

#endif

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

	#ifdef CANON_TARGET_WIN32
		//void startWindows();
		ofxCanonThreadSynchronized sync;
		HANDLE thread_handle;
		static void startThread(void* lParam) {
			ofxCanonThread* thread = (ofxCanonThread*) lParam;
			if(thread != NULL) {
				thread->run();
			}
			_endthread();
		}

	#endif

	ofxCanon* getCanon();
	void checkConnection();
	void addActionSource(ofxActionSource* pSource);
	void addModelObserver(ofxObserver* pObserver);
	void setDownloadDir(string sDir);
	void startEvf();
	void lock();
	void unlock();

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
