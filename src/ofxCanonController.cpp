#include "ofxCanonController.h"
#include "ofxCanon.h"
#include "ofxLog.h"

ofxCanonController::ofxCanonController()
	:canon(NULL)
	,model(NULL)
	,is_running(false)
{

}
void ofxCanonController::init(ofxCanon* pCanon, ofxCanonModel* pModel) {
	canon = pCanon;
	model = pModel;
}

void ofxCanonController::shutdown() {
	while(!processor.isReady()) {
		processor.remove("get_property");
		processor.remove("download_evf");
		processor.update();
		printf("Processing command queue.....\n");
		ofSleepMillis(10);
	}
	printf("ofxCanon: ofxCanonController ready.\n");
}

void ofxCanonController::run() {
	is_running = true;
	processor.start();
	addCommand(new ofxCanonCommandOpenSession("open_session", model));
}

void ofxCanonController::update() {
	processor.update();
}

bool ofxCanonController::isRunning() {
	return is_running;
}

void ofxCanonController::actionPerformed(const ofxActionEvent& rEvent) {
	std::string command = rEvent.getActionCommand();
	if(command == "take_picture") {
		addCommand(new ofxCanonCommandTakePicture("take_picture", model));
	}
	if(command == "open_session") {
		addCommand(new ofxCanonCommandOpenSession("open_session", model));
	}
	if(command == "close_session") {
		addCommand(new ofxCanonCommandCloseSession("close_session", model));
	}
	if(command == "keep_alive") {
		if(model->getKeepAlive())
			addCommand(new ofxCanonCommandKeepAlive("keep_alive", model));
	}
	if(command == "download") {
		OFXLOG("ofxCanon: (controller) got download action");
		addCommand(new ofxCanonCommandDownload(
								"download"
								,model
								,static_cast<EdsBaseRef>(rEvent.getArg()))
		);
	}
	if(command == "download_evf") {
		addCommand(new ofxCanonCommandDownloadEvf("download_evf",model));
	}
	if(command == "start_evf") {
		addCommand(new ofxCanonCommandStartEvf("start_evf", model));
	}
	if(command == "end_evf") {
		addCommand(new ofxCanonCommandEndEvf("end_evf",model));
	}
	if(command == "get_property") {

		addCommand(new ofxCanonCommandGetProperty(
				"get_property"
				,model
				,*static_cast<EdsUInt32*>(rEvent.getArg())
			)
		);

	}
	if(command == "shutdown") {
		canon->resetInit();
	}

}

// add a new command to the processor which a executes it in a thread.
void ofxCanonController::addCommand(ofxCommand* pCommand) {
    OFXLOG("ofxCanonController: addCommand: " << pCommand->name);
	if(pCommand != NULL)
		processor.enqueue(pCommand);
}
