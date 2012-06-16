#include "ChasingAI.h"
#include "ObjectFactory.h"
#include "BaseCharacter.h"
#include "ViewManager.h"
#include "Enemy.h"
#include "GamePlayState.h"

ChasingAI::ChasingAI()
{

}

ChasingAI::~ChasingAI()
{

}

void ChasingAI::Update(float fElapsedTime)
{
	Enemy::Update(fElapsedTime);
}

void ChasingAI::Render() 
{
	ViewManager* pVM = ViewManager::GetInstance();

	pVM->DrawRect(GetRect(), 255, 0, 0);
}

bool ChasingAI::CheckCollision(IObjects* pBase) 
{
	return Enemy::CheckCollision(pBase);
}

void ChasingAI::HandleEvent(Event* aPEvent)
{

}



