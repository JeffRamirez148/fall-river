
#ifndef __Message_h__
#define __Message_h__

#include "IMessage.h"

// Enumeration of message types:
enum MSG_TYPE {MSG_CREATE_BULLET, MSG_CREATE_ENEMYC, MSG_CREATE_ENEMYS, MSG_CREATE_NPC, MSG__CREATE_PICKUP, MSG_DESTROY_BULLET, MSG_DESTROY_ENEMYC, MSG_DESTROY_ENEMY, MSG_DESTROY_ENEMYS, MSG_DESTROY_NPC,  MSG_DESTROY_PICKUP};

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
