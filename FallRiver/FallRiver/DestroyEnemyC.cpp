#include "DestroyEnemyC.h"
#include "ChasingAi.h"

DestroyEnemyC::DestroyEnemyC(ChasingAI* aEnemyC) : Message(MSG_DESTROY_ENEMYC)
{
	m_pEnemy = aEnemyC;
	m_pEnemy->AddRef();
}

DestroyEnemyC::~DestroyEnemyC() 
{
	m_pEnemy->Release();
}
