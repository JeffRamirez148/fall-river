#include "DestroyEnemyS.h"
#include "ShootingAi.h"
DestroyEnemyS::DestroyEnemyS(ShootingAi* aEnemyS) : Message(MSG_DESTROY_ENEMYS)
{
	_m_pEnemy = aEnemyS;
	_m_pEnemy->AddRef();
}

DestroyEnemyS::~DestroyEnemyS() 
{
	_m_pEnemy->Release();
}
