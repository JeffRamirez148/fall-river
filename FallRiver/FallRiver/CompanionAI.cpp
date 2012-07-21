#include "CompanionAI.h"
#include "ChasingAI.h"
#include "GamePlayState.h"
#include "Weapon.h"
#include "Enemy.h"
#include "Player.h"
#include "CGame.h"
#include "ViewManager.h"
#include "TutorialState.h"
#include "DirectInput.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"

CompanionAI::CompanionAI()
{
	m_nCharacterType = CHA_COMPANION;
	SetVelX(0);
	SetVelY(0);
	m_nStages = 0;
	m_nStep = 0;
	m_nNumTimes = 0;
	m_nSpawnCounter = 0;
	m_fSpawnTime = 0;
	enemies = 0;
	m_dwGunDelay = 0;
	m_nFontID = ViewManager::GetInstance()->RegisterFont("resource/graphics/FallRiver_0.png");
	talkBox = ViewManager::GetInstance()->RegisterTexture("resource/graphics/Paperthingy.png");
	teaching = true;
	talking = false;
	spawning = false;

	m_cFriend = TutorialState::GetInstance()->GetPlayer();

	//AnimInfo startup
	m_playerAnim.curAnimation = 0;
	m_playerAnim.curAnimID = 0;
	m_playerAnim.curFrame = 0;
	m_playerAnim.fTime = 0;

	SetDirection(DIRE_UP);

	m_pOF = Factory::GetInstance();
	m_fSpawnTime = 0;
}

CompanionAI::~CompanionAI()
{
	delete m_cWeapon;
}

