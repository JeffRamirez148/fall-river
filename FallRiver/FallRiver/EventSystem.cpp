

#include "EventSystem.h"
#include "Event.h"
#include "IListener.h"

bool EventSystem::AlreadyRegistered(EVENTID eventID, IListener* pClient) 
{
	bool bIsAlreadyRegistered = false;

	//	Make an iterator that will iterate all of our clients that
	//	should be receiveing this event
	pair<multimap<EVENTID, IListener*>::iterator,
		 multimap<EVENTID, IListener*>::iterator> range;

	//	Find all of the clients that are able to receive this event.
	range = m_mCDatabase.equal_range(eventID);

	//	Go through the list of clients that are able to receive this event.
	for(multimap<EVENTID, IListener*>::iterator mmIter = range.first;
					mmIter != range.second; mmIter++)
	{
		//	check if the pointer is equal to the client
		if((*mmIter).second == pClient)
		{
			bIsAlreadyRegistered = true;
			break;
		}
	}

	return bIsAlreadyRegistered;
}

void EventSystem::DispatchEvent(Event* pEvent)
{
	//	Make an iterator that will iterate all of our clients that
	//	should be receiveing this event
	pair<multimap<EVENTID, IListener*>::iterator,
		 multimap<EVENTID, IListener*>::iterator> range;

	//	Find all of the clients that are able to receive this event.
	range = m_mCDatabase.equal_range(pEvent->GetEventID());

	//	Go through the linked list of clients that are able to receive this event.
	for(multimap<EVENTID, IListener*>::iterator mmIter = range.first;
					mmIter != range.second; mmIter++)
	{
		//	Pass this event to the client
		(*mmIter).second->HandleEvent(pEvent);
	}
}

EventSystem* EventSystem::GetInstance() 
{
	static EventSystem s_Instance;

	return &s_Instance;
}

void EventSystem::RegisterClient(EVENTID eventID, IListener* pClient) 
{
		//	Error check to make sure the client exists and hasn't been registered for this event already.
	if (!pClient || AlreadyRegistered(eventID, pClient))	return;

	//	Register (Build) the database of clients.
	m_mCDatabase.insert( make_pair(eventID, pClient) );
}

void EventSystem::UnregisterClient(EVENTID eventID, IListener* pClient) 
{
	//	Make an iterator that will iterate all of our clients that
	//	should be receiveing this event
	pair<multimap<EVENTID, IListener*>::iterator,
		 multimap<EVENTID, IListener*>::iterator> range;

	//	Find all of the clients that are able to receive this event.
	range = m_mCDatabase.equal_range(eventID);

	//	Go through the list of clients that are able to receive this event.
	for(multimap<EVENTID, IListener*>::iterator mmIter = range.first;
					mmIter != range.second; mmIter++)
	{
		//	check if the pointer is equal to the client
		if((*mmIter).second == pClient)
		{
			//	remove the client from the list
			mmIter = m_mCDatabase.erase(mmIter);
			break;
		}
	}
}

void EventSystem::UnregisterAllClients(IListener* pClient) 
{
	multimap<string, IListener*>::iterator mmIter = m_mCDatabase.begin();

	while(mmIter != m_mCDatabase.end())
	{
		if((*mmIter).second == pClient)
		{
			mmIter = m_mCDatabase.erase(mmIter);
		}
		else
			mmIter++;
	}
}

bool EventSystem::HasEventTriggered(EVENTID eventID) 
{
	// Check if the event is waiting to be processed
	list<Event>::iterator iter = m_lCurrEvent.begin();

	for( ; iter != m_lCurrEvent.end(); ++iter )
		if( (*iter).GetEventID() == eventID )
			return true;


	// Not in the queue
	return false;
}

void EventSystem::SendEvent(EVENTID eventID, void* pData) 
{
	//	Push my event into the list.
	Event newEvent(eventID, pData);

	m_lCurrEvent.push_back(newEvent);
}

void EventSystem::SendUniqueEvent(EVENTID eventID, void* pData) 
{
	// Ignore if the event is already in the queue
	if( HasEventTriggered( eventID ) )
		return;

	// Queue the event
	SendEvent( eventID, pData );
}

void EventSystem::ProcessEvents() 
{
	//	Go through my list of events that are waiting to be processed.
	while(m_lCurrEvent.size())
	{
		DispatchEvent(&m_lCurrEvent.front());
		m_lCurrEvent.pop_front();
	}
}

void EventSystem::ClearEvents() 
{
	m_lCurrEvent.clear();
}

void EventSystem::Shutdown() 
{
	m_mCDatabase.clear();
}

