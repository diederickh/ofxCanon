#ifndef OFXCANONCONTROLLERH
#define OFXCANONCONTROLLERH

#include "ofxActionListener.h"
#include "ofxActionEvent.h"
#include "ofxCommandProcessor.h"

#if defined( __WIN32__ ) || defined( _WIN32 )
	#include "ofxCommandProcessorThreadWin.h"
#elif defined(__APPLE__)
	#include "ofxCommandProcessorThreadMac.h"
#endif
#include "ofxCanonModel.h"


#include "ofxCanonCommandOpenSession.h"
#include "ofxCanonCommandCloseSession.h"
#include "ofxCanonCommandTakePicture.h"
#include "ofxCanonCommandDownload.h"
#include "ofxCanonCommandStartEvf.h"
#include "ofxCanonCommandEndEvf.h"
#include "ofxCanonCommandGetProperty.h"
#include "ofxCanonCommandDownloadEvf.h"
#include "ofxCanonCommandKeepAlive.h"
#include <boost/shared_ptr.hpp>


class ofxCanon;
class ofxCanonController : public ofxActionListener {
public:
	ofxCanonController();
	void init(ofxCanon* pCanon, ofxCanonModel* pModel);
	void shutdown();
	void run();
	bool isRunning();
	void update(); // fixing ofxCommandProcessor
	void actionPerformed(const ofxActionEvent& rEvent);
	//void addCommand(ofxCommand* pCommand);
	void addCommand(boost::shared_ptr<ofxCommand> pCommand);

private:
	bool is_running;
	ofxCanon* canon;
	ofxCanonModel* model;

	#if defined( __WIN32__ ) || defined( _WIN32 )
		ofxCommandProcessorThreadWin processor;
	#elif defined(__APPLE__)
		ofxCommandProcessorThreadMac processor;
	#endif
};
#endif
