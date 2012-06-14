#pragma once

#include <Windows.h>

class IObjects
{
public:
	virtual void AddRef() = 0;

	virtual void Release() = 0;

	virtual void Update(float fElapsedTime) = 0;

	virtual void Render() = 0;

	virtual bool CheckCollision(IObjects* pBase) = 0;
	virtual RECT GetRect() = 0;
};