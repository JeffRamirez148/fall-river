#include <vector>
using namespace std;

#ifndef __GamePlayState_h__
#define __GamePlayState_h__

#include "IMenuState.h"
#include "BaseObject.h"
#include "ObjectFactory.h"

class ViewManager;
class AudioManager;
class ObjectManager;
class OptionsMenuState;
class EventSystem;
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
	Level*		m_clevel;
	ViewManager*	m_pVM;
	DirectInput*	m_pDI;
	AudioManager*	audio;
	Factory*		m_pOF;
	ObjectManager*	m_pOM;
	EventSystem*	m_pES;

	// Data Members
	float fTime;

	// Characters In the world
	Player*			m_cPlayer;
	vector<Enemy*>	m_cEnemies;
	vector<NPC*>	m_cNpcs;

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

	// Check if the Player can move
	bool CanMoveLeft()	{return m_bCanMoveLeft; }
	bool CanMoveRight() {return m_bCanMoveLeft; }
	bool CanMoveUp()	{return m_bCanMoveLeft; }
	bool CanMoveDown()	{return m_bCanMoveLeft; }

	// Set if the player can move
	void SetCanMoveLeft(bool left)	{m_bCanMoveLeft; }
	void SetCanMoveRight(bool right){m_bCanMoveLeft; }
	void SetCanMoveUp(bool up)		{m_bCanMoveLeft; }
	void SetCanMoveDown(bool down)	{m_bCanMoveLeft; }

	void Enter();

	void Exit();

	bool Input();

	void Update(float fElapsedTime);

	void Render();

	static GamePlayState* GetInstance();

	static void MessageProc(IMessage* pMsg);
};

#endif
