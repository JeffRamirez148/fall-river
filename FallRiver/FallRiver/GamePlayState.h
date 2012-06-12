#include <vector>
using namespace std;

#ifndef __GamePlayState_h__
#define __GamePlayState_h__

#include "AudioManager.h"
#include "IMenuState.h"
#include "BaseObject.h"
#include "ObjectFactory.h"

class ViewManager;
class AudioManager;
class ObjectManager;
class OptionsMenuState;
class Level;
class DirectInput;
class Enemy;
class Player;
class HUD;
class NPC;
class IMessage;

typedef CObjectFactory< std::wstring, BaseObject> Factory;

class GamePlayState : public IMenuState
{
private: 
	// Wrapper Memebers
	Level* level;
	ViewManager* view;
	DirectInput* m_pDI;
	AudioManager* audio;
	Factory* m_pOF;
	ObjectManager* m_pOM;

	// Data Members
	float fTime;

	// Characters In the world
	Player*			player;
	vector<Enemy*>	enemies;
	vector<NPC*>	npcs;

	// Private Constructors
	GamePlayState()		{ }
	~GamePlayState()	{ }
	GamePlayState(const GamePlayState&);
	GamePlayState& operator=(const GamePlayState&);

public:
	void Enter();

	void Exit();

	bool Input();

	void Update(float fElapsedTime);

	void Render();

	static GamePlayState* GetInstance();

	static void MessageProc(IMessage* pMsg);
};

#endif
