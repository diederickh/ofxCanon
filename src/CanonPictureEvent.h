#ifndef ROXLU_CANONPICTUREEVENTH
#define ROXLU_CANONPICTUREEVENTH

#include <string>

namespace roxlu {

class CanonPictureEvent {
public:
	CanonPictureEvent(std::string fileName)
		:file_name(fileName)
	{
	}

	std::string getFilePath();
	
private:
	std::string file_name;
};

} // roxlu
#endif