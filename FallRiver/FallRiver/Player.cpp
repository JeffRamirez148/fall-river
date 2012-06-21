#include "Player.h"
#include "Quests.h"
#include "GamePlayState.h"
#include "Enemy.h"
#include "ViewManager.h"
#include "DirectInput.h"
#include "Weapon.h"
#include "Light.h"
#include "EventSystem.h"

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

	//AnimInfo startup
	m_playerAnim.curAnimation = 0;
	m_playerAnim.curAnimID = 0;
	m_playerAnim.curFrame = 0;
	m_playerAnim.fTime = 0;
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

	if((pDI->KeyDown(DIK_RIGHT) || pDI->KeyDown(DIK_LEFT)|| pDI->KeyDown(DIK_UP)|| pDI->KeyDown(DIK_DOWN)) && m_playerAnim.curAnimation == 0)
	{
		m_playerAnim.curAnimation = 1;
		m_playerAnim.curFrame = 0;
		m_playerAnim.fTime = 0;
	}
	else if((!pDI->KeyDown(DIK_RIGHT) && !pDI->KeyDown(DIK_LEFT)&& !pDI->KeyDown(DIK_UP) && !pDI->KeyDown(DIK_DOWN)) && m_playerAnim.curAnimation == 1)
	{
		m_playerAnim.curAnimation = 0;
		m_playerAnim.curFrame = 0;
		m_playerAnim.fTime = 0;
	}

	for(unsigned int i = 0; i < m_vpWeapons.size(); i++)
		m_vpWeapons[i]->Update(fElapsedTime);

	//Updating the player's frame and timer for animations
	Animation thisAnim = ViewManager::GetInstance()->GetAnimation(m_playerAnim.curAnimID);
	m_playerAnim.fTime += fElapsedTime;

	if(m_playerAnim.fTime >= thisAnim.frames[m_playerAnim.curAnimation][m_playerAnim.curFrame].duration)
	{
		m_playerAnim.fTime -= thisAnim.frames[m_playerAnim.curAnimation][m_playerAnim.curFrame].duration;
		m_playerAnim.curFrame++;
		if(m_playerAnim.curFrame < (int)thisAnim.frames[m_playerAnim.curAnimation].size())
		{
		if(strcmp(thisAnim.frames[m_playerAnim.curAnimation][m_playerAnim.curFrame].eventMsg,"none") != 0)
			EventSystem::GetInstance()->SendEvent(thisAnim.frames[m_playerAnim.curAnimation][m_playerAnim.curFrame].eventMsg, this);
		}
		if((m_playerAnim.curFrame == thisAnim.frames[m_playerAnim.curAnimation].size()) && thisAnim.looping[m_playerAnim.curAnimation])
			m_playerAnim.curFrame = 0;
		else if(m_playerAnim.curFrame == thisAnim.frames[m_playerAnim.curAnimation].size() && !thisAnim.looping[m_playerAnim.curAnimation])
			m_playerAnim.curFrame = thisAnim.frames.size() -1;
	}
}

void Player::Render()
{
	ViewManager* pVM = ViewManager::GetInstance();
	//Drawing Player Placeholder Sprite
	pVM->DrawAnimation(&m_playerAnim, (int)GetPosX(), (int)GetPosY());
	//pVM->DrawRect(GetRect(), 0, 0, 255);

	for(unsigned int i = 0; i < m_vpWeapons.size(); i++)
		m_vpWeapons[i]->Render();
}

bool Player::CheckCollision(IObjects* pBase) 
{
	Animation thisAnim = ViewManager::GetInstance()->GetAnimation(m_playerAnim.curAnimID);
	Frame thisFrame = thisAnim.frames[m_playerAnim.curAnimation][m_playerAnim.curFrame];

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
				if(pEn->GetRect().left <= (GetPosX() + thisFrame.colRect.left) && (GetPosX() + thisFrame.colRect.left) - pEn->GetRect().left <= 5) //Formerly GetRect.right
				{
					pEn->SetPosX(float(GetPosX() + thisFrame.colRect.right));
					GamePlayState::GetInstance()->SetCanMoveRight(false);
					pEn->SetCanMove(false);
				}
				else if(pEn->GetRect().right >= (GetPosX() + thisFrame.colRect.right) && pEn->GetRect().right - (GetPosX() + thisFrame.colRect.right) <= 5) //Formerly GetRect.left
				{
					pEn->SetPosX(float(GetRect().left-pEn->GetWidth()));
					GamePlayState::GetInstance()->SetCanMoveLeft(false);
					pEn->SetCanMove(false);
				}
				else if(pEn->GetRect().top <= (GetPosY() + thisFrame.colRect.top) && (GetPosY() + thisFrame.colRect.top)  - pEn->GetRect().top <= 5) //Formerly GetRect.bottom
				{
					pEn->SetPosY(float(GetPosY() + thisFrame.colRect.bottom));
					GamePlayState::GetInstance()->SetCanMoveUp(false);
					pEn->SetCanMove(false);
				}
				else if(pEn->GetRect().bottom >= (GetPosY() + thisFrame.colRect.bottom)  && pEn->GetRect().bottom - (GetPosY() + thisFrame.colRect.bottom) <= 5) //Formerly GetRect.top
				{
					pEn->SetPosY(float(GetRect().top-pEn->GetHeight()));
					GamePlayState::GetInstance()->SetCanMoveDown(false);
					pEn->SetCanMove(false);
				}
				return true;
			}
			// Fixing the movement.. TODO: Change So is used for New Camera
			{
				if( (GetPosX() + thisFrame.colRect.right) <= pBase->GetRect().left + 5 )
					GamePlayState::GetInstance()->SetCanMoveRight(false);
				else if( (GetPosX() + thisFrame.colRect.left)  >= pBase->GetRect().right - 5 )
					GamePlayState::GetInstance()->SetCanMoveLeft(false);
				else if( (GetPosY() + thisFrame.colRect.top)  >= pBase->GetRect().bottom -5 )
					GamePlayState::GetInstance()->SetCanMoveUp(false);
				else if( (GetPosY() + thisFrame.colRect.bottom) <= pBase->GetRect().top + 5 )
					GamePlayState::GetInstance()->SetCanMoveDown(false);
			}
		}
		return true;
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

