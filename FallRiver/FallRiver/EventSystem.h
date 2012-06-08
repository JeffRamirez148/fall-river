#include <Windows.h>
#include <list>
#include <map>
using namespace std;

#ifndef __EventSystem_h__
#define __EventSystem_h__

// #include "Event.h"
// #include "IListener.h"

class Event;
class IListener;

class EventSystem
{
private:
	multimap<int, IListener*> m_mCDatabase;
	list<Event*> m_lCurrEvent;

	EventSystem();

	~EventSystem();

	EventSystem(EventSystem& aEventsys);

	EventSystem& operator=(EventSystem& aEventsys);

	bool AlreadyRegistered(int aEventid, IListener* aPClient);

	void DispatchEvent(Event* aEvent);

public: 
	static EventSystem* GetInstance();

	void RegisterClient(int aEventid, IListener* aClient);

	void UnregisterClient(int aEventid, IListener* aClient);

	void UnregisterAllClients(IListener* aClient);

	bool HasEventTriggered(int aEventid);

	void SendEvent(int aEventid, void* aData);

	void SendUniqueEvent(int aEventid, void* aData);

	void ProcessEvents();

	void ClearEvents();

	void Shutdown();
};

#endif
