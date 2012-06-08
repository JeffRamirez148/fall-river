#include <Windows.h>
using namespace std;

#ifndef __Event_h__
#define __Event_h__

// #include "EventSystem.h"
// #include "IListener.h"

class EventSystem;
class IListener;
class Event;

class Event
{
private: 
	int m_nEventID;
	void* m_pParam;

public: 
	EventSystem* _unnamed_EventSystem_;
	IListener* _unnamed_IListener_;

	Event();

	~Event();
};

#endif
