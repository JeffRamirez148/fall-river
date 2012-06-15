#ifndef __BaseCharacter_h__
#define __BaseCharacter_h__

#include "BaseObject.h"
#include <Windows.h>

enum CHARACTERS { CHA_PLAYER = 0, CHA_COMPANION, CHA_ENEMY, CHA_NPC };

class BaseCharacter: public BaseObject
{
protected: 
	int				m_nCharacterType;

private:
	int				m_nHealth;

public:
	BaseCharacter();
	virtual ~BaseCharacter();

	virtual void Update(float fElapsedTime);

	virtual void Render();

	virtual bool CheckCollision(IObjects* pBase);
	virtual RECT GetRect();

	int GetHealth() {return m_nHealth;}
	int GetCharacterType() {return m_nCharacterType;}

	void SetHealth(int health) {m_nHealth = health;}
};

#endif
