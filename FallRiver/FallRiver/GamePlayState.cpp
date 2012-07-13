#include "GamePlayState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "ObjectManager.h"
#include "OptionsMenuState.h"
#include "PauseMenuState.h"
#include "Level.h"
#include "Particle_Manager.h"
#include "Emitter.h"
#include "CGame.h"
#include "DirectInput.h"
#include "Enemy.h"
#include "EventSystem.h"
#include "Player.h"
#include "CompanionAI.h"
#include "Weapon.h"
#include "HUD.h"
#include "XMLManager.h"
#include "Message.h"
#include "Bullet.h"
#include "ChasingAI.h"
#include "ShootingAi.h"
#include "NPC.h"
#include "PickUp.h"
#include "CreateBullet.h"
#include "DestroyBullet.h"
#include "DestroyEnemyC.h"
#include "DestroyEnemyS.h"
#include "DestroyNPC.h"
#include "DestroyPickUp.h"
#include "Bush.h"
#include "SpawnPoint.h"
#include "LoseMenuState.h"
#include "WinMenuState.h"


GamePlayState::GamePlayState()
{
	m_pVM = nullptr;
	m_pDI = nullptr;
	m_pAM = nullptr;
	m_pOF = nullptr;
	m_pOM = nullptr;
	m_pES = nullptr;
	m_pPM = nullptr;
	m_cPlayer = nullptr;

	m_cWeapon = nullptr;

	backGroundID = -1;
	swingHitID = -1;
	SpawnEnemyAniID = -1;

	winLose = true;
	questFlag = false;
	rainA = -1;
	rainL = -1;
	smokeL = -1;
}

GamePlayState* GamePlayState::GetInstance() 
{
	static GamePlayState s_Instance;

	return &s_Instance;
}

