#include <Windows.h>
using namespace std;

#ifndef __DestroyPickUp_h__
#define __DestroyPickUp_h__

// #include "PickUp.h"
#include "Message.h"

class PickUp;
// class Message;

class DestroyPickUp: public Message
{
private: 
	PickUp* _m_pPickup;
public: 
	DestroyPickUp(PickUp* aPickUp);

	~DestroyPickUp() = 0;
};

#endif
