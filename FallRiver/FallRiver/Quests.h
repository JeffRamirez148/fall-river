#ifndef __Quests_h__
#define __Quests_h__

class NPC;

class Quests
{
private: 
	NPC* m_pOwner;
	int m_nType;
	char* m_cObjective;

public: 
	void SetQuest(char* aCName, int aNType, NPC* aPOwner);
	void CompleteQuest();
};

#endif
