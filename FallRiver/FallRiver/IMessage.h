#include <Windows.h>

#ifndef __IMessage_h__
#define __IMessage_h__

typedef		int		MSGID;

class IMessage
{
public:
	IMessage( void ) {}
	virtual ~IMessage( void ) = 0 {}

	virtual MSGID	GetMessageID( void )	= 0 {}

private:
	IMessage( const IMessage& );
	IMessage& operator= ( const IMessage& );
};

#endif
