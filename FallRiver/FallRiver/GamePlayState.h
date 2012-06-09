#include <vector>
using namespace std;

#ifndef __GamePlayState_h__
#define __GamePlayState_h__

#include "AudioManager.h"
#include "IMenuState.h"

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

class GamePlayState : public IMenuState
{
private: 
	// Wrapper Memebers
	Level* level;
	ViewManager* view;
	DirectInput* m_pDI;
	AudioManager* audio;

	// Data Members
	float fTime;

	// Characters In the world
	Player*			player;
	vector<Enemy*>	enemies;
	vector<NPC*>	npcs;

public:
	void Enter();

	void Exit();

	bool Input();

	void Update(float fElapsedTime);

	void Render();

	static GamePlayState* GetInstance();
};

#endif
