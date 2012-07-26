#include "TutorialState.h"
#include "ViewManager.h"
#include "DirectInput.h"
#include "AudioManager.h"
#include "Particle_Manager.h"
#include "CompanionAI.h"
#include "DestroyBullet.h"
#include "PauseMenuState.h"
#include "Player.h"
#include "HUD.h"
#include "LoadingScreen.h"
#include "Bush.h"
#include "PickUp.h"
#include "Weapon.h"
#include "Level.h"
#include "Emitter.h"
#include "CreateBullet.h"
#include "DestroyEnemyC.h"
#include "ObjectFactory.h"
#include "Message.h"
#include "ObjectManager.h"
#include "GamePlayState.h"
#include "ChasingAI.h"
#include "Bullet.h"
#include "CGame.h"

TutorialState* TutorialState::GetInstance()
{
	static TutorialState s_Instance;

	return &s_Instance;
}

TutorialState::TutorialState(void)
{
	m_pDI = nullptr;
	m_pVM = nullptr;
	m_pAM = nullptr;
	goback = false;
}

void TutorialState::ReEnter()
{

}


TutorialState::~TutorialState(void)
{
}

void TutorialState::Enter()
{
	goback = false;
	LoadingScreen* loading = LoadingScreen::GetInstance();

	m_pDI = DirectInput::GetInstance();
	m_pVM = ViewManager::GetInstance();
	m_pOF = Factory::GetInstance();
	m_pOM = ObjectManager::GetInstance();
	m_pES = EventSystem::GetInstance();
	m_pMS = MessageSystem::GetInstance();
	m_pPM = Particle_Manager::GetInstance();
	m_pAM = AudioManager::GetInstance();

	m_pVM->SetLightPos(0, 0, -1.0f);
	m_pVM->SetSpotLightPos(0, 0, -.85f);
	m_pVM->SetInnerCone(.95f);
	m_pVM->SetOuterCone(.9f);

	loading->Render();

	m_pVM->SetAmbientLight( .1f, .1f, .0f);

	m_pOF->RegisterClassType< Player		>( _T("Player") );
	m_pOF->RegisterClassType< Level			>( _T("Level") );
	m_pOF->RegisterClassType< Weapon		>( _T("Weapon") );
	m_pOF->RegisterClassType< Bush			>( _T("Bush") );
	m_pOF->RegisterClassType< Enemy			>( _T("Enemy") );
	m_pOF->RegisterClassType< CompanionAI	>( _T("CompanionAI") );
	m_pOF->RegisterClassType< ChasingAI		>( _T("ChasingAI") );
	m_pOF->RegisterClassType< Bullet		>( _T("Bullet") );


	loading->Update();
	loading->Render();

	// Smoke particles
	smokeL = m_pPM->LoadEmitter("smoke.xml");

	bloodL1	= m_pPM->LoadEmitter("blood1.xml");
	bloodL2 = m_pPM->LoadEmitter("blood2.xml");
	bloodL3 = m_pPM->LoadEmitter("blood3.xml");
	bloodL4 = m_pPM->LoadEmitter("blood4.xml");
	bloodL5 = m_pPM->LoadEmitter("blood5.xml");
	bloodL6 = m_pPM->LoadEmitter("blood6.xml");
	bloodL7 = m_pPM->LoadEmitter("blood7.xml");
	bloodL8 = m_pPM->LoadEmitter("blood8.xml");
	goreL1 = m_pPM->LoadEmitter("gore1.xml");
	goreL2 = m_pPM->LoadEmitter("gore2.xml");
	goreL3 = m_pPM->LoadEmitter("gore3.xml");
	goreL4 = m_pPM->LoadEmitter("gore4.xml");
	goreL5 = m_pPM->LoadEmitter("gore5.xml");
	goreL6 = m_pPM->LoadEmitter("gore6.xml");
	goreL7 = m_pPM->LoadEmitter("gore7.xml");
	goreL8 = m_pPM->LoadEmitter("gore8.xml");

	loading->Update();
	loading->Render();


	int bush = m_pVM->RegisterTexture("resource//graphics//Bush.png");

	GamePlayState::GetInstance()->SetBloodL1(bloodL1);
	GamePlayState::GetInstance()->SetBloodL2(bloodL2);
	GamePlayState::GetInstance()->SetBloodL3(bloodL3);
	GamePlayState::GetInstance()->SetBloodL4(bloodL4);
	GamePlayState::GetInstance()->SetBloodL5(bloodL5);
	GamePlayState::GetInstance()->SetBloodL6(bloodL6);
	GamePlayState::GetInstance()->SetBloodL7(bloodL7);
	GamePlayState::GetInstance()->SetBloodL8(bloodL8);

	GamePlayState::GetInstance()->SetGoreL1(goreL1);
	GamePlayState::GetInstance()->SetGoreL2(goreL2);
	GamePlayState::GetInstance()->SetGoreL3(goreL3);
	GamePlayState::GetInstance()->SetGoreL4(goreL4);
	GamePlayState::GetInstance()->SetGoreL5(goreL5);
	GamePlayState::GetInstance()->SetGoreL6(goreL6);
	GamePlayState::GetInstance()->SetGoreL7(goreL7);
	GamePlayState::GetInstance()->SetGoreL8(goreL8);

	m_pVM->ClearOtherLights();

	Player* pPlayer = nullptr;
	Level* pLevel = nullptr;	Bush* pBush = nullptr;
	PickUp* pPickUp = nullptr;


	loading->Update();
	loading->Render();


	if( pLevel == nullptr )
	{
		m_clevel = (Level*)m_pOF->CreateObject( _T("Level"));
		pLevel = m_clevel;
		pLevel->LoadLevel("TutorialMap.xml");
		m_pOM->AddObject(pLevel);
	}

	m_cPlayer = (Player*)m_pOF->CreateObject( _T("Player"));
	pPlayer = (m_cPlayer);
	pPlayer->SetHeight(32);
	pPlayer->SetWidth(32);
	pPlayer->SetImageID(-1);
	pPlayer->SetPosX(620);
	pPlayer->SetPosY(500);


	//Weapon* pWeapon2 = nullptr;
	Weapon* pWeapon3 = nullptr;
	Weapon* pWeapon4 = nullptr;

	/*pWeapon = (Weapon*)m_pOF->CreateObject( _T("Weapon"));
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
	*/
	pWeapon4 = (Weapon*)m_pOF->CreateObject( _T("Weapon"));
	pWeapon4->SetHeight(20);
	pWeapon4->SetWidth(10);
	pWeapon4->SetImageID(-1);
	pWeapon4->SetOwner(pPlayer);
	pWeapon4->Init(WPN_MACHETE, 100, 0);
	pWeapon4->SetPosX(pPlayer->GetPosX()+pPlayer->GetWidth()/2);
	pWeapon4->SetPosY(pPlayer->GetPosY());

	pPlayer->SetAnimation(m_pVM->RegisterAnimation("resource/graphics/PlayerAnimations.xml"));

	//pPlayer->AddWeapon(pWeapon2);
	pPlayer->AddWeapon(pWeapon3);
	//pPlayer->AddWeapon(pWeapon);
	pPlayer->AddWeapon(pWeapon4);

	loading->Update();
	loading->Render();


	m_cBuddy = (CompanionAI*)m_pOF->CreateObject( _T("CompanionAI") );
	CompanionAI* pBuddy = (CompanionAI*)(m_cBuddy);
	pBuddy->SetPosX(550);
	pBuddy->SetPosY(500);
	pBuddy->SetHeight(32);
	pBuddy->SetWidth(32);
	pBuddy->SetImageID(-1);
	pBuddy->SetAnimation(m_pVM->RegisterAnimation("resource/graphics/Npc.xml"));
	m_pOM->AddObject(pBuddy);

	pWeapon3 = (Weapon*)m_pOF->CreateObject( _T("Weapon"));
	pWeapon3->SetHeight(20);
	pWeapon3->SetWidth(10);
	pWeapon3->SetImageID(-1);
	pWeapon3->SetOwner(pBuddy);
	pWeapon3->Init(WPN_RIFLE, 100, 0);
	pWeapon3->SetPosX(pPlayer->GetPosX()+pPlayer->GetWidth()/2);
	pWeapon3->SetPosY(pPlayer->GetPosY());

	pBuddy->SetWeapon(pWeapon3);

	for(int i = 0; i < 10; i++)
		loading->Update();
	loading->Render();

	m_pHUD = new HUD;
	//m_pVM->SetAmbientLight( .0f, .0f, .0f);

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

		for(int i = 0; i < 10; i++)
			loading->Update();
		loading->Render();

	}
	pLevel->SetCollision(tmp);

	//	backGroundID = m_pAM->registerMusic("resource/Sounds/background.mp3");

	swingHitID = m_pAM->RegisterSound("resource/Sounds/swingHit.mp3");

	FMOD_VECTOR sound1 = { 0, 0, 0 };

	//	m_pAM->setMusicPos(backGroundID, sound1);
	//	m_pAM->setMusicVel(backGroundID, sound1);
	//	m_pAM->setMusicLooping(backGroundID, true);
	//	m_pAM->playMusic(backGroundID);

	soundID2 = m_pAM->RegisterSound("resource/Sounds/thunder.wav");
	m_pAM->setSoundPos(soundID2, sound1);

	m_pAM->setSoundVel(soundID2, sound1);
	m_pAM->setSoundLooping(soundID2, false);

	//	musicID = m_pAM->registerMusic("resource/Sounds/rainroof.wav");
	//	m_pAM->setMusicPos(musicID, sound1);

	//	m_pAM->setMusicVel(musicID, sound1);
	//	m_pAM->setMusicLooping(musicID, true);
	//	m_pAM->playMusic(musicID);


	loading->Update();
	loading->Render();


	m_pHUD->m_nHudID = m_pVM->RegisterTexture("resource//graphics//sprites_HUD.png");
	m_pHUD->m_nArrowID = m_pVM->RegisterTexture("resource//graphics//Arrow.png");
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

	m_pOM->AddObject(pPlayer);

	loading->Update();
	loading->Update();
	loading->Update();
	loading->Render();

	m_pVM->SetAmbientLight( .0f, .0f, .0f);

	GamePlayState::GetInstance()->SetPlayer(m_cPlayer);
	GamePlayState::GetInstance()->SetHud(m_pHUD);
	GamePlayState::GetInstance()->SetCompanion(m_cBuddy);

	loading->Reset();
	loading = nullptr;

	m_pMS->InitMessageSystem( &MessageProc );

	m_cPlayer->SetLocked(true);
	m_cPlayer->SetMove(false);

}

