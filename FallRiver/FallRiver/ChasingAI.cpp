#include "ChasingAI.h"
#include "ObjectFactory.h"
#include "BaseCharacter.h"
#include "ViewManager.h"
#include "Enemy.h"

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

bool ChasingAI::CheckCollision(BaseCharacter* pBase) 
{
	return true;
}

void ChasingAI::HandleEvent(Event* aPEvent)
{

}



