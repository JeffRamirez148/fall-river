#include "Bush.h"
#include "DirectInput.h"
#include "ViewManager.h"
#include "GamePlayState.h"

Bush::Bush()
{
	m_nObjectType = OBJ_BUSH;
	m_bIsInBush = false;
	m_bCloset = false;
	//this->
}

Bush::~Bush()
{

}

void Bush::Update(float fElapsedTime)
{
	fElapsedTime;
	//DirectInput* pDI = DirectInput::GetInstance();

	//if(pDI->KeyDown(DIK_RIGHT) && GamePlayState::GetInstance()->CanMoveRight() )
	//{
	//	SetPosX(GetPosX()-100 * fElapsedTime);
	//}
	//else if(pDI->KeyDown(DIK_LEFT) && GamePlayState::GetInstance()->CanMoveLeft() )
	//{
	//	SetPosX(GetPosX()+100 * fElapsedTime);
	//}

	//if(pDI->KeyDown(DIK_UP) && GamePlayState::GetInstance()->CanMoveUp() )
	//{
	//	SetPosY(GetPosY()+100 * fElapsedTime);
	//}
	//else if(pDI->KeyDown(DIK_DOWN) && GamePlayState::GetInstance()->CanMoveDown() )
	//{
	//	SetPosY(GetPosY()-100 * fElapsedTime);
	//}

}

void Bush::Render() 
{
	ViewManager* pView = ViewManager::GetInstance();
	if( m_bCloset == true )
	{
		return;
	}
	if( m_bIsInBush == false )
	{
		float x, y;
		int z;
		x = GetPosX();
		y = GetPosY();
		z = GetImageID();
		RECT tmp = {0,0,64,64};
		pView->DrawStaticTexture(z,x-GamePlayState::GetInstance()->GetCamera().x,y-GamePlayState::GetInstance()->GetCamera().y,1.0f,1.0f,&tmp,0,0,0,D3DCOLOR_ARGB(255,255,255,255));
		//pView->GetSprite()->Flush();
	}
	else
	{
		float x, y;
		int z;
		x = GetPosX();
		y = GetPosY();
		z = GetImageID();
		RECT tmp = {0,0,64,64};
		pView->DrawStaticTexture(z,x-GamePlayState::GetInstance()->GetCamera().x,y-GamePlayState::GetInstance()->GetCamera().y,1.0f,1.0f,&tmp,0,0,0,D3DCOLOR_ARGB(130,255,255,255));
	}
}

RECT Bush::GetRect()
{
	RECT cRect = {long(GetPosX()), long(GetPosY()), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight()) };
	return cRect;
}

bool Bush::CheckCollision(IObjects* pBase)
{
	RECT cRect;
	RECT temp = GetRect();
	RECT temp2 = pBase->GetRect();
	if( IntersectRect( &cRect, &temp, &temp2 ) == TRUE  )
		return true;
	return false;
}