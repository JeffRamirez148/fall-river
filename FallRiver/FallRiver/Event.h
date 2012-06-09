#ifndef __Event_h__
#define __Event_h__

#include <string>
using std::string;

typedef string EVENTID;		//	could be an int or enum, just used strings to change it
							//	up.
class Event
{
private: 
	EVENTID			m_EventID;	//	The event's id type.
	void*			m_pParam;	//	Store any variable type (but only one)
public:
	Event(EVENTID eventID, void* pParam = NULL)
	{
		m_EventID = eventID;
		m_pParam  = pParam;
	}

	~Event() {}

	//	Accessors:
	inline EVENTID  GetEventID(void)	{	return m_EventID;	}
	inline void*	GetParam(void)		{	return m_pParam;	}
};

#endif
