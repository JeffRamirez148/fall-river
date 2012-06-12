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
	ShootingAi* GetEnemyS(void) { return _m_pEnemy; }
	virtual ~DestroyEnemyS();
};

#endif