void CompanionAI::Update(float fElapsedTime)
{
	BaseCharacter::Update(fElapsedTime);
	m_fSpawnTime += fElapsedTime;
	m_cWeapon->SetDamage(50);

	m_cWeapon->Update(fElapsedTime);

	for(unsigned int i = 0; i < m_cEnemies.size(); i++)
	{
		if( m_cEnemies[i]->GetState() == GONE )
		{
			delete m_cEnemies[i];
			m_cEnemies.pop_back();
			enemies++;
			m_nSpawnCounter--;
			break;
		}
		if(m_nStages == 2 )
			m_cEnemies[i]->MoveTo(GetPosX() + 200, GetPosY(), 80);
		else
			m_cEnemies[i]->MoveTo(GetPosX(), GetPosY()-100, 80);
		m_cEnemies[i]->Update(fElapsedTime);
		m_cEnemies[i]->Enemy::Update(fElapsedTime);
	}

	if( talking && DirectInput::GetInstance()->KeyPressed(DIK_SPACE) )
		m_nStep++;

	switch(m_nStages)
	{
		// talking
	case 0:
		{
			m_playerAnim.curAnimation = 2;
			if( m_nNumTimes == 0 )
				m_nNumTimes = 5;

			if( m_nNumTimes <= m_nStep )
			{
				m_nStages++;
				m_nStep = 0;
				m_nNumTimes = 5;
				//TutorialState::GetInstance()->GetPlayer()->SetLocked(false);
			}
			break;
		}
		// Using lights
	case 1:
		{
			m_playerAnim.curAnimation = 1;
			spawning = true;

			if( m_cFriend->IsOn() && m_cFriend->GetDirection() == DIRE_UP && m_cEnemies.size() > 0 && m_dwGunDelay <= GetTickCount() )
			{
				double playerX = (m_cEnemies.back()->GetPosX());
				double myX = GetPosX();
				double playerY = m_cEnemies.back()->GetPosY();
				double myY = GetPosY();

				double distance;
				distance = sqrt(pow(playerX - myX,2) + pow(playerY - myY,2));

				if( distance < 120 )
				{
					m_dwGunDelay = GetTickCount() + 1000;
					m_cWeapon->FireWeapon();
				}
			}
			if( enemies == 3 )
			{
				spawning = false;
				m_nStages++;
				m_nStep = 0;
				m_nNumTimes = 10;
				
				Weapon* pWeap = new Weapon();
				pWeap->SetOwner(m_cFriend);
				pWeap->Init(WPN_PISTOL, 100, 0);
				pWeap->SetHeight(32);
				pWeap->SetWidth(32);
				m_cFriend->AddWeapon(pWeap);
			}
			break;
		}
		// Shooting enemies
	case 2:
		{
			m_playerAnim.curAnimation = 2;
			spawning = true;
			if( enemies == 6 )
			{
				spawning = false;
				m_nStages++;
				m_nStep = 0;
				m_nNumTimes = 5;
				m_cFriend->SetLocked(true);
			}
			break;
		}
		// Switching Guns
	case 3:
		{
			m_playerAnim.curAnimation = 1;
			if( m_nNumTimes <= m_nStep )
			{
				m_nStages++;
				m_nStep = 0;
				teaching = false;
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

	//pVM->GetSprite()->Flush();

	pVM->DrawAnimation(&m_playerAnim, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2  ,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight(), 1.5f, 1.5f);

	//RECT reRect = {long(GetPosX() - GamePlayState::GetInstance()->GetCamera().x), long(GetPosY() - GamePlayState::GetInstance()->GetCamera().y), long(reRect.left+GetWidth()), long(reRect.top + GetHeight())};

	//pVM->DrawRect(reRect, 255, 255, 0);
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

	//if( distance > 100 )
	//return;

	ViewManager* pVM = ViewManager::GetInstance();

	RECT talkRect;
	talkRect.left = 0;
	talkRect.top = CGame::GetInstance()->GetScreenHeight() - 100;
	talkRect.right = CGame::GetInstance()->GetScreenWidth();
	talkRect.bottom = CGame::GetInstance()->GetScreenHeight();

	RECT src_Rect = {0,200,800,300};
	pVM->DrawStaticTexture(talkBox,0,CGame::GetInstance()->GetScreenHeight() - 130.0f,1.0f,2.5f,&src_Rect);

	pVM->GetSprite()->Flush();

	switch(m_nStages)
	{
		// Using Flashlight
	case 0:
		{
			if( DirectInput::GetInstance()->JoystickIsUnplugged(0) )
			{
				switch(m_nStep)
				{
				case 0:
					{
						pVM->DrawFont(m_nFontID, "Steven - \n\n Aghh my leg... I don't think I can walk...\n\n\n\t Press \"Space\" to Continue", 12, 500, 0.7f, 0.7f);
						talking = true;
					}
					break;
				case 1:
					{
						pVM->DrawFont(m_nFontID, "Steven - \n\n You're terrible driving cost me my dang leg\n and you turn up just fine. Well that's total freakin' crap.\n\n\n\t Press \"Space\" to Continue", 12, 500, 0.7f, 0.7f);
						talking = true;
					}
					break;
				case 2:
					{
						pVM->DrawFont(m_nFontID, "Steven - \n\n Forget it... By now whatever zombies nearby heard the crash and\n are on there way over here to kill us.\n\n\n\t Press \"Space\" to Continue", 12, 500, 0.7f, 0.7f);
						talking = true;
					}
					break;
				case 3:
					{
						pVM->DrawFont(m_nFontID, "Steven - \n\n Listen to me. I'm not gonna live much longer with my leg so\n messed up, so I need YOU to go into the city\n to save my sister.\n\n\t Press \"Space\" to Continue", 12, 500, 0.7f, 0.7f);
						talking = true;
					}
					break;
				case 4:
					{
						pVM->DrawFont(m_nFontID, "Steven - \n\n Least I can do to help you along is teaching you how to survive\n but you better not die before you save my sister. Just because\n you married her doesn't mean you can treat her how you like. \n\n\t Press \"Space\" to Continue", 12, 500, 0.7f, 0.7f);
						talking = true;
					}
					break;
				}
			}
			else
			{
				switch(m_nStep)
				{
				case 0:
					{
						pVM->DrawFont(m_nFontID, "Steven - \n\n Aghh my leg... I don't think I can walk...\n\n\n\t Press \"A\" to Continue", 12, 500, 0.7f, 0.7f);
						talking = true;
					}
					break;
				case 1:
					{
						pVM->DrawFont(m_nFontID, "Steven - \n\n You're terrible driving cost me my dang leg\n and you turn up just fine. Well that's total freakin' crap.\n\n\n\t Press \"A\" to Continue", 12, 500, 0.7f, 0.7f);
						talking = true;
					}
					break;
				case 2:
					{
						pVM->DrawFont(m_nFontID, "Steven - \n\n Forget it... By now whatever zombies nearby heard the crash and\n are on there way over here to kill us.\n\n\n\t Press \"A\" to Continue", 12, 500, 0.7f, 0.7f);
						talking = true;
					}
					break;
				case 3:
					{
						pVM->DrawFont(m_nFontID, "Steven - \n\n Listen to me. I'm not gonna live much longer with my leg so\n messed up, so I need YOU to go into the city\n to save my sister.\n\n\t Press \"A\" to Continue", 12, 500, 0.7f, 0.7f);
						talking = true;
					}
					break;
				case 4:
					{
						pVM->DrawFont(m_nFontID, "Steven - \n\n Least I can do to help you along is teaching you how to survive\n but you better not die before you save my sister. Just because\n you married her doesn't mean you can treat her how you like. \n\n\t Press \"A\" to Continue", 12, 500, 0.7f, 0.7f);
						talking = true;
					}
					break;
				}
			}

			break;
		}
		// Switching Lights
	case 1:
		{
			switch(m_nStep)
			{
			case 0:
				{
					if( enemies == 0)
						pVM->DrawFont(m_nFontID, "Steven - \n\n First of all I need you to shine that flashlight on the zombies\n so I can get a clear shot at them.\n\n Press \"F\" To turn on your flashlight", 12, 500, 0.7f, 0.7f);
					else if( enemies == 1 )
						pVM->DrawFont(m_nFontID, "Steven - \n\n Keep it up they'll probably keep coming.\n\n Press \"F\" To turn on your flashlight", 12, 500, 0.7f, 0.7f);
					else if( enemies == 2 )
						pVM->DrawFont(m_nFontID, "Steven - \n\n I only see one more Shine your flashlight on him.\n\n Press \"F\" To turn on your flashlight", 12, 500, 0.7f, 0.7f);
					talking = false;
				}
				break;
			}
			break;
		}
		// Firing guns
	case 2:
		{
			switch(m_nStep)
			{
			case 0:
				{
				pVM->DrawFont(m_nFontID, "Steven - \n\n I've Lost to much blood, I'm not gonna last much longer.\n Take my gun and shoot them.\n\n\t Press \"Space\" to Continue", 12, 500, 0.7f, 0.7f);
				talking = true;
				}
				break;
			case 1:
				{
					pVM->DrawFont(m_nFontID, "Steven - \n\nThey are coming from the right. Make sure you line up your shots\n or you'll just be wasting bullets.\n\n Press or Hold \"SPACE\" to Fire Weapon. \t Press \"R\" to Reload", 12, 500, 0.7f, 0.7f);
					m_cFriend->SetLocked(false);
					talking = false;
				}
				break;
			}
			break;
		}
		// Switching weapons
	case 3:
		{
			switch(m_nStep)
			{
			case 0:
				{
					pVM->DrawFont(m_nFontID, "Steven - \n\n That's the last of them for now..\n I need you to listen up cause  I got a few more things to say.\n\n\t Press\"SPACE\" to Continue", 12, 500, 0.7f, 0.7f);
					talking = true;
				}
				break;
			case 1:
				{
					pVM->DrawFont(m_nFontID, "Steven - \n\n If you come across anymore weapons\n You can press \"Tab\" to switch weapons.\n\n\t Press\"SPACE\" to Continue", 12, 500, 0.7f, 0.7f);
					talking = true;
				}
				break;
			case 2:
				{
					pVM->DrawFont(m_nFontID, "Steven - \n\n Right now all you have is a Machete and that pistol.\n but I'm sure you'll find a shotgun or two once you get into town.\n\n\t Press\"SPACE\" to Continue", 12, 500, 0.7f, 0.7f);
					talking = true;
				}
				break;
			case 3:
				{
					pVM->DrawFont(m_nFontID, "Steven - \n\n Also you can press \"E\" or \"Q\" to change\n what kind of light your using.\n You have a flashlight, Maglight, a Lantern and a lighter.\n\n\t Press\"SPACE\" to Continue", 12, 500, 0.7f, 0.7f);
					talking = true;
				}
				break;
			case 4:
				{
					pVM->DrawFont(m_nFontID, "Steven - \n\n That's all I can teach you. Your on your own from now on.\n You need to go through the forest and get into Fall River.\n Save my sister, and be careful.\n Zombies aren't the only danger out there.\n\n\t Press\"SPACE\" to Continue", 12, 500, 0.7f, 0.7f);
					talking = true;
				}
				break;
			}
		}
	case 4:
		{
		}
	}
}

void CompanionAI::Spawn()
{

	ObjectManager* m_pOM = ObjectManager::GetInstance();
	if( m_nSpawnCounter < 1 )
	{
		m_cEnemies.push_back(nullptr);
		m_cEnemies.back() = (ChasingAI*)m_pOF->CreateObject( _T("ChasingAI") );
		ChasingAI* pEnemy = (ChasingAI*)(m_cEnemies.back());
		pEnemy->SetHeight(GetHeight());
		pEnemy->SetWidth(GetWidth());
		pEnemy->SetImageID(-1);
		pEnemy->SetTarget(TutorialState::GetInstance()->GetPlayer());
		pEnemy->SetPosX(GetPosX());
		pEnemy->SetPosY(GetPosY()-400);
		pEnemy->SetHealth(100);
		pEnemy->SetAnimation(ViewManager::GetInstance()->RegisterAnimation("resource/graphics/Zombies.xml"));
		pEnemy->SetLocked(true);
		m_pOM->AddObject(pEnemy);
		TutorialState::GetInstance()->AddEnemy(m_cEnemies.back());
		m_fSpawnTime = 0;
		m_nSpawnCounter++;
	}
}

void CompanionAI::SpawnRight()
{

	ObjectManager* m_pOM = ObjectManager::GetInstance();
	if( m_nSpawnCounter < 1 )
	{
		m_cEnemies.push_back(nullptr);
		m_cEnemies.back() = (ChasingAI*)m_pOF->CreateObject( _T("ChasingAI") );
		ChasingAI* pEnemy = (ChasingAI*)(m_cEnemies.back());
		pEnemy->SetHeight(GetHeight());
		pEnemy->SetWidth(GetWidth());
		pEnemy->SetImageID(-1);
		pEnemy->SetTarget(TutorialState::GetInstance()->GetPlayer());
		pEnemy->SetPosX(GetPosX()+400);
		pEnemy->SetPosY(GetPosY());
		pEnemy->SetHealth(100);
		pEnemy->SetAnimation(ViewManager::GetInstance()->RegisterAnimation("resource/graphics/Zombies.xml"));
		pEnemy->SetLocked(true);
		m_pOM->AddObject(pEnemy);
		TutorialState::GetInstance()->AddEnemy(m_cEnemies.back());
		m_fSpawnTime = 0;
		m_nSpawnCounter++;
	}
}