void GamePlayState::Enter()
{
	m_pDI = DirectInput::GetInstance();
	m_pVM = ViewManager::GetInstance();
	m_pOF = Factory::GetInstance();
	m_pOM = ObjectManager::GetInstance();
	m_pES = EventSystem::GetInstance();
	m_pMS = MessageSystem::GetInstance();
	m_pPM = Particle_Manager::GetInstance();
	m_pAM = AudioManager::GetInstance();

	// Rain particles
	rainL = m_pPM->LoadEmitter("rain.xml");
	rainA = m_pPM->ActivateEmitter(rainL);
	// Smoke particles
	smokeL = m_pPM->LoadEmitter("smoke.xml");
	

	int bush = m_pVM->RegisterTexture("resource//graphics//Bush.png");
	SpawnEnemyAniID = m_pVM->RegisterAnimation("resource/graphics/EnimeisChase.xml");


	m_pOF->RegisterClassType< BaseObject	>( _T("BaseObject") );
	m_pOF->RegisterClassType< Level			>( _T("Level") );
	m_pOF->RegisterClassType< Player		>( _T("Player") );
	m_pOF->RegisterClassType< Weapon		>( _T("Weapon") );
	m_pOF->RegisterClassType< Bush			>( _T("Bush") );
	m_pOF->RegisterClassType< NPC			>( _T("NPC") );
	m_pOF->RegisterClassType< PickUp		>( _T("PickUp") );
	m_pOF->RegisterClassType< Enemy			>( _T("Enemy") );
	m_pOF->RegisterClassType< ShootingAi	>( _T("ShootingAi") );
	m_pOF->RegisterClassType< CompanionAI	>( _T("CompanionAI") );
	m_pOF->RegisterClassType< ChasingAI		>( _T("ChasingAI") );
	m_pOF->RegisterClassType< Bullet		>( _T("Bullet") );
	m_pOF->RegisterClassType< SpawnPoint	>( _T("SpawnPoint") );


	Player* pPlayer = nullptr;
	Weapon* pWeapon = nullptr;
	Level* pLevel = nullptr;
	Bush* pBush = nullptr;
	SpawnPoint* pSpawn = nullptr;
	PickUp* pPickUp = nullptr;


	if( pLevel == nullptr )
	{
		m_clevel = (Level*)m_pOF->CreateObject( _T("Level"));
		pLevel = m_clevel;
		pLevel->LoadLevel("level.xml");
		m_pOM->AddObject(pLevel);
	}

	if(m_cPlayer == nullptr)
	{
		m_cPlayer = (Player*)m_pOF->CreateObject( _T("Player"));
		pPlayer = (m_cPlayer);
		pPlayer->SetHeight(32);
		pPlayer->SetWidth(32);
		pPlayer->SetImageID(-1);
		pPlayer->SetPosX(600);
		pPlayer->SetPosY(500);

		
		Weapon* pWeapon2 = nullptr;
		Weapon* pWeapon3 = nullptr;

		pWeapon = (Weapon*)m_pOF->CreateObject( _T("Weapon"));
		pWeapon->SetHeight(20);
		pWeapon->SetWidth(10);
		pWeapon->SetImageID(-1);
		pWeapon->SetOwner(pPlayer);
		pWeapon->Init(WPN_PISTOL, 100, 0);
		pWeapon->SetPosX(pPlayer->GetPosX()+pPlayer->GetWidth()/2);
		pWeapon->SetPosY(pPlayer->GetPosY());

		pWeapon2 = (Weapon*)m_pOF->CreateObject( _T("Weapon"));
		pWeapon2->SetHeight(20);
		pWeapon2->SetWidth(10);
		pWeapon2->SetImageID(-1);
		pWeapon2->SetOwner(pPlayer);
		pWeapon2->Init(WPN_SHOTGUN, 100, 0);
		pWeapon2->SetPosX(pPlayer->GetPosX()+pPlayer->GetWidth()/2);
		pWeapon2->SetPosY(pPlayer->GetPosY());

		pWeapon3 = (Weapon*)m_pOF->CreateObject( _T("Weapon"));
		pWeapon3->SetHeight(20);
		pWeapon3->SetWidth(10);
		pWeapon3->SetImageID(-1);
		pWeapon3->SetOwner(pPlayer);
		pWeapon3->Init(WPN_RIFLE, 100, 0);
		pWeapon3->SetPosX(pPlayer->GetPosX()+pPlayer->GetWidth()/2);
		pWeapon3->SetPosY(pPlayer->GetPosY());

		pPlayer->SetAnimation(m_pVM->RegisterAnimation("resource/graphics/PlayerAnimations.xml"));

		pPlayer->AddWeapon(pWeapon2);
		pPlayer->AddWeapon(pWeapon3);
		pPlayer->AddWeapon(pWeapon);

	}
	else
	{
		pPlayer = (m_cPlayer);
		pPlayer->SetHeight(32);
		pPlayer->SetWidth(32);
		pPlayer->SetImageID(-1);
		pPlayer->SetPosX(m_cPlayer->GetPosX());
		pPlayer->SetHealth(100);
		pPlayer->SetPosY(m_cPlayer->GetPosY());

		for(unsigned int i = 0; i < m_cPlayer->GetWeapons().size(); i++)
		{
			pWeapon = m_cPlayer->GetWeapons()[i];
			m_cPlayer->GetWeapons()[i] = (Weapon*)m_pOF->CreateObject( _T("Weapon") );
			m_cPlayer->GetWeapons()[i]->Init(pWeapon->GetWeaponType(), pWeapon->GetAmmo(), 0);
			m_cPlayer->GetWeapons()[i]->SetPosX(pPlayer->GetPosX()+(pPlayer->GetWidth()/2));
			m_cPlayer->GetWeapons()[i]->SetPosY(pPlayer->GetPosY());
			m_cPlayer->GetWeapons()[i]->SetOwner(pWeapon->GetOwner());
			m_cPlayer->GetWeapons()[i]->SetHeight(pWeapon->GetHeight());
			m_cPlayer->GetWeapons()[i]->SetWidth(pWeapon->GetWidth());
		}
	}
	
	m_pVM->SetAmbientLight( .0f, .0f, .0f);


	vector<leveldata> tmp = pLevel->GetCollision();
	for(unsigned int i = 0; i < tmp.size(); i++) 
	{
		vector<leveldata>::iterator nth = tmp.begin() + i;

		if( _stricmp(nth->m_cType,"Bush") == 0 )
		{
			m_cBushes.push_back(nullptr);
			m_cBushes[m_cBushes.size()-1] = (Bush*)m_pOF->CreateObject( _T("Bush") );
			pBush = m_cBushes[m_cBushes.size()-1];
			pBush->SetPosX((float)nth->x);
			pBush->SetPosY((float)nth->y);
			pBush->SetWidth(nth->width);
			pBush->SetHeight(nth->height);
			pBush->SetImageID(bush);
			m_pOM->AddObject(pBush);
			pBush = nullptr;
			tmp.erase(nth);
			i--;
		}
		else if( _stricmp(nth->m_cType,"Shotgun Ammo") == 0)
		{
			pPickUp = (PickUp*)m_pOF->CreateObject( _T("PickUp"));
			pPickUp->SetPosX((float)nth->x);
			pPickUp->SetPosY((float)nth->y);
			pPickUp->SetWidth(nth->width);
			pPickUp->SetHeight(nth->height);
			pPickUp->SetImageID(-1);
			pPickUp->SetPickUpType(SHOTGUN_AMMO);
			m_pOM->AddObject(pPickUp);
			pPickUp = nullptr;
			tmp.erase(nth);
			i--;
		}
		else if( _stricmp(nth->m_cType,"Rifle Ammo") == 0)
		{
			pPickUp = (PickUp*)m_pOF->CreateObject( _T("PickUp"));
			pPickUp->SetPosX((float)nth->x);
			pPickUp->SetPosY((float)nth->y);
			pPickUp->SetWidth(nth->width);
			pPickUp->SetHeight(nth->height);
			pPickUp->SetImageID(-1);
			pPickUp->SetPickUpType(RIFLE_AMMO);
			m_pOM->AddObject(pPickUp);
			pPickUp = nullptr;
			tmp.erase(nth);
			i--;
		}
		else if( _stricmp(nth->m_cType,"Pistol Ammo") == 0)
		{
			pPickUp = (PickUp*)m_pOF->CreateObject( _T("PickUp"));
			pPickUp->SetPosX((float)nth->x);
			pPickUp->SetPosY((float)nth->y);
			pPickUp->SetWidth(nth->width);
			pPickUp->SetHeight(nth->height);
			pPickUp->SetImageID(-1);
			pPickUp->SetPickUpType(PISTOL_AMMO);
			m_pOM->AddObject(pPickUp);
			pPickUp = nullptr;
			tmp.erase(nth);
			i--;
		}
		else if( _stricmp(nth->m_cType,"Medicine") == 0)
		{
			pPickUp = (PickUp*)m_pOF->CreateObject( _T("PickUp"));
			pPickUp->SetPosX((float)nth->x);
			pPickUp->SetPosY((float)nth->y);
			pPickUp->SetWidth(nth->width);
			pPickUp->SetHeight(nth->height);
			pPickUp->SetImageID(-1);
			pPickUp->SetPickUpType(MEDICINE);
			m_pOM->AddObject(pPickUp);
			pPickUp = nullptr;
			tmp.erase(nth);
			i--;
		}
		else if( _stricmp(nth->m_cType,"Health") == 0)
		{
			pPickUp = (PickUp*)m_pOF->CreateObject( _T("PickUp"));
			pPickUp->SetPosX((float)nth->x);
			pPickUp->SetPosY((float)nth->y);
			pPickUp->SetWidth(nth->width);
			pPickUp->SetHeight(nth->height);
			pPickUp->SetImageID(-1);
			pPickUp->SetPickUpType(HEALTH);
			m_pOM->AddObject(pPickUp);
			pPickUp = nullptr;
			tmp.erase(nth);
			i--;
		}
		else if( _stricmp(nth->m_cType,"Battery") == 0)
		{
			pPickUp = (PickUp*)m_pOF->CreateObject( _T("PickUp"));
			pPickUp->SetPosX((float)nth->x);
			pPickUp->SetPosY((float)nth->y);
			pPickUp->SetWidth(nth->width);
			pPickUp->SetHeight(nth->height);
			pPickUp->SetImageID(-1);
			pPickUp->SetPickUpType(BATTERY);
			m_pOM->AddObject(pPickUp);
			pPickUp = nullptr;
			tmp.erase(nth);
			i--;
		}
		else if( _stricmp(nth->m_cType,"Shooting Enemy") == 0)
		{
			m_cEnemies.push_back(nullptr);
			m_cEnemies[m_cEnemies.size()-1] = (ShootingAi*)m_pOF->CreateObject( _T("ShootingAi") );
			ShootingAi* pEnemy = (ShootingAi*)(m_cEnemies[m_cEnemies.size()-1]);
			pEnemy->SetHeight( nth->height);
			pEnemy->SetWidth( nth->width);
			pEnemy->SetImageID(-1);
			pEnemy->SetTarget(m_cPlayer);
			pEnemy->SetPosX((float)nth->x);
			pEnemy->SetPosY((float)nth->y);
			pEnemy->SetHealth(100);
			pEnemy->SetAnimation(m_pVM->RegisterAnimation("resource/graphics/EnemiesShoot.xml"));
			m_pOM->AddObject(pEnemy);

			Weapon* eWeapon = (Weapon*)m_pOF->CreateObject( _T("Weapon"));
			eWeapon->SetHeight(20);
			eWeapon->SetWidth(10);
			eWeapon->SetImageID(-1);
			eWeapon->SetOwner(pEnemy);
			eWeapon->Init(WPN_PISTOL, 100, 0);
			eWeapon->SetPosX(pEnemy->GetPosX()+pEnemy->GetWidth()/2);
			eWeapon->SetPosY(pEnemy->GetPosY());
			pEnemy->SetWeapon(eWeapon);
			tmp.erase(nth);
			i--;
		}
		else if( _stricmp(nth->m_cType,"NPC") == 0)
		{
			m_cNpcs.push_back(nullptr);
			m_cNpcs[m_cNpcs.size()-1] = (NPC*)m_pOF->CreateObject( _T("NPC") );
			NPC* pNpc =(NPC*)(m_cNpcs[m_cNpcs.size()-1]);
			pNpc->SetHeight(32);
			pNpc->SetWidth(32);
			pNpc->SetImageID(-1);
			pNpc->SetPosX((float)nth->x);
			pNpc->SetPosY((float)nth->y);
			pNpc->SetQuest(m_cNpcs.size());
			pNpc->SetLabel(m_cNpcs.size()-1);
			pNpc->SetAnimation(m_pVM->RegisterAnimation("resource/graphics/Npc.xml"));
			m_pOM->AddObject(pNpc);
			pNpc = nullptr;
			tmp.erase(nth);
			i--;
		}
		else if ( _stricmp(nth->m_cType,"Spawn Point") == 0 )
		{
			m_cSpawn.push_back(nullptr);
			m_cSpawn[m_cSpawn.size()-1] = (SpawnPoint*)m_pOF->CreateObject( _T("SpawnPoint") );
			pSpawn = m_cSpawn[m_cSpawn.size()-1];
			pSpawn->SetPosX( (float)nth->x );
			pSpawn->SetPosY( (float)nth->y );
			pSpawn->SetHeight( nth->height );
			pSpawn->SetWidth( nth->width );
			pSpawn->SetImageID( -1 );
			//m_pOM->AddObject(pSpawn);
			pSpawn = nullptr;
			tmp.erase(nth);
			i--;
			for( int i = 0; i < 1; i++)
			{
				m_cEnemies.push_back(nullptr);
				m_cEnemies[m_cEnemies.size()-1] = (ChasingAI*)GamePlayState::GetInstance()->m_pOF->CreateObject( _T("ChasingAI") );
				ChasingAI* pEnemy = (ChasingAI*)(m_cEnemies[m_cEnemies.size()-1]);
				pEnemy->SetHeight(m_cSpawn[m_cSpawn.size()-1]->GetHeight());
				pEnemy->SetWidth(m_cSpawn[m_cSpawn.size()-1]->GetWidth());
				pEnemy->SetImageID(-1);
				pEnemy->SetTarget(GetPlayer());
				pEnemy->SetPosX((float)m_cSpawn[m_cSpawn.size()-1]->GetPosX()/*+(rand()%20-10)*/);
				pEnemy->SetPosY((float)m_cSpawn[m_cSpawn.size()-1]->GetPosY()/*+(rand()%20-10)*/);
				pEnemy->SetHealth(100);
				pEnemy->SetAnimation(SpawnEnemyAniID);
				GamePlayState::GetInstance()->m_pOM->AddObject(pEnemy);
				m_cSpawn[m_cSpawn.size()-1]->SetSpawn( false );
			}
		}
	}
	pLevel->SetCollision(tmp);


	vector<mapTiles> tmpTiles = pLevel->GetTiles();
	for(unsigned int i = 0; i < tmpTiles.size(); i++) 
	{
		for(unsigned int x = i+1; x < tmpTiles.size(); x++) 
		{
			if( tmpTiles[x].m_Layer < tmpTiles[i].m_Layer )
			{
				swap(tmpTiles[i],tmpTiles[x]);
			}
		}
	}

	m_cBuddy = (CompanionAI*)m_pOF->CreateObject( _T("CompanionAI") );
	CompanionAI* pBuddy = (CompanionAI*)(m_cBuddy);
	pBuddy->SetPosX(550);
	pBuddy->SetPosY(550);
	pBuddy->SetHeight(32);
	pBuddy->SetWidth(32);
	pBuddy->SetImageID(-1);
	m_pOM->AddObject(pBuddy);


	//for(int i = 0; i < 1; i++)
	//{
	//	m_cEnemies.push_back(nullptr);
	//	m_cEnemies[i] = (ChasingAI*)m_pOF->CreateObject( _T("ChasingAI") );
	//	ChasingAI* pEnemy = (ChasingAI*)(m_cEnemies[i]);
	//	pEnemy->SetHeight(32);
	//	pEnemy->SetWidth(32);
	//	pEnemy->SetImageID(-1);
	//	pEnemy->SetTarget(m_cPlayer);
	//	pEnemy->SetPosX(float(50+200));
	//	pEnemy->SetPosY(200);
	//	pEnemy->SetHealth(100);
	//	m_pOM->AddObject(pEnemy);
	//}

	/*for(int i = 0; i < 1; i++)
	{
		m_cEnemies.push_back(nullptr);
		m_cEnemies[i] = (ShootingAi*)m_pOF->CreateObject( _T("ShootingAi") );
		ShootingAi* pEnemy = (ShootingAi*)(m_cEnemies[i]);
		pEnemy->SetHeight(32);
		pEnemy->SetWidth(32);
		pEnemy->SetImageID(-1);
		pEnemy->SetTarget(m_cPlayer);
		pEnemy->SetPosX(700);
		pEnemy->SetPosY(500);
		pEnemy->SetHealth(100);
		pEnemy->SetAnimation(m_pVM->RegisterAnimation("resource/graphics/EnemiesShoot.xml"));
		m_pOM->AddObject(pEnemy);

		Weapon* eWeapon = (Weapon*)m_pOF->CreateObject( _T("Weapon"));
		eWeapon->SetHeight(20);
		eWeapon->SetWidth(10);
		eWeapon->SetImageID(-1);
		eWeapon->SetOwner(pEnemy);
		eWeapon->Init(WPN_RIFLE, 100, 0);
		eWeapon->SetPosX(pEnemy->GetPosX()+pEnemy->GetWidth()/2);
		eWeapon->SetPosY(pEnemy->GetPosY());
		pEnemy->SetWeapon(eWeapon);
	}*/

	//for(int i = 0; i < 1; i++)
	//{
	//	m_cNpcs.push_back(nullptr);
	//	m_cNpcs[i] = (NPC*)m_pOF->CreateObject( _T("NPC") );
	//	NPC* pNpc =(NPC*)(m_cNpcs[i]);
	//	pNpc->SetHeight(32);
	//	pNpc->SetWidth(32);
	//	pNpc->SetImageID(-1);
	//	pNpc->SetPosX(400);
	//	pNpc->SetPosY(100);
	//	pNpc->SetQuest(i+1);
	//	pNpc->SetLabel(i);
	//	m_pOM->AddObject(pNpc);

	//}

	m_pOM->AddObject(pPlayer);

	m_pMS->InitMessageSystem( &MessageProc );

	backGroundID = m_pAM->registerMusic("resource/Sounds/background.mp3");

	swingHitID = m_pAM->RegisterSound("resource/Sounds/swingHit.mp3");
	FMOD_VECTOR sound1 = { 0, 0, 0 };

	m_pAM->setMusicPos(backGroundID, sound1);
	m_pAM->setMusicVel(backGroundID, sound1);
	m_pAM->setMusicLooping(backGroundID, true);
	m_pAM->playMusic(backGroundID);

	soundID2 = m_pAM->RegisterSound("resource/Sounds/thunder.wav");
	m_pAM->setSoundPos(soundID2, sound1);

	m_pAM->setSoundVel(soundID2, sound1);
	m_pAM->setSoundLooping(soundID2, false);

	musicID = m_pAM->registerMusic("resource/Sounds/rainroof.wav");
	m_pAM->setMusicPos(musicID, sound1);

	m_pAM->setMusicVel(musicID, sound1);
	m_pAM->setMusicLooping(musicID, true);
	m_pAM->playMusic(musicID);
	winLose = true;

	m_pHUD = new HUD;
	m_pHUD->m_nHudID = m_pVM->RegisterTexture("resource//graphics//sprites_HUD.png");
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_01.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_02.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_03.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_04.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_05.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_06.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_07.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_08.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_09.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_10.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_11.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_12.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_13.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_14.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_15.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_16.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_17.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_18.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_19.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_20.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_21.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_22.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_23.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_24.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_25.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_26.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_27.png.png"));
	m_pHUD->m_vFrameIDs.push_back( m_pVM->RegisterTexture("resource//graphics//health_animation//health_anm_28.png.png"));

	// Example of how to set up a light
	//Light tmpLight;
	//tmpLight.lightPos[0] = 0.0f;
	//tmpLight.lightPos[1] = 0.0f;
	//tmpLight.lightPos[2] = -1.0f;
	//tmpLight.lightDir[0] = 0.0f;
	//tmpLight.lightDir[1] = 0.0f;
	//tmpLight.lightDir[2] = 1.0f;
	//tmpLight.color[0] = 1;
	//tmpLight.color[1] = 1;
	//tmpLight.color[2] = 1;
	//ViewManager::GetInstance()->RegisterLight(tmpLight);
}

