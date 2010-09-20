#ifndef OFXCANONCONTROLLERH
#define OFXCANONCONTROLLERH

#include "ofxActionListener.h"
#include "ofxActionEvent.h"
#include "ofxCommandProcessor.h"
#include "ofxCommandProcessorThreadWin.h"
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


class ofxCanon;
class ofxCanonController : public ofxActionListener {
public:
	//ofxCanonController(ofxCanon* pCanon, ofxCanonModel* pModel);
	ofxCanonController();
	void init(ofxCanon* pCanon, ofxCanonModel* pModel);
	void shutdown();
	void run();
	bool isRunning();
	void update(); // fixing ofxCommandProcessor
	void actionPerformed(const ofxActionEvent& rEvent);
	void addCommand(ofxCommand* pCommand);

private:
	bool is_running;
	ofxCanon* canon;
	ofxCanonModel* model;
	//ofxCommandProcessor processor;
	ofxCommandProcessorThreadWin processor;
};
#endif
