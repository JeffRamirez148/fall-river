#ifndef __CreateBullet_h__
#define __CreateBullet_h__

// #include "BaseCharacter.h"
#include "Message.h"

class BaseCharacter;
// class Message;
class CreateBullet;

class CreateBullet: public Message
{
	private:
		BaseCharacter* _owner;

	public:
	CreateBullet();

	~CreateBullet();

};

#endif
