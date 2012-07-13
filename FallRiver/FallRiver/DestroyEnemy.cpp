#include "DestroyEnemy.h"
#include "Enemy.h"

DestroyEnemy::DestroyEnemy(Enemy* aEnemyC) : Message(MSG_DESTROY_ENEMY)
{
	m_pEnemy = aEnemyC;
	m_pEnemy->AddRef();
}


DestroyEnemy::~DestroyEnemy(void)
{
	m_pEnemy->Release();
}
