#ifndef __DestroyEnemyS_h__
#define __DestroyEnemyS_h__

#include "Message.h"

class ShootingAi;

class DestroyEnemyS: public Message
{
private: 
	ShootingAi* _m_pEnemy;

public: 
	DestroyEnemyS(ShootingAi* aEnemyS);

	virtual ~DestroyEnemyS();
};

#endif
