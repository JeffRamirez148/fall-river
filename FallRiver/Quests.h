#include <Windows.h>
using namespace std;

#ifndef __Quests_h__
#define __Quests_h__

// #include "NPC.h"
// #include "Player.h"

class NPC;
class Player;
class Quests;

class Quests
{
private: 
	NPC* m_pOwner;
	int m_nType;
	char* m_cObjective;

public: 
	void StartQuest(char* aCName, int aNType, NPC* aPOwner);
	void CompleteQuest();
};

#endif
