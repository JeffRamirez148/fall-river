#ifndef __BaseCharacter_h__
#define __BaseCharacter_h__

#include "BaseObject.h"
#include "AnimInfo.h"
#include "Animation.h"
#include "ViewManager.h"
#include <Windows.h>

enum CHARACTERS { CHA_PLAYER = 0, CHA_COMPANION, CHA_ENEMY, CHA_NPC };
enum DIRECTIONS { DIRE_LEFT = 0, DIRE_UP, DIRE_RIGHT, DIRE_DOWN, DIRE_UPLEFT, DIRE_UPRIGHT, DIRE_DOWNLEFT, DIRE_DOWNRIGHT};

class BaseCharacter: public BaseObject
{
protected: 
	int			m_nCharacterType;
	AnimInfo	m_playerAnim;
	//Animation	thisAnim;

private:
	int				m_nHealth;
	int				m_nDir;
	vector<int>		bloodA;
	bool			died;
	float			goreTime;
public:
	BaseCharacter();
	virtual ~BaseCharacter();
	AnimInfo* GetAnimation() { return &m_playerAnim; }
	virtual void Update(float fElapsedTime);

	virtual void Render();

	virtual bool CheckCollision(IObjects* pBase);
	virtual RECT GetRect2();
	virtual RECT GetRect();

	int GetHealth() {return m_nHealth;}
	int GetDirection() {return m_nDir;}
	int GetCharacterType() {return m_nCharacterType;}

	void SetDirection(int dir) {m_nDir = dir;}

	void SetHealth(int health) {m_nHealth = health;}

	void SetAnimation(int nAnimID) { m_playerAnim.curAnimID = nAnimID; }
};

#endif
