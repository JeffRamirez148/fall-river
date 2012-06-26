#include <vector>
using namespace std;

#ifndef __GamePlayState_h__
#define __GamePlayState_h__

#include "IMenuState.h"
#include "BaseObject.h"
#include "ObjectFactory.h"
#include "MessageSystem.h"

class ViewManager;
class AudioManager;
class ObjectManager;
class OptionsMenuState;
class Particle_Manager;
class EventSystem;
class Level;
class Weapon;
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
	Level*			m_clevel;
	ViewManager*	m_pVM;
	DirectInput*	m_pDI;
	AudioManager*	m_pAM;
	Factory*		m_pOF;
	ObjectManager*	m_pOM;
	EventSystem*	m_pES;
	MessageSystem*	m_pMS;
	Particle_Manager*m_pPM;

	// Data Members
	float fTime;

	// Characters In the world
	Player*			m_cPlayer;
	vector<Enemy*>	m_cEnemies;
	vector<NPC*>	m_cNpcs;
	Weapon*			m_cWeapon;

	// For Everyone else on the screen
	POINTFLOAT camera;

	// Private Constructors
	GamePlayState();
	~GamePlayState()	{ }
	GamePlayState(const GamePlayState&);
	GamePlayState& operator=(const GamePlayState&);

public:

	Player* GetPlayer() {return m_cPlayer;}
	void SetPlayer(Player* pPlayer) {m_cPlayer = pPlayer;}

	POINTFLOAT GetCamera() {return camera;}

	void Enter();

	void Exit();

	bool Input();

	void Update(float fElapsedTime);

	void Render();

	static GamePlayState* GetInstance();

	static void MessageProc(IMessage* pMsg);
};

#endif
