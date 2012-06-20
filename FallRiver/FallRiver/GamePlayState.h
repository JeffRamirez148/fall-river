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
class EventSystem;
#include "Level.h"
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
	Level			m_clevel;
	ViewManager*	m_pVM;
	DirectInput*	m_pDI;
	AudioManager*	m_pAM;
	Factory*		m_pOF;
	ObjectManager*	m_pOM;
	EventSystem*	m_pES;
	MessageSystem*	m_pMS;

	// Data Members
	float fTime;

	// Characters In the world
	Player*			m_cPlayer;
	vector<Enemy*>	m_cEnemies;
	vector<NPC*>	m_cNpcs;
	Weapon*			m_cWeapon;

	// For Everyone else on the screen
	bool m_bCanMoveLeft;
	bool m_bCanMoveRight;
	bool m_bCanMoveUp;
	bool m_bCanMoveDown;

	// Private Constructors
	GamePlayState();
	~GamePlayState()	{ }
	GamePlayState(const GamePlayState&);
	GamePlayState& operator=(const GamePlayState&);

public:

	Player* GetPlayer() {return m_cPlayer;}
	void SetPlayer(Player* pPlayer) {m_cPlayer = pPlayer;}
	// Check if the Player can move
	bool CanMoveLeft()	{return m_bCanMoveLeft; }
	bool CanMoveRight() {return m_bCanMoveRight; }
	bool CanMoveUp()	{return m_bCanMoveUp; }
	bool CanMoveDown()	{return m_bCanMoveDown; }

	// Set if the player can move
	void SetCanMoveLeft(bool left)	{m_bCanMoveLeft = left; }
	void SetCanMoveRight(bool right){m_bCanMoveRight = right; }
	void SetCanMoveUp(bool up)		{m_bCanMoveUp = up; }
	void SetCanMoveDown(bool down)	{m_bCanMoveDown = down; }

	void Enter();

	void Exit();

	bool Input();

	void Update(float fElapsedTime);

	void Render();

	static GamePlayState* GetInstance();

	static void MessageProc(IMessage* pMsg);
};

#endif
