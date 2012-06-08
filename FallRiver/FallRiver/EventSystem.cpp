

#include "EventSystem.h"
#include "Event.h"
#include "IListener.h"

EventSystem::EventSystem() 
{
}

EventSystem::~EventSystem() {
}

EventSystem::EventSystem(EventSystem& aEventsys) 
{
}

bool EventSystem::AlreadyRegistered(int aEventid, IListener* aPClient) 
{
	return true;
}

void EventSystem::DispatchEvent(Event* aEvent)
{
}

EventSystem* EventSystem::GetInstance() 
{
	static EventSystem s_Instance;

	return &s_Instance;
}

void EventSystem::RegisterClient(int aEventid, IListener* aClient) 
{
}

void EventSystem::UnregisterClient(int aEventid, IListener* aClient) 
{
}

void EventSystem::UnregisterAllClients(IListener* aClient) 
{
}

bool EventSystem::HasEventTriggered(int aEventid) 
{
	return true;
}

void EventSystem::SendEvent(int aEventid, void* aData) 
{
}

void EventSystem::SendUniqueEvent(int aEventid, void* aData) 
{
}

void EventSystem::ProcessEvents() 
{
}

void EventSystem::ClearEvents() 
{
}

void EventSystem::Shutdown() 
{
}