void TutorialState::Exit() 
{
	m_cPlayer->SetPosX(600);
	m_cPlayer->SetPosY(500);
	GamePlayState::GetInstance()->SetPlayer(m_cPlayer);
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
	/*m_cEnemies.clear();
	delete m_cBuddy;
	delete m_cPlayer;*/

	m_clevel = nullptr;

	GamePlayState::GetInstance()->SetPlayer(nullptr);
	GamePlayState::GetInstance()->SetCompanion(nullptr);
	GamePlayState::GetInstance()->SetHud(nullptr);
}

bool TutorialState::Input() 
{
	// Pressing Escape will End the Game
	if( m_pDI->KeyPressed(DIK_ESCAPE) || m_pDI->JoystickButtonPressed(1,0) )
	{
		CGame::GetInstance()->ChangeState(PauseMenuState::GetInstance());
	}
	else if( m_pDI->KeyPressed(DIK_T) )
		m_cBuddy->SetTeaching(false);

	if( !m_cBuddy->IsTeaching() )
	{
		CGame::GetInstance()->RemoveState();
		if(!goback)
			CGame::GetInstance()->ChangeState(GamePlayState::GetInstance());
	}

	return true;
}

void TutorialState::Update(float fElapsedTime) 
{
	m_cPlayer->SetBattery(100);
	m_cPlayer->GetWeapons().back()->SetAmmo(100);
	GamePlayState::GetInstance()->SetPlayer(m_cPlayer);
	m_pVM->SetAmbientLight( .0f, .0f, .0f);
	GamePlayState::GetInstance()->SetCamera( float(m_cPlayer->GetPosX() - (CGame::GetInstance()->GetScreenWidth()*0.5)), float(m_cPlayer->GetPosY() - (CGame::GetInstance()->GetScreenHeight()*0.5)));
	m_pOM->UpdateAllObjects(fElapsedTime);
	m_pOM->CheckCollisions();

	if(m_cPlayer->IsOn() && m_cPlayer->GetLightType() < 2)
		m_pOM->CheckTriangleCollisions();

	FMOD_VECTOR tmp;
	tmp.x = m_cPlayer->GetPosX();
	tmp.y = m_cPlayer->GetPosY();
	tmp.z = 0;
	m_pAM->SetListenerPos(tmp);
	m_pAM->setSoundPos(soundID2,tmp);
	m_pES->ProcessEvents();
	m_pMS->ProcessMessages();

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
			m_cBushes[i]->SetIsInBush( false );
	}

	if( check == true )
		GetPlayer()->m_bIsHidden = true; 
	else
		GetPlayer()->m_bIsHidden = false; 

	m_pHUD->Update(fElapsedTime);
	m_pPM->Update(fElapsedTime);

	if( m_cBuddy->IsSpawning() && m_cPlayer->GetWeaponType() != WPN_PISTOL )
		m_cBuddy->Spawn();
	else if( m_cBuddy->IsSpawning() && m_cPlayer->GetWeaponType() == WPN_PISTOL )
		m_cBuddy->SpawnRight();
}

