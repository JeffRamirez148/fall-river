#include "Bush.h"
#include "DirectInput.h"

Bush::Bush()
{
	m_nObjectType = OBJ_BUSH;
}

Bush::~Bush()
{

}

void Bush::Update(float fElapsedTime)
{
	DirectInput* pDI = DirectInput::GetInstance();

	if(pDI->KeyDown(DIK_RIGHT) )
		SetPosX(GetPosX()+30*(int)fElapsedTime);
	else if(pDI->KeyDown(DIK_LEFT) )
		SetPosX(GetPosX()-30*(int)fElapsedTime);
	
	if(pDI->KeyDown(DIK_UP) )
		SetPosX(GetPosY()+30*(int)fElapsedTime);
	else if(pDI->KeyDown(DIK_DOWN) )
		SetPosY(GetPosY()-30*(int)fElapsedTime);
}

void Bush::Render() 
{
}

RECT Bush::GetRect()
{
	RECT cRect = {long(GetPosX()), long(GetPosY()), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight()) };
	return cRect;
}

bool Bush::CheckCollision(BaseObject* pBase)
{
	RECT cRect;
	if( IntersectRect( &cRect, &GetRect(), &pBase->GetRect() ) == false  )
		return false;
	return true;
}