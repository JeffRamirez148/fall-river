#include "GamePlayState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "ObjectManager.h"
#include "OptionsMenuState.h"
#include "PauseMenuState.h"
#include "Level.h"
#include "CGame.h"
#include "DirectInput.h"
#include "Enemy.h"
#include "EventSystem.h"
#include "Player.h"
#include "Weapon.h"
#include "Particle_Manager.h"
#include "HUD.h"
#include "XMLManager.h"
#include "Message.h"
#include "Bullet.h"
#include "ChasingAI.h"
#include "ShootingAi.h"
#include "NPC.h"
#include "PickUp.h"
#include "DestroyBullet.h"
#include "DestroyEnemyC.h"
#include "DestroyEnemyS.h"
#include "DestroyNPC.h"
#include "DestroyPickUp.h"

GamePlayState::GamePlayState()
{
	m_pVM = nullptr;
	m_pDI = nullptr;
	m_pAM = nullptr;
	m_pOF = nullptr;
	m_pOM = nullptr;
	m_pES = nullptr;

	m_cWeapon = nullptr;

	m_bCanMoveLeft	= true;
	m_bCanMoveRight	= true;
	m_bCanMoveUp	= true;
	m_bCanMoveDown	= true;
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

	m_pOF->RegisterClassType< BaseObject	>( _T("BaseObject") );
	m_pOF->RegisterClassType< Player		>( _T("Player") );
	m_pOF->RegisterClassType< Weapon		>( _T("Weapon") );
	m_pOF->RegisterClassType< NPC			>( _T("NPC") );
	m_pOF->RegisterClassType< Enemy			>( _T("Enemy") );
	m_pOF->RegisterClassType< ShootingAi	>( _T("ShootingAi") );
	m_pOF->RegisterClassType< ChasingAI		>( _T("ChasingAI") );
	m_pOF->RegisterClassType< Bullet		>( _T("Bullet") );

	m_clevel.LoadLevel("level.xml");

	for(int i = 0; i < 1; i++)
	{
		m_cEnemies.push_back(nullptr);
		m_cEnemies[i] = (ShootingAi*)m_pOF->CreateObject( _T("ShootingAi") );
		ShootingAi* pEnemy = (ShootingAi*)(m_cEnemies[i]);
		pEnemy->SetHeight(32);
		pEnemy->SetWidth(32);
		pEnemy->SetImageID(-1);
		pEnemy->SetPosX(200);
		pEnemy->SetPosY(100);
		m_pOM->AddObject(pEnemy);
	}

	for(int i = 0; i < 1; i++)
	{
		m_cEnemies.push_back(nullptr);
		m_cEnemies[i] = (ChasingAI*)m_pOF->CreateObject( _T("ChasingAI") );
		ChasingAI* pEnemy = (ChasingAI*)(m_cEnemies[i]);
		pEnemy->SetHeight(32);
		pEnemy->SetWidth(32);
		pEnemy->SetImageID(-1);
		pEnemy->SetPosX(200);
		pEnemy->SetPosY(200);
		m_pOM->AddObject(pEnemy);
	}

	for(int i = 0; i < 1; i++)
	{
		m_cNpcs.push_back(nullptr);
		m_cNpcs[i] = (NPC*)m_pOF->CreateObject( _T("NPC") );
		NPC* pNpc =(NPC*)(m_cNpcs[i]);
		pNpc->SetHeight(32);
		pNpc->SetWidth(32);
		pNpc->SetImageID(-1);
		pNpc->SetPosX(400);
		pNpc->SetPosY(100);
		m_pOM->AddObject(pNpc);
	}

	m_cWeapon = (Weapon*)m_pOF->CreateObject( _T("Weapon") );
	Weapon* pWeapon = (Weapon*)m_cWeapon;
	pWeapon->SetHeight(10);
	pWeapon->SetWidth(20);
	pWeapon->SetImageID(-1);
	pWeapon->SetPosX(int(CGame::GetInstance()->GetScreenWidth()*0.4));
	pWeapon->SetPosY(int(CGame::GetInstance()->GetScreenHeight()*0.4));


	m_cPlayer = (Player*)m_pOF->CreateObject( _T("Player"));
	Player* pPlayer = (Player*)(m_cPlayer);
	pPlayer->SetHeight(32);
	pPlayer->SetWidth(32);
	pPlayer->SetImageID(-1);
	pPlayer->SetPosX(int(CGame::GetInstance()->GetScreenWidth()*0.45));
	pPlayer->SetPosY(int(CGame::GetInstance()->GetScreenHeight()*0.4));

	m_pOM->AddObject(pPlayer);
	m_pOM->AddObject(pWeapon);
}

void GamePlayState::Exit() 
{
	m_pVM = nullptr;
	m_pDI = nullptr;
	m_pAM = nullptr;
	m_pOF = nullptr;
	m_pOM = nullptr;
	m_pES = nullptr;
}

bool GamePlayState::Input() 
{
	if( m_pDI->KeyPressed(DIK_ESCAPE) )
		CGame::GetInstance()->ChangeState(PauseMenuState::GetInstance());

	return true;
}

void GamePlayState::Update(float fElapsedTime) 
{
	m_clevel.Update(fElapsedTime);
	m_pOM->UpdateAllObjects(fElapsedTime);
	m_pES->ProcessEvents();
}

void GamePlayState::Render() 
{
	m_pVM->GetSprite()->Flush();
	m_clevel.Render();

	m_pOM->RenderAllObjects();
}

void GamePlayState::MessageProc(IMessage* pMsg)
{
	GamePlayState* self = GamePlayState::GetInstance();
	switch( pMsg->GetMessageID() )
	{
	case MSG_CREATE_BULLET:
		{
			// Create bullet
			Bullet* bullet = dynamic_cast< Bullet* >( self->m_pOF->CreateObject( _T("Bullet") ) );
			//Set up data members			
			//bullet->SetImageID( self->m_BulletID );
			//bullet->SetHeight( );
			//bullet->SetWidth( );
			//bullet->SetPosX( );
			//bullet->SetPosY( );
			
			// Add bullet to object manager
			self->m_pOM->AddObject( bullet );
			bullet->Release();
			bullet = nullptr;

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
			self->m_pOM->RemoveObject( enemyc );
			break;
		}
	case MSG_DESTROY_ENEMYS:
		{
			ShootingAi* enemys = dynamic_cast<DestroyEnemyS*>(pMsg)->GetEnemyS();
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