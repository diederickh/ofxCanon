#include "CanonTaskCloseSession.h"
#include "Canon.h"

namespace roxlu {
	
bool CanonTaskCloseSession::execute() {
	EdsError err = EDS_ERR_OK;
	err = EdsCloseSession(canon->camera);
	canon->setSessionOpen(false);
	if(err != EDS_ERR_OK) {
		printf("Canon: error while trying to close the current session.\n");
		return true; // even when we got an error we need to stop the connection
	}
	printf("Canon: closed session.\n");
	return true;
}

} // roxlu