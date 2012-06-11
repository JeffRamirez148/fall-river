#ifndef __DestroyPickUp_h__
#define __DestroyPickUp_h__

#include "Message.h"

class PickUp;

class DestroyPickUp: public Message
{
private: 
	PickUp* _m_pPickup;
public: 
	DestroyPickUp(PickUp* aPickUp);
	virtual ~DestroyPickUp();
};

#endif
