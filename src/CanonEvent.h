#ifndef ROXLU_CANONEVENTH
#define ROXLU_CANONEVENTH

#include <string>
namespace roxlu {

class CanonEvent {
public:
	CanonEvent(std::string eventName, void* eventData)
		:name(eventName)
		,data(eventData) 
	{
	}

	void* data;
	std::string name;
private:
};

} // roxlu
#endif