void GamePlayState::ReEnter()
{
	m_pAM->playMusic(backGroundID);
	m_pAM->playMusic(musicID);
}

void GamePlayState::Exit() 
{
	m_pVM->SetAmbientLight( 1.0f, 1.0f, 1.0f);

	if( m_pES != nullptr )
	{
		m_pES->ClearEvents();
		m_pES->Shutdown();
		m_pES = nullptr;
	}

	if( m_pMS != nullptr )
	{
		m_pMS->ClearMessages();
		m_pMS->Shutdown();
		m_pMS = nullptr;
	}

	if( m_pOM != nullptr )
	{
		m_pOM->RemoveAllObjects();
		ObjectManager::DeleteInstance();
		m_pOM = nullptr;
	}

	if( m_pOF != nullptr )
	{
		m_pOF->ShutdownObjectFactory();
		m_pOF = nullptr;
	}

	for(unsigned int i = 0; i < m_cEnemies.size(); i++)
	{
		m_cEnemies[i] = nullptr;
	}
	m_cEnemies.clear();

	for(unsigned int i = 0; i < m_cNpcs.size(); i++)
	{
		m_cNpcs[i] = nullptr;
	}
	m_cNpcs.clear();

	m_pVM = nullptr;
	m_pDI = nullptr;
	m_pAM = nullptr;
	m_pOF = nullptr;
	m_pOM = nullptr;
	m_pES = nullptr;

	m_cPlayer = nullptr;
}

