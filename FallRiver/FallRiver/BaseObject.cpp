#include"BaseObject.h"

void BaseObject::AddRef()
{
	// Increase the reference counter
	++m_unRefCount;
}

void BaseObject::Release()
{
	--m_unRefCount;

	if( m_unRefCount == 0 )
		delete this;
}

void BaseObject::Update(float fElapsedTime)
{
}

void BaseObject::Render()
{

}

bool BaseObject::CheckCollision(IObjects* pBase)
{
	RECT cRect;
	if( IntersectRect(&cRect, &GetRect(), &pBase->GetRect() ) == false )
		return false;

	return true;
}

RECT BaseObject::GetRect()
{
	RECT mRect = {long(GetPosX()), long(GetPosY()), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight())};
	return mRect;
}