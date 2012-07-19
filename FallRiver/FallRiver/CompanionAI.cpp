#include "CompanionAI.h"
#include "GamePlayState.h"
#include "Weapon.h"
#include "Enemy.h"
#include "Player.h"
#include "CGame.h"
#include "ViewManager.h"
#include "DirectInput.h"

CompanionAI::CompanionAI()
{
	m_nCharacterType = CHA_COMPANION;
	SetVelX(0);
	SetVelY(0);
	m_nStages = 0;
	m_nStep = 0;
	m_nNumTimes = 0;
	m_nFontID = ViewManager::GetInstance()->RegisterFont("resource/graphics/FallRiver_0.png");
	talkBox = ViewManager::GetInstance()->RegisterTexture("resource/graphics/Paperthingy.png");
	teaching = true;

	//AnimInfo startup
	m_playerAnim.curAnimation = 0;
	m_playerAnim.curAnimID = 0;
	m_playerAnim.curFrame = 0;
	m_playerAnim.fTime = 0;
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
				m_nNumTimes = 3;

			if( m_nNumTimes <= m_nStep )
			{
				m_nStages++;
				m_nStep = 0;
				m_nNumTimes = 5;
			}
			break;
		}
		// Switching lights
	case 1:
		{
			if( m_nStep >= 5 && GamePlayState::GetInstance()->GetPlayer()->GetLightType() == 0 )
			{
				m_nStages++;
				m_nStep = 0;
				m_nNumTimes = 10;
			}
			break;
		}
		// Shooting enemies
	case 2:
		{
			if( m_nNumTimes <= m_nStep )
			{
				m_nStages++;
				m_nStep = 0;
				m_nNumTimes = 1;
			}
			break;
		}
		// Switching Guns
	case 3:
		{
			if( m_nNumTimes <= m_nStep )
			{
				m_nStages++;
				m_nStep = 0;
			}
			break;
		}
		// Hiding in bushes
	case 4:
		{
			if( m_nNumTimes <= m_nStep )
			{
				m_nStages++;
				m_nStep = 0;
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
	BaseCharacter::Render();

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
	double myX = GetPosX();
	double playerY = tempPlayer->GetPosY();
	double myY = GetPosY();

	double distance;
	distance = sqrt(pow(playerX - myX,2) + pow(playerY - myY,2));

	if( distance > 100 )
		return;

	ViewManager* pVM = ViewManager::GetInstance();

	RECT talkRect;
	talkRect.left = 0;
	talkRect.top = CGame::GetInstance()->GetScreenHeight() - 100;
	talkRect.right = CGame::GetInstance()->GetScreenWidth();
	talkRect.bottom = CGame::GetInstance()->GetScreenHeight();

	RECT src_Rect = {0,200,800,300};
	pVM->DrawStaticTexture(talkBox,0,CGame::GetInstance()->GetScreenHeight() - 130.0f,1.0f,2.5f,&src_Rect);

	switch(m_nStages)
	{
		// Using Flashlight
	case 0:
		{
			if( DirectInput::GetInstance()->JoystickIsUnplugged(0) )
			{
				if( m_nStep == 0 )
					pVM->DrawFont(m_nFontID, "Alright let me teach me a few things before you run off.\n Turn your flashlight on and off by pressing    \"F\" \n    Turn on your Flashlight now.", 12, 500, 0.7f, 0.7f);
				else if( m_nStep == 1 )
					pVM->DrawFont(m_nFontID, "Ok now turn your flashlight off", 12, 500, 0.7f, 0.7f);
				else
					pVM->DrawFont(m_nFontID, "Ok turn your flashlight back on\n so I can teach you about your different lights.", 12, 500, 0.7f, 0.7f);
			}
			else
			{
				if( m_nStep == 0 )
					pVM->DrawFont(m_nFontID, "Alright let me teach me a few things before you run off.\n Turn your flashlight on and off by pressing    \"B\" \n    Turn on your Flashlight now.", 12, 500, 0.7f, 0.7f);
				else if( m_nStep == 1 )
					pVM->DrawFont(m_nFontID, "Ok now turn your flashlight off", 12, 500, 0.7f, 0.7f);
				else
					pVM->DrawFont(m_nFontID, "Ok turn your flashlight back on\n so I can teach you about your different lights.", 12, 500, 0.7f, 0.7f);
			}
			break;
		}
		// Switching Lights
	case 1:
		{
			if( DirectInput::GetInstance()->JoystickIsUnplugged(0) )
			{
				if( m_nStep == 0 )
					pVM->DrawFont(m_nFontID, "Thie is your Flashlight.\n It allows you to see far away far away distances\n while only attracting a little attention. \n\n\tPress \"E\" to select your next light source. ", 12, 500, 0.7f, 0.7f);
				else if( m_nStep == 1 )
					pVM->DrawFont(m_nFontID, "This is your MagLight. \nIt will let you see much farther than your flashlight would\n but you'll definitely attract more attention. \n\n\tPress \"E\" to select your next light source.", 12, 500, 0.6f, 0.7f);
				else if( m_nStep == 2 )
					pVM->DrawFont(m_nFontID, "This is your Lantern.\n It allows you to see very far\n but will make everyone in the area aware of where you are. \n\n\tPress \"E\" to select your next light source. ", 12, 500, 0.7f, 0.7f);
				else if( m_nStep == 3 )
					pVM->DrawFont(m_nFontID, "This is your lighter.\n You can barely see at all with it\n however you'll be virtually invisable. \n\n\tPress \"E\" to select your next light source. ", 12, 500, 0.7f, 0.7f);
				else if( m_nStep == 4 )
					pVM->DrawFont(m_nFontID, "Press \"Q\" to select your previous light source. ", 12, 500, 0.7f, 0.7f);
				else
					pVM->DrawFont(m_nFontID, "Now equip your flashlight again!", 12, 500, 0.7f, 0.7f);
			}
			else
			{
				if( m_nStep == 0 )
					pVM->DrawFont(m_nFontID, "Thie is your Flashlight.\n It allows you to see far away far away distances\n while only attracting a little attention. \n\n\tPress \"LB\" to select your next light source. ", 12, 500, 0.7f, 0.7f);
				else if( m_nStep == 1 )
					pVM->DrawFont(m_nFontID, "This is your MagLight. \nIt will let you see much farther than your flashlight would\n but you'll definitely attract more attention. \n\n\tPress \"LB\" to select your next light source.", 12, 500, 0.6f, 0.7f);
				else if( m_nStep == 2 )
					pVM->DrawFont(m_nFontID, "This is your Lantern.\n It allows you to see very far\n but will make everyone in the area aware of where you are. \n\n\tPress \"LB\" to select your next light source. ", 12, 500, 0.7f, 0.7f);
				else if( m_nStep == 3 )
					pVM->DrawFont(m_nFontID, "This is your lighter.\n You can barely see at all with it\n however you'll be virtually invisable. \n\n\tPress \"LB\" to select your next light source. ", 12, 500, 0.7f, 0.7f);
				else if( m_nStep == 4 )
					pVM->DrawFont(m_nFontID, "Press \"RB\" to select your previous light source. ", 12, 500, 0.7f, 0.7f);
				else
					pVM->DrawFont(m_nFontID, "Now equip your flashlight again!", 12, 500, 0.7f, 0.7f);
			}
			break;
		}
		// Firing guns
	case 2:
		{
			//TCHAR buffer[200];
			//_stprintf_s( buffer, 200, _T("Ok now its time to learn how to defend yourself\n if you ever get into trouble. \n\n\tPress or Hold \"Spacebar\" to shoot. \n\tShoot %i times"), 10-m_nStep);
			char buffer[100];
			_itoa_s(m_nNumTimes - m_nStep, buffer, 10);
			//string info = "Ok now its time to learn how to defend yourself\n if you ever get into trouble. \n\n\tPress or Hold \"Spacebar\" to shoot. \n\tShoot ";

			if( DirectInput::GetInstance()->JoystickIsUnplugged(0) )
			{
				pVM->DrawFont(m_nFontID, "Ok now its time to learn how to defend yourself\n if you ever get into trouble. \n\n\tPress or Hold \"Spacebar\" to shoot. \n\tShoot ", 12, 500, 0.7f, 0.7f);
				pVM->DrawFont(m_nFontID, (char*)buffer, 130, 560, 0.7f, 0.7f);
				pVM->DrawFont(m_nFontID, "time(s)", 150, 560, 0.7f, 0.7f);
			}
			else
			{
				pVM->DrawFont(m_nFontID, "Ok now its time to learn how to defend yourself\n if you ever get into trouble. \n\n\tPress or Hold \"RT\" to shoot. \n\tShoot ", 12, 500, 0.7f, 0.7f);
				pVM->DrawFont(m_nFontID, (char*)buffer, 130, 555, 0.7f, 0.7f);
				pVM->DrawFont(m_nFontID, "time(s)", 150, 555, 0.7f, 0.7f);
			}
			break;
		}
		// Switching weapons
	case 3:
		{
			if( DirectInput::GetInstance()->JoystickIsUnplugged(0) )
			{
				pVM->DrawFont(m_nFontID, "Like Lights you also have several weapons you can choose from.\n\n\tPress \"TAB\" To select the next weapon in your inventory", 12, 500, 0.7f, 0.7f);
			}
			else
			{
				pVM->DrawFont(m_nFontID, "Like Lights you also have several weapons you can choose from.\n\n\tPress \"Y\" To select the next weapon in your inventory", 12, 500, 0.7f, 0.7f);

			}
			break;
		}
	case 4:
		{
			if( DirectInput::GetInstance()->JoystickIsUnplugged(0) )
			{
				pVM->DrawFont(m_nFontID, "Last but not least Press \"L\" to see/hide your mission log.\n\n Your mission log displays any current tasks you must complete", 12, 500, 0.7f, 0.7f);
			}
			else
			{
				pVM->DrawFont(m_nFontID, "Last but not least Press \"BACK\" to see/hide your mission log.\n\n Your mission log displays any current tasks you must complete", 12, 500, 0.7f, 0.7f);

			}
		}
	}
}

