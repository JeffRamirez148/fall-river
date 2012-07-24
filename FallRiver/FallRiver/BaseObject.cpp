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
	fElapsedTime;
}

void BaseObject::Render()
{

}

bool BaseObject::CheckCollision(IObjects* pBase)
{
	RECT cRect;
	RECT temp = GetRect();
	RECT temp2 = pBase->GetRect();
	if( IntersectRect(&cRect, &temp, &temp2 ) == false )
		return false;

	return true;
}

RECT BaseObject::GetRect()
{
	RECT mRect = {long(GetPosX()), long(GetPosY()), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight())};
	return mRect;
}