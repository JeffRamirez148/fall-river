#include <Windows.h>

#ifndef __BaseCharacter_h__
#define __BaseCharacter_h__

// #include "ObjectFactory.h"
// #include "CreateBullet.h"
#include "BaseObject.h"

class ObjectFactory;
class CreateBullet;
// class BaseObject;
class BaseCharacter;

class BaseCharacter: public BaseObject
{
private: 
	int _m_nType;
	unsigned int _m_unRefCount;
	int _m_nHealth;

public: 
	ObjectFactory* _unnamed_ObjectFactory_;
	CreateBullet* _unnamed_CreateBullet_;

	virtual void Update(float fElapsedTime) = 0;

	virtual void Render() = 0;

	virtual bool CheckCollision(BaseCharacter* pBase) = 0;

	void addRef();

	void release();
};

#endif
