#include "PickUp.h"
#include "DestroyPickUp.h"
#include "DirectInput.h"

PickUp::PickUp()
{
	m_nObjectType = OBJ_PICKUP;
}

PickUp::~PickUp()
{

}

void PickUp::Update(float fElapsedTime)
{
	DirectInput* pDI = DirectInput::GetInstance();

	if(pDI->KeyDown(DIK_RIGHT) )
		SetVelX(-100);
	else if(pDI->KeyDown(DIK_LEFT) )
		SetVelX(100);
	else
		SetVelX(0);
	
	if(pDI->KeyDown(DIK_UP) )
		SetVelY(100);
	else if(pDI->KeyDown(DIK_DOWN) )
		SetVelY(-100);
	else
		SetVelY(0);
}

void PickUp::Render() 
{
}

RECT PickUp::GetRect()
{
	RECT cRect = {long(GetPosX()), long(GetPosY()), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight()) };
	return cRect;
}

bool PickUp::CheckCollision(BaseObject* pBase)
{
	RECT cRect;
	if( IntersectRect( &cRect, &GetRect(), &pBase->GetRect() ) == false  )
		return false;
	return true;
}