bool GamePlayState::Input() 
{
	if( m_pDI->KeyPressed(DIK_ESCAPE) || m_pDI->JoystickButtonPressed(7,0) )

		CGame::GetInstance()->ChangeState(PauseMenuState::GetInstance());

	return true;
}

void GamePlayState::Update(float fElapsedTime) 
{
	//m_clevel.Update(fElapsedTime);
	m_pVM->SetAmbientLight( .0f, .0f, .0f);


	m_pOM->UpdateAllObjects(fElapsedTime);
	m_pOM->CheckCollisions();
	if(m_cPlayer->IsOn() && m_cPlayer->GetLightType() < 2)
		m_pOM->CheckTriangleCollisions();
	camera.x = float(m_cPlayer->GetPosX() - (CGame::GetInstance()->GetScreenWidth()*0.5));
	camera.y = float(m_cPlayer->GetPosY() - (CGame::GetInstance()->GetScreenHeight()*0.5));
	FMOD_VECTOR tmp;
	tmp.x = m_cPlayer->GetPosX();
	tmp.y = m_cPlayer->GetPosY();
	tmp.z = 0;
	m_pAM->SetListenerPos(tmp);
	m_pAM->setSoundPos(soundID2,tmp);
	m_pES->ProcessEvents();
	m_pMS->ProcessMessages();
	RECT chocolateRain = { (long)camera.x, (long)camera.y, (long)camera.x + CGame::GetInstance()->GetScreenWidth(), (long)camera.y + CGame::GetInstance()->GetScreenHeight()};
	m_pPM->GetActiveEmitter(rainA)->SetRect(chocolateRain);

	bool check = false;
	for( unsigned int i = 0; i < m_cBushes.size(); i++)
	{
		m_cBushes[i]->Update(fElapsedTime);
		if( m_cBushes[i]->CheckCollision(GetPlayer() ) == true )
		{
			m_cBushes[i]->SetIsInBush( true );
			check = true;
		}
		else
		{
			m_cBushes[i]->SetIsInBush( false );
		}
	}

	if( check == true )
	{
		GetPlayer()->m_bIsHidden = true; 
	}
	else
	{
		GetPlayer()->m_bIsHidden = false; 
	}


	for( unsigned int i = 0; i < m_cSpawn.size(); i++)
	{
		m_cSpawn[i]->Update(fElapsedTime);
		if(m_cSpawn[i]->CanSpawn() == true)
		{
			m_cEnemies.push_back(nullptr);
			m_cEnemies[m_cEnemies.size()-1] = (ChasingAI*)GamePlayState::GetInstance()->m_pOF->CreateObject( _T("ChasingAI") );
			ChasingAI* pEnemy = (ChasingAI*)(m_cEnemies[m_cEnemies.size()-1]);
			pEnemy->SetHeight(m_cSpawn[i]->GetHeight());
			pEnemy->SetWidth(m_cSpawn[i]->GetWidth());
			pEnemy->SetImageID(-1);
			pEnemy->SetTarget(GetPlayer());
			pEnemy->SetPosX(m_cSpawn[i]->GetPosX()+(rand()%20-10));
			pEnemy->SetPosY(m_cSpawn[i]->GetPosY()+(rand()%20-10));
			pEnemy->SetHealth(100);
			pEnemy->SetAnimation(SpawnEnemyAniID);
			GamePlayState::GetInstance()->m_pOM->AddObject(pEnemy);
			m_cSpawn[i]->SetSpawn( false );
		}
	}
	//m_pHUD->Input();
	m_pHUD->Update(fElapsedTime);
	m_pPM->Update(fElapsedTime);
	//// Quest 2 completion
	if(GetPlayer()->questCounter == 10 )
	{
		questFlag = true;
		if(m_pDI->KeyPressed(DIK_RETURN) || m_pDI->JoystickButtonPressed(1,0))

		{
			for(unsigned int i = 0; i < GetPlayer()->m_vpActiveQuests.size(); i++)
			{
				GetPlayer()->completedQuest++;
				GetPlayer()->m_vpFinishedQuests.push_back(GetPlayer()->m_vpActiveQuests[i]);
				GetPlayer()->m_vpActiveQuests.pop_back();
			}
			questFlag = false;
		}
	}
	// Total quest completion to win the game
	if(GetPlayer()->m_vpFinishedQuests.size() == 10)
	{
		questFlag = false;
		CGame::GetInstance()->ChangeState(WinMenuState::GetInstance());
	}

	// Auto Lose
	if(m_pDI->KeyPressed(DIK_G) && winLose == true )
	{
		winLose = false;
	}
}

