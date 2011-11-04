#ifndef ROXLU_CANONTASKGETPROPERTYH
#define ROXLU_CANONTASKGETPROPERTYH

#include "CanonTask.h"

namespace roxlu {
	class CanonTaskGetProperty : public CanonTask {
		public:
			
			CanonTaskGetProperty(EdsPropertyID property)
				:property_id(property)
				,CanonTask(TASK_GET_PROPERTY) 
			{
			}
			
			~CanonTaskGetProperty() {
			}
			
			virtual bool execute();
			
		private:
			EdsError getProperty(EdsPropertyID propID);
			EdsPropertyID property_id;
	};
}; // roxlu
#endif
