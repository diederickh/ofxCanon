#include "CanonPictureEvent.h"
#include "Canon.h"

namespace roxlu {

std::string CanonPictureEvent::getFilePath() {
	return Canon::instance().getDownloadDir() + file_name;
}
	

} // roxlu