void GamePlayState::Render() 
{
	m_pVM->GetSprite()->Flush();
	//m_clevel.Render();

	m_pOM->RenderAllObjects();

	for( unsigned int i = 0; i < m_cBushes.size(); i++)
	{
		float x, y;
		int z;
		x = m_cBushes[i]->GetPosX();
		y = m_cBushes[i]->GetPosY();
		z = m_cBushes[i]->GetImageID();
		RECT tmp = {0,0,64,64};
		if(m_cBushes[i]->GetShadow() && m_cPlayer->IsOn())
		{
			if(m_cPlayer->GetDirection() < 4)
				m_pVM->DrawStaticTexture(z,x-GetCamera().x,y-GetCamera().y-15,1.0f,1.25f,&tmp,32,64, (m_cPlayer->GetDirection() - 1) * 1.57079f,D3DCOLOR_ARGB(200,0,0,0));
			else
			{
				switch(m_cPlayer->GetDirection())
				{
				case 4:
					m_pVM->DrawStaticTexture(z,x-GetCamera().x,y-GetCamera().y-15,1.0f,1.25f,&tmp,32,64, -0.78539f,D3DCOLOR_ARGB(200,0,0,0));
					break;
				case 5:
					m_pVM->DrawStaticTexture(z,x-GetCamera().x,y-GetCamera().y-15,1.0f,1.25f,&tmp,32,64, 0.78539f,D3DCOLOR_ARGB(200,0,0,0));
					break;
				case 6:
					m_pVM->DrawStaticTexture(z,x-GetCamera().x,y-GetCamera().y-15,1.0f,1.25f,&tmp,32,64, -2.35619f,D3DCOLOR_ARGB(200,0,0,0));
					break;
				case 7:
					m_pVM->DrawStaticTexture(z,x-GetCamera().x,y-GetCamera().y-15,1.0f,1.25f,&tmp,32,64, 2.35619f,D3DCOLOR_ARGB(200,0,0,0));
					break;
				default:
					break;
				}
			}
		}
		else if( m_cPlayer->IsOn() && m_cPlayer->GetLightType() > 1)
		{
			float angle = 0;
			if( m_cBushes[i]->GetPosY() > m_cPlayer->GetPosY() && m_cBushes[i]->GetPosX() > m_cPlayer->GetPosX())
				angle = 0.78539f;
			else if( m_cBushes[i]->GetPosY() < m_cPlayer->GetPosY() && m_cBushes[i]->GetPosX() > m_cPlayer->GetPosX())
				angle = -0.78539f;
			else if( m_cBushes[i]->GetPosY() > m_cPlayer->GetPosY() && m_cBushes[i]->GetPosX() < m_cPlayer->GetPosX())
				angle = -2.35619f;
			else if( m_cBushes[i]->GetPosY() < m_cPlayer->GetPosY() && m_cBushes[i]->GetPosX() < m_cPlayer->GetPosX())
				angle = 2.35619f;
			else if(m_cBushes[i]->GetPosY() < m_cPlayer->GetPosY() && m_cBushes[i]->GetPosX() == m_cPlayer->GetPosX())
				angle = 0.0f;
			else if(m_cBushes[i]->GetPosY() > m_cPlayer->GetPosY() && m_cBushes[i]->GetPosX() == m_cPlayer->GetPosX())
				angle = 3.14159f;
			else if(m_cBushes[i]->GetPosY() == m_cPlayer->GetPosY() && m_cBushes[i]->GetPosX() < m_cPlayer->GetPosX())
				angle = -1.57079f;
			else if(m_cBushes[i]->GetPosY() == m_cPlayer->GetPosY() && m_cBushes[i]->GetPosX() > m_cPlayer->GetPosX())
				angle = 1.57079f;

			m_pVM->DrawStaticTexture(z,x-GetCamera().x,y-GetCamera().y - 15,1.0f,1.25f,&tmp,32,64, angle,D3DCOLOR_ARGB(200,0,0,0));
		
		}
		m_cBushes[i]->Render();
	}
	m_pPM->Render();
	
	//m_pVM->DrawFont(GetPlayer()->m_nFontID,"Quest Log",610.0f,100.0f,0.5f,0.5f);


	//char szName[100] = {};
	//
	//TCHAR buffer[ 100 ];
	////int playerScore = 15;
	//_stprintf_s( buffer, 100, _T("Health = %i"), m_pHUD->m_fHealth );

	//wcstombs_s( nullptr, szName, 100, buffer, _TRUNCATE );
	//m_pVM->DrawTextW("hello",GamePlayState::GetInstance()->GetCamera().x,GamePlayState::GetInstance()->GetCamera().y,255,255,255);

	////m_pVM->DrawText(szName,0,0,255,255,255);
	//m_pVM->DrawFont(this->m_cNpcs[0]->temp_font_id,szName,0,0);

	////char szName1[100] = {};
	////
	////TCHAR buffer1[ 100 ];
	////int playerScore = 15;
	//_stprintf_s( buffer, 100, _T("Lives = %i"), m_pHUD->m_nLives );

	//wcstombs_s( nullptr, szName, 100, buffer, _TRUNCATE );

	//m_pVM->DrawFont(this->m_cNpcs[0]->temp_font_id,szName,0,20);




	

}

