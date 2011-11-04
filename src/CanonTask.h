#ifndef ROXLU_CANONTASKH
#define ROXLU_CANONTASKH

#include "CanonDebug.h" 

#define 	TASK_INIT				1
#define		TASK_OPEN_SESSION		2
#define		TASK_CLOSE_SESSION		3
#define		TASK_SHUTDOWN			4
#define		TASK_TAKE_PICTURE		5
#define		TASK_DOWNLOAD_PICTURE	6
#define		TASK_GET_PROPERTY		7
#define		TASK_START_EVF			8
#define		TASK_DOWNLOAD_EVF		9
#define		TASK_END_EVF			10

namespace roxlu {
	
	class Canon;

	class CanonTask {
	public:
		CanonTask(int taskID);
		~CanonTask();
		virtual bool execute() = 0;
		void setCanon(Canon* can);
		int task_id;
	protected:
		Canon* canon;
	};
}; // roxlu
#endif