void TutorialState::Render() 
{
	m_pVM->GetSprite()->Flush();
	//m_clevel.Render();

	m_pOM->RenderAllObjects();

	for( unsigned int i = 0; i < m_cBushes.size(); i++)
	{
		if( m_cPlayer->IsOn() && (m_cPlayer->GetLightType() > 1 || m_cBushes[i]->GetShadow()))
		{
			RECT tmp = {0,0,64,64};

			float angle = 0;
			float x2 = m_cPlayer->GetPosX() - m_cBushes[i]->GetPosX();
			float x = x2;
			float y2 = m_cPlayer->GetPosY() - m_cBushes[i]->GetPosY();
			float y = y2;
			x2 *= x2;
			y2 *= y2;
			float distance = sqrt(x2 + y2);

			angle = acos(x/distance);
			if( y < 0)
				angle *=  -1;

			angle -= 1.57079f;

			float xP, yP;
			int z;
			xP = m_cBushes[i]->GetPosX();
			yP = m_cBushes[i]->GetPosY();
			z = m_cBushes[i]->GetImageID();

			m_pVM->DrawStaticTexture(z,xP-GamePlayState::GetInstance()->GetCamera().x,yP-GamePlayState::GetInstance()->GetCamera().y - 15,1.0f,1.25f,&tmp,32,64, angle,D3DCOLOR_ARGB(200,0,0,0));

		}
		m_cBushes[i]->Render();
	}
	m_pPM->Render();
}

