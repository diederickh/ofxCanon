#ifndef OFXCANONCOMMANDH
#define OFXCANONCOMMANDH

#include "ofxCommand.h"

class ofxCanonCommand : public ofxCommand {
public:
	ofxCanonCommand(std::string sName, ofxCanonModel* pModel):ofxCommand(sName),model(pModel){};
	ofxCanonModel* getModel() { return model; };
	
	virtual bool execute() = 0;

protected:
	ofxCanonModel* model;
};
#endif