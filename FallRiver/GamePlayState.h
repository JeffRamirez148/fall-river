#include <Windows.h>
#include <vector>
using namespace std;

#ifndef __GamePlayState_h__
#define __GamePlayState_h__

#include "AudioManager.h"


class ViewManager;
class AudioManager;
class ObjectManager;
class OptionsMenuState;
class Level;
class DirectInput;
class Enemy;
class Player;
class MessageSystem;
class Particle_Manager;
class HUD;
class NPC;
class XMLManager;
class GamePlayState;

class GamePlayState
{
private: 
	Level* level;
	ViewManager* view;
	DirectInput* nput;
	AudioManager audio;
	float fTime;
	Player* player;
	vector<Enemy*> enemies;
	vector<NPC*> npcs;

public:
	void Enter();

	void Exit();

	bool Input();

	void Update(float fElapsedTime);

	void Render();

	GamePlayState* GetInstance();
};

#endif
