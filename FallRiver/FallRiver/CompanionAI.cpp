#include "CompanionAI.h"
#include "GamePlayState.h"
#include "Weapon.h"
#include "Enemy.h"
#include "Player.h"
#include "CGame.h"
#include "ViewManager.h"

CompanionAI::CompanionAI()
{
	SetVelX(0);
	SetVelY(0);
	m_nStages = 0;
	m_nStep = 0;
	m_nNumTimes = 0;
	m_nFontID = ViewManager::GetInstance()->RegisterFont("resource/graphics/FallRiver_0.png");
	teaching = true;
}

CompanionAI::~CompanionAI()
{

}

void CompanionAI::Update(float fElapsedTime)
{
	BaseCharacter::Update(fElapsedTime);

	switch(m_nStages)
	{
		// Using Flashlight
	case 0:
		{
			if( m_nNumTimes == 0 )
				m_nNumTimes = 5;

			if( m_nNumTimes <= m_nStep )
			{
				m_nStages++;
				m_nStep = 0;
			}
			break;
		}
		// Attracting a zombies attention
	case 1:
		{
			if( m_nNumTimes <= m_nStep )
			{
				m_nStages++;
				m_nStep = 0;
			}
			break;
		}
		// Firing guns
	case 2:
		{
			if( m_nNumTimes <= m_nStep )
			{
				teaching = false;
			}
			break;
		}
	}
}

void CompanionAI::Render()
{
	ViewManager* pVM = ViewManager::GetInstance();

	pVM->GetSprite()->Flush();

	RECT reRect = {long(GetPosX() - GamePlayState::GetInstance()->GetCamera().x), long(GetPosY() - GamePlayState::GetInstance()->GetCamera().y), long(reRect.left+GetWidth()), long(reRect.top + GetHeight())};

	pVM->DrawRect(reRect, 255, 255, 0);

}

bool CompanionAI::CheckCollision(IObjects* pBase) 
{
	if( BaseCharacter::CheckCollision(pBase) )
		return true;
	return false;
}

void CompanionAI::HandleEvent(Event* aPEvent)
{

}

void CompanionAI::SaySomething() 
{
	Player* tempPlayer = GamePlayState::GetInstance()->GetPlayer();	

	double playerX = (tempPlayer->GetPosX());
	double npcX = this->GetPosX();
	//double playerY = (tempPlayer->GetRect().bottom/2) + tempPlayer->GetRect().top;
	double playerY = tempPlayer->GetPosY();
	double npcY = this->GetPosY();

	double distance;
	distance = sqrt(pow(playerX - npcX,2) + pow(playerY - npcY,2));

	if( distance > 100 )
		return;

	ViewManager* pVM = ViewManager::GetInstance();

	RECT questBox;
	questBox.left = 0;
	questBox.top = CGame::GetInstance()->GetScreenHeight() - 100;
	questBox.right = CGame::GetInstance()->GetScreenWidth();
	questBox.bottom = CGame::GetInstance()->GetScreenHeight();
	pVM->DrawRect(questBox, 100, 100, 100);

	switch(m_nStages)
	{
		// Using Flashlight
	case 0:
		{
			if( m_nStep == 0 )
				pVM->DrawFont(m_nFontID, "Alright I need you to shine your flashlight over there so I can see the zombies", 10, 500, 0.6f, 0.6f);
			else if( m_nStep == 1)
				pVM->DrawFont(m_nFontID, "Keep it up!", 10, 500, 0.6f, 0.6f);
			else if( m_nStep == 2 )
				pVM->DrawFont(m_nFontID, "Come on we can do this!", 10, 500, 0.6f, 0.6f);
			else if( m_nStep == 3 )
				pVM->DrawFont(m_nFontID, "Alright one more!", 10, 500, 0.6f, 0.6f);
			break;
		}
		// Attracting a zombies attention
	case 1:
		{
				pVM->DrawFont(m_nFontID, "Hey see if you can attract draw them over to that tree with your flashlight!\n I could get a clear shot over there if you do it right! \n Shine your flashlight at the tree!", 10, 500, 0.6f, 0.6f);

			break;
		}
		// Firing guns
	case 2:
		{
			break;
		}
	}
}

