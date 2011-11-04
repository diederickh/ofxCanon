#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	canon.start();
	canon.addPictureTakenListener(this, &testApp::onPictureTaken);
}

void testApp::onPictureTaken(roxlu::CanonPictureEvent& ev) {
	cout << ev.getFilePath() << endl;
}

//--------------------------------------------------------------
void testApp::update(){
	if(!canon.isLiveViewActive() && canon.isSessionOpen()) {
		canon.startLiveView();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	canon.drawLiveView();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == ' ') {
		canon.takePicture();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}