void TutorialState::MessageProc(IMessage* pMsg)
{
	TutorialState* self = TutorialState::GetInstance();
	switch( pMsg->GetMessageID() )
	{
		case MSG_CREATE_BULLET:
		{
			// Create bullet
			Bullet* bullet = (Bullet*)( self->m_pOF->CreateObject( _T("Bullet") ) );
			Weapon* pOwner = dynamic_cast< CreateBullet* > (pMsg)->GetWeapon();
			//Set up data members
			bullet->SetImageID( self->m_pVM->RegisterTexture("resource/graphics/bullet.png"));
			bullet->SetHeight(16);
			bullet->SetWidth(16);
			bullet->SetOwner(pOwner);
			bullet->SetPosX(pOwner->GetPosX());
			bullet->SetPosY(pOwner->GetPosY());
			bullet->SetStartPos(pOwner->GetPosX(), pOwner->GetPosY());

			// Smoke effects
			RECT temp = {(long)pOwner->GetPosX(),(long)pOwner->GetPosY()-5,(long)pOwner->GetPosX() + (long)16.0f,(long)16.0f + (long)pOwner->GetPosY()};

			/*bullet->SetSmokeID(Particle_Manager::GetInstance()->ActivateEmitter(self->smokeL));*/

			/*self->m_pPM->GetActiveEmitter(bullet->GetSmokeID())->SetRect(temp);
			self->m_pPM->GetActiveEmitter(bullet->GetSmokeID())->SetLoopin(false);*/

			if( pOwner->GetWeaponType() == WPN_SHOTGUN )
			{
				Bullet* bullet2 = (Bullet*)( self->m_pOF->CreateObject( _T("Bullet") ) );
				Bullet* bullet3 = (Bullet*)( self->m_pOF->CreateObject( _T("Bullet") ) );
				bullet2->SetImageID( self->m_pVM->RegisterTexture("resource/graphics/bullet.png"));
				bullet3->SetImageID( self->m_pVM->RegisterTexture("resource/graphics/bullet.png"));
				//bullet 2
				bullet2->SetHeight(16);
				bullet2->SetWidth(16);
				bullet2->SetOwner(pOwner);
				bullet2->SetPosX(pOwner->GetPosX());
				bullet2->SetPosY(pOwner->GetPosY());
				bullet2->SetStartPos(pOwner->GetPosX(), pOwner->GetPosY());
				//bullet 3
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
						bullet->SetPosY(pOwner->GetPosY()-30);
						bullet2->SetPosY(bullet->GetPosY());
						bullet3->SetPosY(bullet->GetPosY());

						temp.top = (long)bullet->GetPosY();
						temp.bottom = (long)16.0f + (long)bullet->GetPosY();

						bullet->SetSpeedX(0);
						bullet->SetSpeedY(-500);
						bullet->SetRotation(-D3DX_PI/2);
						bullet2->SetSpeedX(50);
						bullet2->SetSpeedY(-500);
						bullet2->SetRotation(-D3DX_PI/2);
						bullet3->SetSpeedX(-50);
						bullet3->SetSpeedY(-500);
						bullet3->SetRotation(-D3DX_PI/2);
						break;
					}
				case DIRE_LEFT:
					{
						bullet->SetPosX((float)pOwner->GetOwner()->GetRect().left);
						bullet->SetPosY((float)bullet->GetPosY()+ 15);
						bullet2->SetPosX(bullet->GetPosX());
						bullet2->SetPosY(bullet->GetPosY());
						bullet3->SetPosX(bullet->GetPosX());
						bullet3->SetPosY(bullet->GetPosY());

						temp.left = (long)bullet->GetPosX();
						temp.right = (long)16.0f + temp.left;

						bullet->SetSpeedX(-500);
						bullet->SetSpeedY(0);
						bullet->SetRotation(D3DX_PI);
						bullet2->SetSpeedX(-500);
						bullet2->SetSpeedY(50);
						bullet2->SetRotation(D3DX_PI);
						bullet3->SetSpeedX(-500);
						bullet3->SetSpeedY(-50);
						bullet3->SetRotation(D3DX_PI);
						break;
					}
				case DIRE_RIGHT:
					{
						bullet->SetPosX((float)pOwner->GetPosX()+30);
						bullet->SetPosY((float)bullet->GetPosY()-15);
						bullet2->SetPosX(bullet->GetPosX());
						bullet2->SetPosY(bullet->GetPosY());
						bullet3->SetPosX(bullet->GetPosX());
						bullet3->SetPosY(bullet->GetPosY());
						
						temp.left = (long)bullet->GetPosX();
						temp.right = (long)16.0f + temp.left;

						bullet->SetSpeedX(500);
						bullet->SetSpeedY(0);
						bullet2->SetSpeedX(500);
						bullet2->SetSpeedY(50);
						bullet3->SetSpeedX(500);
						bullet3->SetSpeedY(-50);
						break;
					}
				case DIRE_DOWN:
					{
						bullet->SetPosY(pOwner->GetPosY()+20);
						bullet->SetPosX(pOwner->GetPosX());
						bullet2->SetPosY(bullet->GetPosY());
						bullet2->SetPosX(bullet->GetPosX());
						bullet3->SetPosY(bullet->GetPosY());
						bullet3->SetPosX(bullet->GetPosX());

						temp.top = (long)bullet->GetPosY();
						temp.bottom = (long)16.0f + (long)bullet->GetPosY();

						bullet->SetSpeedX(0);
						bullet->SetSpeedY(500);
						bullet->SetRotation(D3DX_PI/2);
						bullet2->SetSpeedX(50);
						bullet2->SetSpeedY(500);
						bullet2->SetRotation(D3DX_PI/2);
						bullet3->SetSpeedX(-50);
						bullet3->SetSpeedY(500);
						bullet3->SetRotation(D3DX_PI/2);
						break;
					}
				case DIRE_UPRIGHT:
					{
						bullet->SetPosY(pOwner->GetPosY()-20);
						bullet->SetPosX(pOwner->GetPosX()-20);
						bullet2->SetPosY(bullet->GetPosY());
						bullet2->SetPosX(bullet->GetPosX());
						bullet3->SetPosX(bullet->GetPosX());
						bullet3->SetPosY(bullet->GetPosY());

						bullet->SetSpeedX(500);
						bullet->SetSpeedY(-500);
						bullet->SetRotation(-D3DX_PI/4);
						bullet2->SetSpeedX(500);
						bullet2->SetSpeedY(-550);
						bullet2->SetRotation(-D3DX_PI/4);
						bullet3->SetSpeedX(550);
						bullet3->SetSpeedY(-500);
						bullet3->SetRotation(-D3DX_PI/4);
						break;
					}
				case DIRE_UPLEFT:
					{
						bullet->SetPosY(pOwner->GetPosY()-20);
						bullet->SetPosX(pOwner->GetPosX());
						bullet2->SetPosY(bullet->GetPosY());
						bullet2->SetPosX(bullet->GetPosX());
						bullet3->SetPosX(bullet->GetPosX());
						bullet3->SetPosY(bullet->GetPosY());

						bullet->SetSpeedX(-500);
						bullet->SetSpeedY(-500);
						bullet->SetRotation(-3*D3DX_PI/4);
						bullet2->SetSpeedX(-500);
						bullet2->SetSpeedY(-550);
						bullet2->SetRotation(-3*D3DX_PI/4);
						bullet3->SetSpeedX(-550);
						bullet3->SetSpeedY(-500);
						bullet3->SetRotation(-3*D3DX_PI/4);
						break;
					}
				case DIRE_DOWNLEFT:
					{
						bullet->SetPosY(pOwner->GetPosY()+25);
						bullet->SetPosX(pOwner->GetPosX()+10);
						bullet2->SetPosY(bullet->GetPosY());
						bullet2->SetPosX(bullet->GetPosX());
						bullet3->SetPosX(bullet->GetPosX());
						bullet3->SetPosY(bullet->GetPosY());

						bullet->SetSpeedX(-500);
						bullet->SetSpeedY(500);
						bullet->SetRotation(3*D3DX_PI/4);
						bullet2->SetSpeedX(-500);
						bullet2->SetSpeedY(550);
						bullet2->SetRotation(3*D3DX_PI/4);
						bullet3->SetSpeedX(-550);
						bullet3->SetSpeedY(500);
						bullet3->SetRotation(3*D3DX_PI/4);
						break;
					}
				case DIRE_DOWNRIGHT:
					{
						bullet->SetPosY(pOwner->GetPosY()+20);
						bullet->SetPosX(pOwner->GetPosX());
						bullet2->SetPosY(bullet->GetPosY());
						bullet2->SetPosX(bullet->GetPosX());
						bullet3->SetPosX(bullet->GetPosX());
						bullet3->SetPosY(bullet->GetPosY());

						bullet->SetSpeedX(500);
						bullet->SetSpeedY(500);
						bullet->SetRotation(D3DX_PI/4);
						bullet2->SetSpeedX(500);
						bullet2->SetSpeedY(550);
						bullet2->SetRotation(D3DX_PI/4);
						bullet3->SetSpeedX(550);
						bullet3->SetSpeedY(500);
						bullet3->SetRotation(D3DX_PI/4);
						break;
					}
				}

				bullet->SetSmokeID(Particle_Manager::GetInstance()->ActivateEmitter(self->smokeL));

				self->m_pPM->GetActiveEmitter(bullet->GetSmokeID())->SetRect(temp);
				self->m_pPM->GetActiveEmitter(bullet->GetSmokeID())->SetLoopin(false);

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
						bullet->SetPosY(pOwner->GetPosY()-30);
						bullet->SetSpeedX(0);
						bullet->SetSpeedY(-500);
						bullet->SetRotation(-D3DX_PI/2);
						if(pOwner->GetOwner()->GetCharacterType() == CHA_BOSS2)
							bullet->SetSpeedY(-150);
						break;
					}
				case DIRE_LEFT:
					{
						if(pOwner->GetWeaponType() == WPN_RIFLE)
							bullet->SetPosY(bullet->GetPosY()+15);
						else
							bullet->SetPosY(bullet->GetPosY()+5);
						bullet->SetPosX((float)pOwner->GetOwner()->GetRect2().left);
						bullet->SetSpeedX(-500);
						bullet->SetRotation(D3DX_PI);
						if(pOwner->GetOwner()->GetCharacterType() == CHA_BOSS2)
							bullet->SetSpeedX(-150);
						bullet->SetSpeedY(0);
						break;
					}
				case DIRE_RIGHT:
					{
						if( pOwner->GetWeaponType() == WPN_RIFLE )
							bullet->SetPosY(pOwner->GetPosY()-15);
						else
							bullet->SetPosY(bullet->GetPosY()-25);
						bullet->SetPosX((float)pOwner->GetPosX()+30);
						bullet->SetSpeedX(500);
						if(pOwner->GetOwner()->GetCharacterType() == CHA_BOSS2)
							bullet->SetSpeedX(150);

						bullet->SetSpeedY(0);
						break;
					}
				case DIRE_DOWN:
					{
						bullet->SetPosY(pOwner->GetPosY()+20);
						bullet->SetPosX(pOwner->GetPosX()+5);
						bullet->SetSpeedX(0);
						bullet->SetSpeedY(500);
						bullet->SetRotation(D3DX_PI/2);
						if(pOwner->GetOwner()->GetCharacterType() == CHA_BOSS2)
							bullet->SetSpeedY(150);
						break;
					}
				case DIRE_UPRIGHT:
					{
						if( pOwner->GetWeaponType() == WPN_RIFLE )
						{
							bullet->SetPosY(pOwner->GetPosY()-35);
							bullet->SetPosX(pOwner->GetPosX());
						}
						else
						{
							bullet->SetPosY(pOwner->GetPosY()-35);
							bullet->SetPosX(pOwner->GetPosX());
						}
						
						bullet->SetSpeedX(500);
						bullet->SetSpeedY(-500);
						bullet->SetRotation(-D3DX_PI/4);
						if(pOwner->GetOwner()->GetCharacterType() == CHA_BOSS2)
						{
							bullet->SetSpeedX(150);
							bullet->SetSpeedY(-150);
						}
						break;
					}
				case DIRE_UPLEFT:
					{
						if( pOwner->GetWeaponType() == WPN_RIFLE )
						{
							bullet->SetPosY(pOwner->GetPosY()-35);
							bullet->SetPosX(pOwner->GetPosX());
						}
						else
						{
							bullet->SetPosY(pOwner->GetPosY()-35);
							bullet->SetPosX(pOwner->GetPosX());
						}
						bullet->SetSpeedX(-500);
						bullet->SetSpeedY(-500);
						bullet->SetRotation(-3*D3DX_PI/4);
						if(pOwner->GetOwner()->GetCharacterType() == CHA_BOSS2)
						{
							bullet->SetSpeedX(-150);
							bullet->SetSpeedY(-150);
						}
						break;
					}
				case DIRE_DOWNLEFT:
					{
						if( pOwner->GetWeaponType() == WPN_RIFLE )
						{
							bullet->SetPosY(pOwner->GetPosY()+20);
							bullet->SetPosX(pOwner->GetPosX()+15);
						}
						else
						{
							bullet->SetPosY(pOwner->GetPosY()+20);
							bullet->SetPosX(pOwner->GetPosX()+15);
						}
						bullet->SetSpeedX(-500);
						bullet->SetSpeedY(500);
						bullet->SetRotation(3*D3DX_PI/4);
						if(pOwner->GetOwner()->GetCharacterType() == CHA_BOSS2)
						{
							bullet->SetSpeedX(-150);
							bullet->SetSpeedY(150);
						}
						break;
					}
				case DIRE_DOWNRIGHT:
					{
						if( pOwner->GetWeaponType() == WPN_RIFLE )
						{
							bullet->SetPosY(pOwner->GetPosY()+20);
							bullet->SetPosX(pOwner->GetPosX());
						}
						else
						{
							bullet->SetPosY(pOwner->GetPosY()+20);
							bullet->SetPosX(pOwner->GetPosX());
						}

						bullet->SetSpeedX(500);
						bullet->SetSpeedY(500);
						bullet->SetRotation(D3DX_PI/4);
						if(pOwner->GetOwner()->GetCharacterType() == CHA_BOSS2)
						{
							bullet->SetSpeedX(150);
							bullet->SetSpeedY(150);
						}
						break;
					}
				}

				bullet->SetSmokeID(Particle_Manager::GetInstance()->ActivateEmitter(self->smokeL));

				self->m_pPM->GetActiveEmitter(bullet->GetSmokeID())->SetRect(temp);
				self->m_pPM->GetActiveEmitter(bullet->GetSmokeID())->SetLoopin(false);

				self->m_pOM->AddObject( bullet );
				bullet->Release();
				bullet = nullptr;
			}

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
			for(unsigned int i = 0; i < self->m_cPlayer->m_vpActiveQuests.size();i++)
			{
				if(self->m_cPlayer->m_vpActiveQuests[i]->QuestID == 2)
					self->m_cPlayer->questCounter++;
			}		

			self->m_pOM->RemoveObject( enemyc );
			break;
		}
	}
}