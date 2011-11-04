#include "CanonConnection.h"
#include "Canon.h"

namespace roxlu {

CanonConnection::CanonConnection(Canon* can)
	:canon(can)
{
}

CanonConnection::~CanonConnection() {
}

void CanonConnection::run() {
	Poco::Thread::sleep(3000);
	while(true) {
		if(!canon->isCameraConnected()) {
			printf("Canon: restarting SDK\n");
			canon->restartSDK();
		}
		Poco::Thread::sleep(5000);
	}
}

} // roxlu