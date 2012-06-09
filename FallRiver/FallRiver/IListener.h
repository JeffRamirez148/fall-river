#ifndef __IListener_h__
#define __IListener_h__

class Event;

class IListener
{
public: 
	IListener();
	virtual ~IListener();
	virtual void HandleEvent(Event* aPEvent) = 0;
};

#endif
