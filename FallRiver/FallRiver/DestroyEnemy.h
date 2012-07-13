#pragma once
#include "Message.h"

class Enemy;

class DestroyEnemy : public Message
{
private:
	Enemy* m_pEnemy;
public:
	Enemy* GetEnemy(void) { return m_pEnemy; }
	DestroyEnemy(Enemy* aEnemyC);
	virtual ~DestroyEnemy(void);
};

