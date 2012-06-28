#include <Windows.h>
using namespace std;

#include "Quests.h"
#include "NPC.h"
#include "Player.h"

Quests::Quests()
{
	m_pOwner = nullptr;
	m_nType = -1;
	m_cObjective = "";
}
Quests::~Quests()
{

}
bool Quests::LoadQuests(const char* sz_Filename)
{
	TiXmlDocument doc;
	
	// attempt to load
	if(!(doc.LoadFile(sz_Filename)))
		return false;

	TiXmlElement* pRoot = doc.RootElement();

	if(pRoot == nullptr)
		return false;

	//int q_size = AllQuests.size();
	//if( q_size > 0)
		AllQuests.clear();

	TiXmlElement* pQuestLayer = pRoot->FirstChildElement("Quest_Layer");
	TiXmlElement* pQuestInfo = pQuestLayer->FirstChildElement("Quest_Info");

	
	
	string temp_quest;
	string temp_title;
	int temp_ID;

	while(pQuestLayer != nullptr)
	{
		while(pQuestInfo != nullptr)
		{
			Quest_Struct* temp = new Quest_Struct;
			pQuestInfo->Attribute("Quest_ID",&temp_ID);
			temp_title = pQuestInfo->Attribute("Quest_Title");
			temp_quest = pQuestInfo->Attribute("Quest_Dialog");

			for(unsigned int i = 0; i < temp_quest.size();i++)
			{
				

				if( temp_quest[i] == '.' )
					temp_quest.insert(i+1,1,'\n');//temp_quest.insert(i+1,'\n');
				
			}
			temp->QuestID = temp_ID;
			temp->QuestTitle = temp_title;
			temp->QuestBody = temp_quest;

			AllQuests.push_back(temp);

			pQuestInfo = pQuestInfo->NextSiblingElement("Quest_Info");
		}
		pQuestLayer = pQuestLayer->NextSiblingElement("Quest_Layer");
	}
	return true;
}

