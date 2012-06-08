#include <Windows.h>

#ifndef __BaseObject_h__
#define __BaseObject_h__

// #include "ObjectManager.h"
// #include "ObjectFactory.h"

class ObjectManager;
class ObjectFactory;
class BaseObject;

class BaseObject
{
private: 
	int _m_nPosX;
	int _m_nPosY;
	int _m_nHeight;
	int _m_nWidth;
	int _m_nImageID;
	int _m_nType;
public: 
	ObjectManager* _unnamed_ObjectManager_;

	ObjectFactory* _unnamed_ObjectFactory_;

	virtual void Update(float fElapsedTime) = 0;

	virtual void Render() = 0;
};

#endif
