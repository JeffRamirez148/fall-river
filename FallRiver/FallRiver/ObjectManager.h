#include <Windows.h>
#include <vector>
using namespace std;

#ifndef __ObjectManager_h__
#define __ObjectManager_h__

// #include "GamePlayState.h"
// #include "BaseObject.h"

class GamePlayState;
class BaseObject;
class ObjectManager;

class ObjectManager
{
	private: 
		vector<BaseObject*> _objects;
	float _fTime;

public: 
	void Enter();

	void Exit();

	bool Input();

	void Update(float fElapsedTime);

	void Render();

	static ObjectManager* GetInstance();
};

#endif
