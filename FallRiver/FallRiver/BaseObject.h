#ifndef __BaseObject_h__
#define __BaseObject_h__

#include <Windows.h>
#include "IObjects.h"

enum OBJECTS { OBJ_BUSH = 0, OBJ_CLOSET, OBJ_BULLET, OBJ_CHARACTER, OBJ_PICKUP, OBJ_LIGHT, OBJ_LEVEL };

class BaseObject : public IObjects
{
private: 
	int m_nHeight;
	int m_nWidth;
	int m_nImageID;
	unsigned int	m_unRefCount;

protected:
	float m_nPosX;
	float m_nPosY;
	float	m_nVelX;
	float	m_nVelY;
	int m_nObjectType;

public: 

	virtual void AddRef();

	virtual void Release();

	virtual void Update(float fElapsedTime);

	virtual void Render();

	virtual bool CheckCollision(IObjects* pBase);
	virtual RECT GetRect();

	float GetPosX()	{return m_nPosX;}
	float GetPosY()	{return m_nPosY;}
	float GetVelX() {return m_nVelX;}
	float GetVelY() {return m_nVelY;}
	int GetHeight() {return m_nHeight;}
	int GetWidth()	{return m_nWidth;}
	int GetImageID(){return m_nImageID;}
	int GetObjectType() {return m_nObjectType;}

	void SetPosX(float x)	{m_nPosX = x;}
	void SetPosY(float y) {m_nPosY = y;}
	void SetVelX(float x) {m_nVelX = x;}
	void SetVelY(float y) {m_nVelY = y;}
	void SetHeight(int height) {m_nHeight = height;}
	void SetWidth(int width)   {m_nWidth = width;}
	void SetImageID(int id)	   {m_nImageID = id;}
};

#endif
