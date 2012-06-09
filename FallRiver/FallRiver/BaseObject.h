#include <Windows.h>

#ifndef __BaseObject_h__
#define __BaseObject_h__

class ObjectManager;
class ObjectFactory;
class BaseObject;

enum OBJECTS { OBJ_BUSH = 0, OBJ_CLOSET, OBJ_BULLET, OBJ_CHARACTER };

class BaseObject
{
private: 
	int m_nPosX;
	int m_nPosY;
	int m_nHeight;
	int m_nWidth;
	int m_nImageID;

protected:
	int m_nObjectType;

public: 

	virtual void AddRef() = 0;

	virtual void Release() = 0;

	virtual void Update(float fElapsedTime) = 0;

	virtual void Render() = 0;

	virtual bool CheckCollision(BaseObject* pBase) = 0;
	virtual RECT GetRect();

	int GetPosX()	{return m_nPosX;}
	int GetPosY()	{return m_nPosY;}
	int GetHeight() {return m_nHeight;}
	int GetWidth()	{return m_nWidth;}
	int GetImageID(){return m_nImageID;}
	int GetObjectType() {return m_nObjectType;}

	void SetPosX(int x)	{m_nPosX = x;}
	void SetPosY(int y) {m_nPosY = y;}
	void SetHeight(int height) {m_nHeight = height;}
	void SetWidth(int width)   {m_nWidth = width;}
	void SetImageID(int id)	   {m_nImageID = id;}
};

#endif
