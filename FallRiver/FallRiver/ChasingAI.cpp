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

bool ChasingAI::CheckCollision(BaseObject* pBase) 
{
	if(Enemy::CheckCollision(pBase) == true )
	{
		if(pBase->GetObjectType() == OBJ_CHARACTER)
		{
			BaseCharacter* pCh = (BaseCharacter*)pBase;
			if(pCh->GetCharacterType() == CHA_PLAYER)
			{
				if( GetRect().right < pBase->GetRect().left )
					GamePlayState::GetInstance()->SetCanMoveLeft(false);
				else if( GetRect().left > pBase->GetRect().right )
					GamePlayState::GetInstance()->SetCanMoveRight(false);
				else if( GetRect().top > pBase->GetRect().bottom )
					GamePlayState::GetInstance()->SetCanMoveDown(false);
				else if( GetRect().bottom < pBase->GetRect().top )
					GamePlayState::GetInstance()->SetCanMoveUp(false);
			}
		}
		return true;
	}
	return false;
}

void ChasingAI::HandleEvent(Event* aPEvent)
{

}



