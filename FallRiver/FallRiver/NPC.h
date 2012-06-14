#include <Windows.h>
using namespace std;

#ifndef __NPC_h__
#define __NPC_h__

#include "BaseCharacter.h"

class NPC: public BaseCharacter
{
private: 
	char* m_cName;

public:
	NPC();
	~NPC();

	void Update(float fElapsedTime);

	void Render();

	void SaySomething();

	bool CheckCollision(BaseCharacter* pBase);
};

#endif
