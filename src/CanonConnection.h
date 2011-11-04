#ifndef ROXLU_CANONCONNECTIONH
#define ROXLU_CANONCONNECTIONH

#include <Poco/Thread.h>
#include <Poco/Runnable.h>

namespace roxlu {

class Canon;

class CanonConnection : public Poco::Runnable {
	public:
		CanonConnection(Canon* can);
		~CanonConnection();
		virtual void run();
	private:
		Canon* canon;
};

}; // roxlu

#endif