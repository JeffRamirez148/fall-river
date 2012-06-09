#include <list>
#include <map>
using std::multimap;
using std::pair;
using std::list;

using namespace std;

#include "Event.h"
#include "IListener.h"

#ifndef __EventSystem_h__
#define __EventSystem_h__

class EventSystem
{
private:
	multimap<EVENTID, IListener*>	m_mCDatabase;
	list<Event>						m_lCurrEvent;

	EventSystem() {/* Do Nothing */}
	~EventSystem() { /* Do Nothing */}
	EventSystem(const EventSystem&);
	EventSystem& operator=(const EventSystem&);

	bool AlreadyRegistered(EVENTID eventid, IListener* pClient);

	void DispatchEvent(Event* pEvent);

public: 
	static EventSystem* GetInstance();

	void RegisterClient(EVENTID eventID, IListener* pClient);

	void UnregisterClient(EVENTID eventID, IListener* pClient);

	void UnregisterAllClients(IListener* pClient);

	bool HasEventTriggered(EVENTID eventID);

	void SendEvent(EVENTID eventID, void* pData);

	void SendUniqueEvent(EVENTID eventID, void* pData);

	void ProcessEvents();

	void ClearEvents();

	void Shutdown();
};

#endif
