#ifndef __Quests_h__
#define __Quests_h__

#include <Windows.h>
#include <string>
using namespace std;

#include "tinyxml.h"
#include <vector>

class NPC;

struct Quest_Struct
{
	int QuestID;
	string QuestTitle;
	string QuestBody;
};
class Quests
{
private: 
	NPC* m_pOwner;
	int m_nType;
	char* m_cObjective;


public: 
	//void SetQuest(char* aCName, int aNType, NPC* aPOwner);
	//void CompleteQuest();
	Quests();
	~Quests();
	bool LoadQuests(const char* sz_Filename);
	vector<Quest_Struct*> AllQuests;
};

#endif