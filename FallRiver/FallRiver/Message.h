
#ifndef __Message_h__
#define __Message_h__

#include "IMessage.h"

// Enumeration of message types:
enum MSG_TYPE { MSG_1, MSG_2 };

class Message: public IMessage
{
	public:

	Message( MSG_TYPE type)
	{
		m_nType = type;
	}

	virtual ~Message(void)
	{ /* do nothing */	}

	virtual MSGID GetMessageID( void )
	{ return m_nType;	}

private:
	int		m_nType;
};

#endif