void GamePlayState::MessageProc(IMessage* pMsg)
{
	GamePlayState* self = GamePlayState::GetInstance();
	switch( pMsg->GetMessageID() )
	{
	case MSG_CREATE_BULLET:
		{
			// Create bullet
			Bullet* bullet = (Bullet*)( self->m_pOF->CreateObject( _T("Bullet") ) );
			Weapon* pOwner = dynamic_cast< CreateBullet* > (pMsg)->GetWeapon();
			//Set up data members
			bullet->SetImageID( -1 );
			bullet->SetHeight(16);
			bullet->SetWidth(16);
			bullet->SetOwner(pOwner);
			bullet->SetPosX(pOwner->GetPosX());
			bullet->SetPosY(pOwner->GetPosY());
			bullet->SetStartPos(pOwner->GetPosX(), pOwner->GetPosY());

			// Smoke effects
			RECT temp = {(long)pOwner->GetPosX(),(long)pOwner->GetPosY(),(long)pOwner->GetPosX() + (long)16.0f,(long)16.0f + (long)pOwner->GetPosY()};
			
			bullet->SetSmokeID(Particle_Manager::GetInstance()->ActivateEmitter(self->smokeL));

			self->m_pPM->GetActiveEmitter(bullet->GetSmokeID())->SetRect(temp);
			self->m_pPM->GetActiveEmitter(bullet->GetSmokeID())->SetLoopin(false);

			if( pOwner->GetWeaponType() == WPN_SHOTGUN )
			{
				Bullet* bullet2 = (Bullet*)( self->m_pOF->CreateObject( _T("Bullet") ) );
				Bullet* bullet3 = (Bullet*)( self->m_pOF->CreateObject( _T("Bullet") ) );
				//bullet 2
				bullet2->SetImageID( -1 );
				bullet2->SetHeight(16);
				bullet2->SetWidth(16);
				bullet2->SetOwner(pOwner);
				bullet2->SetPosX(pOwner->GetPosX());
				bullet2->SetPosY(pOwner->GetPosY());
				bullet2->SetStartPos(pOwner->GetPosX(), pOwner->GetPosY());
				//bullet 3
				bullet3->SetImageID( -1 );
				bullet3->SetHeight(16);
				bullet3->SetWidth(16);
				bullet3->SetOwner(pOwner);
				bullet3->SetPosX(pOwner->GetPosX());
				bullet3->SetPosY(pOwner->GetPosY());
				bullet3->SetStartPos(pOwner->GetPosX(), pOwner->GetPosY());

				switch(pOwner->GetOwner()->GetDirection())
				{
				case DIRE_UP:
					{
						bullet->SetSpeedX(0);
						bullet->SetSpeedY(-300);
						bullet2->SetSpeedX(50);
						bullet2->SetSpeedY(-300);
						bullet3->SetSpeedX(-50);
						bullet3->SetSpeedY(-300);
						break;
					}
				case DIRE_LEFT:
					{
						bullet->SetSpeedX(-300);
						bullet->SetSpeedY(0);
						bullet2->SetSpeedX(-300);
						bullet2->SetSpeedY(50);
						bullet3->SetSpeedX(-300);
						bullet3->SetSpeedY(-50);
						break;
					}
				case DIRE_RIGHT:
					{
						bullet->SetSpeedX(300);
						bullet->SetSpeedY(0);
						bullet2->SetSpeedX(300);
						bullet2->SetSpeedY(50);
						bullet3->SetSpeedX(300);
						bullet3->SetSpeedY(-50);
						break;
					}
				case DIRE_DOWN:
					{
						bullet->SetSpeedX(0);
						bullet->SetSpeedY(300);
						bullet2->SetSpeedX(50);
						bullet2->SetSpeedY(300);
						bullet3->SetSpeedX(-50);
						bullet3->SetSpeedY(300);
						break;
					}
				case DIRE_UPRIGHT:
					{
						bullet->SetSpeedX(300);
						bullet->SetSpeedY(-300);
						bullet2->SetSpeedX(270);
						bullet2->SetSpeedY(-300);
						bullet3->SetSpeedX(300);
						bullet3->SetSpeedY(-270);
						break;
					}
				case DIRE_UPLEFT:
					{
						bullet->SetSpeedX(-300);
						bullet->SetSpeedY(-300);
						bullet2->SetSpeedX(-270);
						bullet2->SetSpeedY(-300);
						bullet3->SetSpeedX(-300);
						bullet3->SetSpeedY(-270);
						break;
					}
				case DIRE_DOWNLEFT:
					{
						bullet->SetSpeedX(-300);
						bullet->SetSpeedY(300);
						bullet2->SetSpeedX(-270);
						bullet2->SetSpeedY(300);
						bullet3->SetSpeedX(-300);
						bullet3->SetSpeedY(270);
						break;
					}
				case DIRE_DOWNRIGHT:
					{
						bullet->SetSpeedX(300);
						bullet->SetSpeedY(300);
						bullet2->SetSpeedX(270);
						bullet2->SetSpeedY(300);
						bullet3->SetSpeedX(300);
						bullet3->SetSpeedY(270);
						break;
					}
				}
				self->m_pOM->AddObject( bullet );
				self->m_pOM->AddObject( bullet2 );
				self->m_pOM->AddObject( bullet3 );
				bullet->Release();
				bullet2->Release();
				bullet3->Release();
				bullet = nullptr;
				bullet2 = nullptr;
				bullet3 = nullptr;
			}
			else
			{
				switch(pOwner->GetOwner()->GetDirection())
				{
				case DIRE_UP:
					{
						bullet->SetSpeedX(0);
						bullet->SetSpeedY(-300);
						break;
					}
				case DIRE_LEFT:
					{
						bullet->SetSpeedX(-300);
						bullet->SetSpeedY(0);
						break;
					}
				case DIRE_RIGHT:
					{
						bullet->SetSpeedX(300);
						bullet->SetSpeedY(0);
						break;
					}
				case DIRE_DOWN:
					{
						bullet->SetSpeedX(0);
						bullet->SetSpeedY(300);
						break;
					}
				case DIRE_UPRIGHT:
					{
						bullet->SetSpeedX(300);
						bullet->SetSpeedY(-300);
						break;
					}
				case DIRE_UPLEFT:
					{
						bullet->SetSpeedX(-300);
						bullet->SetSpeedY(-300);
						break;
					}
				case DIRE_DOWNLEFT:
					{
						bullet->SetSpeedX(-300);
						bullet->SetSpeedY(300);
						break;
					}
				case DIRE_DOWNRIGHT:
					{
						bullet->SetSpeedX(300);
						bullet->SetSpeedY(300);
						break;
					}
				}
				self->m_pOM->AddObject( bullet );
				bullet->Release();
				bullet = nullptr;
			}

			// Add bullet to object manager


			break;
		}
	case MSG_CREATE_ENEMYC:
		{
			// Create ChasingAI
			ChasingAI* enemyc = dynamic_cast< ChasingAI* >( self->m_pOF->CreateObject( _T("ChasingAI") ) );
			//Set up data members
			//enemyc->SetImageID( );
			//enemyc->SetHealth( );
			//enemyc->SetHeight( );
			//enemyc->SetWidth( );
			//enemyc->SetPosX( );
			//enemyc->SetPosY( );
			//enemyc->SetVelX( );
			//enemyc->SetVelY( );

			// Add enemyc to object manager
			self->m_pOM->AddObject(enemyc);
			enemyc->Release();
			enemyc = nullptr;
			break;
		}
	case MSG_CREATE_ENEMYS:
		{
			// Create ShootingAI
			ShootingAi* enemys = dynamic_cast< ShootingAi* >( self->m_pOF->CreateObject( _T("ShootingAi") ) );
			//Set up data members			
			//enemys->SetImageID( );
			//enemys->SetHealth( );
			//enemys->SetHeight( );
			//enemys->SetWidth( );
			//enemys->SetPosX( );
			//enemys->SetPosY( );
			//enemys->SetVelX( );
			//enemys->SetVelY( );

			// Add enemys to object manager
			self->m_pOM->AddObject(enemys);
			enemys->Release();
			enemys = nullptr;
			break;
		}
	case MSG_CREATE_NPC:
		{
			// Create NPC
			NPC* npc = dynamic_cast< NPC* >( self->m_pOF->CreateObject( _T("NPC") ) );
			//Set up data members			
			//npc->SetImageID( );
			//npc->SetHealth( );
			//npc->SetHeight( );
			//npc->SetWidth( );
			//npc->SetPosX( );
			//npc->SetPosY( );
			//npc->SetVelX( );
			//npc->SetVelY( );

			// Add npc to object manager
			self->m_pOM->AddObject(npc);
			npc->Release();
			npc = nullptr;
			break;
		}
	case MSG__CREATE_PICKUP:
		{
			// Create PickUp
			PickUp* pickup = dynamic_cast< PickUp* >( self->m_pOF->CreateObject( _T("PickUp") ) );
			//Set up data members
			//pickup->SetHeight( );
			//pickup->SetImageID( );
			//pickup->SetPosX( );
			//pickup->SetPosY( );
			//pickup->SetWidth( );

			// Add pickup to object manager
			self->m_pOM->AddObject(pickup);
			pickup->Release();
			pickup = nullptr;
			break;
		}
	case MSG_DESTROY_BULLET:
		{
			Bullet* bullet = dynamic_cast<DestroyBullet*>(pMsg)->GetBullet();
			self->m_pOM->RemoveObject( bullet );
			break;
		}
	case MSG_DESTROY_ENEMYC:
		{
			ChasingAI* enemyc = dynamic_cast<DestroyEnemyC*>(pMsg)->GetEnemyC();
			for( unsigned int i = 0; i < self->m_cEnemies.size(); i++ )
			{
				if( enemyc == self->m_cEnemies[i] )
				{
					vector<Enemy*>::iterator nth = self->m_cEnemies.begin() + i;
					self->m_cEnemies.erase(nth);
					break;
				}
			}
			for(unsigned int i = 0; i < self->GetPlayer()->m_vpActiveQuests.size();i++)
			{
				if(self->GetPlayer()->m_vpActiveQuests[i]->QuestID == 2)
					self->GetPlayer()->questCounter++;
			}		

			self->m_pOM->RemoveObject( enemyc );
			break;
		}
	case MSG_DESTROY_ENEMYS:
		{
			ShootingAi* enemys = dynamic_cast<DestroyEnemyS*>(pMsg)->GetEnemyS();
			for( unsigned int i = 0; i < self->m_cEnemies.size(); i++ )
			{
				if( enemys == self->m_cEnemies[i] )
				{
					vector<Enemy*>::iterator nth = self->m_cEnemies.begin() + i;
					self->m_cEnemies.erase(nth);
					break;
				}
			}
			self->m_pOM->RemoveObject( enemys );
			break;
		}
	case MSG_DESTROY_NPC:
		{
			NPC* npc = dynamic_cast<DestroyNPC*>(pMsg)->GetNPC();
			self->m_pOM->RemoveObject( npc );
			break;
		}
	case MSG_DESTROY_PICKUP:
		{
			PickUp* pickup = dynamic_cast<DestroyPickUp*>(pMsg)->GetPickUp();
			self->m_pOM->RemoveObject( pickup );
			break;
		}
	}
}