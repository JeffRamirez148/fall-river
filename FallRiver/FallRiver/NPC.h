#include <Windows.h>


#ifndef __NPC_h__
#define __NPC_h__

#include "BaseCharacter.h"
#include <string>
using namespace std;

class Quests;
class ViewManager;
class GamePlayState;

class NPC: public BaseCharacter
{
private: 
	char* m_cName;
	Quests* test_quest_obj;
	string sz_QuestTitle;
	string sz_QuestBody;
	bool showQuest;
	GamePlayState* pGPS;
	ViewManager* pVM;

public:
	int temp_font_id;
private:
	int NPCLabel;
	//bool winLose; // win is alive lose is dead
public:
	NPC();
	~NPC();

	void Update(float fElapsedTime);

	void Render();

	void SetQuest(int q_id);
	bool AllQuestsAvail[10];
	bool CheckCollision(IObjects* pBase);

	void ShowDialog();

	void SetLabel(int l)		{NPCLabel = l;}
	void SetShowQuest(bool q)	{showQuest = q;}
	//void SetWinLose(bool wl)	{winLose = wl;}

	bool GetShowQuest()			{return showQuest;}
	int GetLabel()				{return NPCLabel;}
	void RenderQuests(void);
	//bool GetWinLose()			{return winLose;}

};

#endif
