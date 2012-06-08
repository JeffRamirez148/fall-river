#include <Windows.h>
#include <vector>
using namespace std;

#ifndef __Level_h__
#define __Level_h__

// #include "Terrain.h"
// #include "GamePlayState.h"
// #include "PickUp.h"

class Terrain;
class GamePlayState;
class PickUp;
class Level;

class Level
{
private:
	vector<Terrain*> _m_pTerrrain;
	vector<PickUp*> _m_vPickUps;

public: 
	Level();

	~Level();

	void Update(float time);

	void Render();

	void Input();
};

#endif
