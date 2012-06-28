#include "SpawnPoint.h"
#include "ViewManager.h"
#include "DirectInput.h"
#include "GamePlayState.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "ChasingAI.h"
#include "Enemy.h"

//#define SPAWNCAP 5;


SpawnPoint::SpawnPoint(void)
{
	m_nObjectType = OBJ_SPAWN;
	m_fSpawnTime = 0;
	m_bCanSpawn = false;
	m_bIsColliding = false;
	m_nSpawnCounter = 0;
}


SpawnPoint::~SpawnPoint(void)
{
}

void SpawnPoint::Update(float fElapsedTime)
{

	m_fSpawnTime += fElapsedTime;
	//m_pOF = m_pOF->GetInstance();
	//m_pOF = Factory::GetInstance();
	//m_pOM = ObjectManager::GetInstance();
	//m_pOF->RegisterClassType< ChasingAI		>( _T("ChasingAI") );

	//ObjectFactory

	DirectInput* pDI = DirectInput::GetInstance();

	/*if(pDI->KeyDown(DIK_RIGHT) && GamePlayState::GetInstance()->CanMoveRight() )
	{
		SetPosX(GetPosX()-100 * fElapsedTime);
	}
	else if(pDI->KeyDown(DIK_LEFT) && GamePlayState::GetInstance()->CanMoveLeft() )
	{
		SetPosX(GetPosX()+100 * fElapsedTime);
	}

	if(pDI->KeyDown(DIK_UP) && GamePlayState::GetInstance()->CanMoveUp() )
	{
		SetPosY(GetPosY()+100 * fElapsedTime);
	}
	else if(pDI->KeyDown(DIK_DOWN) && GamePlayState::GetInstance()->CanMoveDown() )
	{
		SetPosY(GetPosY()-100 * fElapsedTime);
	}
	*/
	//ChasingAI* pEnemy;
	if( m_fSpawnTime > 30 )
	{
		if( m_nSpawnCounter < 3 )
		{
			m_bCanSpawn = true;
			m_fSpawnTime = 0;
			m_nSpawnCounter++;
		}
	}

}


void SpawnPoint::Render()
{
	ViewManager* pView = ViewManager::GetInstance();
	RECT tmp ;//= GetRect();
	tmp.top = (LONG)(GetRect().top-GamePlayState::GetInstance()->GetCamera().y);
	tmp.right = (LONG)(GetRect().right-GamePlayState::GetInstance()->GetCamera().x);
	tmp.left = (LONG)(GetRect().left-GamePlayState::GetInstance()->GetCamera().x);
	tmp.bottom = (LONG)(GetRect().bottom-GamePlayState::GetInstance()->GetCamera().y);
	//= GetRect();
	//pView->GetSprite()->Flush();
	pView->DrawRect(tmp,0,255,255);
}


RECT SpawnPoint::GetRect()
{
	RECT cRect = {long(GetPosX()), long(GetPosY()), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight()) };
	return cRect;
}


bool SpawnPoint::CheckCollision(IObjects* pBase)
{
	RECT cRect;
	if(pBase->GetObjectType() == OBJ_CHARACTER)
	{
		if( IntersectRect( &cRect, &GetRect(), &pBase->GetRect() ) == TRUE  )
		{
			//m_bIsColliding = true;
			return true;
		}
		else
		{
			return false;
		}
	}

	if( IntersectRect( &cRect, &GetRect(), &pBase->GetRect() ) == TRUE  )
	{
		return true;
	}

	return false;
}

bool SpawnPoint::TestCollision(Enemy* pEnemy )
{
	RECT cRect,test1,test2;

	test1 = GetRect();
	test2 = pEnemy->GetRect();
	
	if( IntersectRect( &cRect, &test1, &test2 ) == TRUE  )
	{
		m_bIsColliding = true;
		return true;
	}
	return false;
}
