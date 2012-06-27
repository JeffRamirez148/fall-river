#include <Windows.h>
using namespace std;

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
	int temp_font_id;
	int NPCLabel;
public:
	NPC();
	~NPC();

	void Update(float fElapsedTime);

	void Render();

	void SetQuest(int q_id);

	bool CheckCollision(IObjects* pBase);

	void ShowDialog();

	void SetLabel(int l)  {NPCLabel = l;}
	void SetShowQuest(bool q) {showQuest = q;}

	bool GetShowQuest() {return showQuest;}
	int GetLabel()  {return NPCLabel;}

};

#endif
