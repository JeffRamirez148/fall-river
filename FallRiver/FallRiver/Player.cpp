#include "Player.h"
#include "Quests.h"
#include "GamePlayState.h"
#include "Enemy.h"
#include "ViewManager.h"
#include "EventSystem.h"
#include "DirectInput.h"
#include "Weapon.h"
#include "Light.h"
#include "Level.h"

Player::Player()
{
	m_nCharacterType = CHA_PLAYER;
	m_bIsAlive = true;
	m_bIsHidden = false;
	m_nScore = 0;
	m_nLives = 3;
	m_cName = "";
	m_nFrameX = 0;
	m_nFrameY = 0;
	SetDirection(DIRE_UP);
	EventSystem::GetInstance()->RegisterClient( "target_hit", this );
	EventSystem::GetInstance()->RegisterClient( "hit_wall", this );
}

Player::~Player()
{

}

void Player::Update(float fElapsedTime) 
{
	DirectInput* pDI = DirectInput::GetInstance();

	if( pDI->KeyDown(DIK_RIGHT))
	{
		if( pDI->KeyDown(DIK_UP))
			SetDirection(DIRE_UPRIGHT);
		else if(pDI->KeyDown(DIK_DOWN))
			SetDirection(DIRE_DOWNRIGHT);
		else
			SetDirection(DIRE_RIGHT);		

	}
	else if( pDI->KeyDown(DIK_LEFT))
	{
		if( pDI->KeyDown(DIK_UP))
			SetDirection(DIRE_UPLEFT);
		else if(pDI->KeyDown(DIK_DOWN))
			SetDirection(DIRE_DOWNLEFT);
		else
			SetDirection(DIRE_LEFT);		
	}
	else if( pDI->KeyDown(DIK_UP))
		SetDirection(DIRE_UP);
	else if( pDI->KeyDown(DIK_DOWN))
		SetDirection(DIRE_DOWN);

	for(unsigned int i = 0; i < m_vpWeapons.size(); i++)
		m_vpWeapons[i]->Update(fElapsedTime);
}

void Player::Render()
{
	ViewManager* pVM = ViewManager::GetInstance();

	pVM->DrawRect(GetRect(), 0, 0, 255);

	for(unsigned int i = 0; i < m_vpWeapons.size(); i++)
		m_vpWeapons[i]->Render();
}

bool Player::CheckCollision(IObjects* pBase) 
{
		if( pBase->GetObjectType() != OBJ_LEVEL)
	{
		if(BaseObject::CheckCollision(pBase) == true )
		{
			if(pBase->GetObjectType() == OBJ_CHARACTER)
			{
				BaseCharacter* pCh = (BaseCharacter*)pBase;
				if(pCh->GetCharacterType() == CHA_ENEMY)
				{
					Enemy*pEn = (Enemy*)pCh;
					if(!GamePlayState::GetInstance()->CanMoveRight() || !GamePlayState::GetInstance()->CanMoveLeft() || !GamePlayState::GetInstance()->CanMoveDown() || !GamePlayState::GetInstance()->CanMoveUp() )
						return true;
					if(pEn->GetRect().left <= GetRect().right && GetRect().right - pEn->GetRect().left <= 5)
					{
						pEn->SetPosX(float(GetRect().right));
						GamePlayState::GetInstance()->SetCanMoveRight(false);
						pEn->SetCanMove(false);
					}
					else if(pEn->GetRect().right >= GetRect().left && pEn->GetRect().right - GetRect().left <= 5)
					{
						pEn->SetPosX(float(GetRect().left-pEn->GetWidth()));
						GamePlayState::GetInstance()->SetCanMoveLeft(false);
						pEn->SetCanMove(false);
					}
					else if(pEn->GetRect().top <= GetRect().bottom && GetRect().bottom - pEn->GetRect().top <= 5)
					{
						pEn->SetPosY(float(GetRect().bottom));
						GamePlayState::GetInstance()->SetCanMoveUp(false);
						pEn->SetCanMove(false);
					}
					else if(pEn->GetRect().bottom >= GetRect().top && pEn->GetRect().bottom - GetRect().top <= 5)
					{
						pEn->SetPosY(float(GetRect().top-pEn->GetHeight()));
						GamePlayState::GetInstance()->SetCanMoveDown(false);
						pEn->SetCanMove(false);
					}
					return true;
				}
				// Fixing the movement.. TODO: Change So is used for New Camera
				{
					if( GetRect().right <= pBase->GetRect().left + 5 )
						GamePlayState::GetInstance()->SetCanMoveRight(false);
					else if( GetRect().left >= pBase->GetRect().right - 5 )
						GamePlayState::GetInstance()->SetCanMoveLeft(false);
					else if( GetRect().top >= pBase->GetRect().bottom -5 )
						GamePlayState::GetInstance()->SetCanMoveUp(false);
					else if( GetRect().bottom <= pBase->GetRect().top + 5 )
						GamePlayState::GetInstance()->SetCanMoveDown(false);
				}
			}
			return true;
		}
	}
	else
	{
		if( pBase->CheckCollision(this) == true )
		{
			return true;
		}

	}

	GamePlayState::GetInstance()->SetCanMoveDown(true);
	GamePlayState::GetInstance()->SetCanMoveUp(true);
	GamePlayState::GetInstance()->SetCanMoveRight(true);
	GamePlayState::GetInstance()->SetCanMoveLeft(true);
	return false;

}

// Check if the player is still alive
bool Player::CheckLifes() {return m_bIsAlive;}

void Player::AddQuest(Quests* pQuest)
{
	// Just in case
	if(pQuest == nullptr)
		return;

	// Add the quest
	m_vpActiveQuests.push_back(pQuest);
}

void Player::AddWeapon(Weapon* pWeapon)
{
	// Just in case
	if(pWeapon == nullptr)
		return;

	// Add the weapon and make it current
	pWeapon->SetHeight(20);
	pWeapon->SetWidth(10);
	pWeapon->SetPosX(GetPosX()+(GetWidth()/2));
	pWeapon->SetPosY(GetPosY());
	m_vpWeapons.push_back(pWeapon);
	m_currWeapon = pWeapon;
}

void Player::AddLight(Light* pLight) 
{
	// Just in case
	if(pLight == nullptr)
		return;

	// Add the weapon and make it current
	m_vpLights.push_back(pLight);
	m_currLight = pLight;
}

void Player::HandleEvent(Event* pEvent)
{
	if(pEvent->GetEventID() == "target_hit")
	{
		if( pEvent->GetParam() == this )
		{
			SetHealth(GetHealth()-30);
		}
	}
	else if(pEvent->GetEventID() == "hit_wall")
	{
		GamePlayState::GetInstance()->SetCanMoveDown(true);
		GamePlayState::GetInstance()->SetCanMoveUp(true);
		GamePlayState::GetInstance()->SetCanMoveRight(true);
		GamePlayState::GetInstance()->SetCanMoveLeft(true);
	}
}


