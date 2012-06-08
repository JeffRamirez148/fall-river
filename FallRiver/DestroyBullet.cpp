#include "DestroyBullet.h"
#include "Bullet.h"
#include "Message.h"

DestroyBullet::DestroyBullet(Bullet* aBullet) : Message(MSG_1)
{
}

DestroyBullet::~DestroyBullet() 
{
}

