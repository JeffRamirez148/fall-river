#include "NPC.h"
#include "ViewManager.h"
#include "DestroyNPC.h"
#include "DirectInput.h"
#include "GamePlayState.h"
#include "CGame.h"
#include "Quests.h"
#include "Player.h"
#include "WinMenuState.h"
#include "LoseMenuState.h"

NPC::NPC()
{
	m_nCharacterType = CHA_NPC;
	m_nVelX = 0;
	m_nVelY = 0;
	test_quest_obj = new Quests;
	test_quest_obj->LoadQuests("resource/graphics/QuestLocker.xml");
	showQuest = false;
	pGPS = GamePlayState::GetInstance();
	pVM = ViewManager::GetInstance();
	temp_font_id = pVM->RegisterFont("resource/graphics/FallRiver_0.png");
	//winLose = true;
}

NPC::~NPC()
{

}

void NPC::Update(float fElapsedTime) 
{
	DirectInput* pDI = DirectInput::GetInstance();
	

	
	
	
	Player* tempPlayer = pGPS->GetPlayer();
	double playerX = (tempPlayer->GetPosX());
	double npcX = this->GetPosX();
	//double playerY = (tempPlayer->GetRect().bottom/2) + tempPlayer->GetRect().top;
	double playerY = tempPlayer->GetPosY();
	double npcY = this->GetPosY();

	double distance;
	distance = sqrt(pow(playerX - npcX,2) + pow(playerY - npcY,2));

	//if( distance >= 200 && pDI->KeyDown(DIK_A))
	if( distance <= 70.0f )
	{
		showQuest = true;
		if(pDI->KeyPressed(DIK_A) )
		{
			bool questEmpty = true;

			for(unsigned int i = 0; i < pGPS->GetPlayer()->m_vpActiveQuests.size(); i++)
			{
				if(pGPS->GetPlayer()->m_vpActiveQuests[i]->QuestID == NPCLabel || pGPS->GetPlayer()->m_vpActiveQuests[i] == nullptr )
				{
					questEmpty = false;
				}
				/*if(pGPS->GetPlayer()->m_vpActiveQuests[i]->QuestID == NPCLabel + 1)
				{
					CGame::GetInstance()->ChangeState(WinMenuState::GetInstance());
				}*/
			}
			if(questEmpty)
				pGPS->GetPlayer()->AddQuest(test_quest_obj->AllQuests[NPCLabel]);			
		}
		if(pDI->KeyPressed(DIK_RETURN))
		{
			for(unsigned int i = 0; i < pGPS->GetPlayer()->m_vpActiveQuests.size(); i++)
			{
				if(pGPS->GetPlayer()->m_vpActiveQuests[i]->QuestID == NPCLabel - 1)
				{
					// temp for first playable
					// Change this to put in next level and complete the quest 
					CGame::GetInstance()->ChangeState(WinMenuState::GetInstance());
					
				}
			}
		}
		if(GamePlayState::GetInstance()->GetWinLose() == false)
			CGame::GetInstance()->ChangeState(LoseMenuState::GetInstance());
		
			
	}
	else
		showQuest = false;

	BaseCharacter::Update(fElapsedTime);
}

void NPC::Render() 
{
	// Render this NPC
 //ViewManager* pVM = ViewManager::GetInstance();

	pVM->GetSprite()->Flush();
	RECT reRect = {long(GetPosX() - GamePlayState::GetInstance()->GetCamera().x), long(GetPosY() - GamePlayState::GetInstance()->GetCamera().y), long(reRect.left+GetWidth()), long(reRect.top + GetHeight())};

	pVM->DrawRect(reRect, 0, 255, 0);



	//pVM->DrawRect(GetRect(), 0, 255, 0);

	

	//char buffer[15];
	//_itoa_s(double(distance), buffer, 10);
	//pVM->DrawFont(temp_font_id,buffer,600,200);
	// left top right bottom
	RECT questBox;
	questBox.left = 0;
	questBox.top = CGame::GetInstance()->GetScreenHeight() - 100;
	questBox.right = CGame::GetInstance()->GetScreenWidth();
	questBox.bottom = CGame::GetInstance()->GetScreenHeight();

	if(showQuest == true && NPCLabel == 0)
	{  
  		pVM->DrawRect(questBox,255,255,255);
		pVM->DrawFont(temp_font_id,(char*)test_quest_obj->AllQuests[NPCLabel]->QuestBody.c_str(),0,500,0.8f,0.8f,0,0,0,D3DCOLOR_XRGB(0,0,0));
	}
	if(showQuest == true && NPCLabel == 1)
	{  
  		pVM->DrawRect(questBox,255,255,255);
		pVM->DrawFont(temp_font_id,(char*)test_quest_obj->AllQuests[NPCLabel]->QuestBody.c_str(),0,500,0.8f,0.8f,0,0,0,D3DCOLOR_XRGB(0,0,0));
	}
	if(showQuest == true && NPCLabel == 2)
	{  
  		pVM->DrawRect(questBox,255,255,255);
		pVM->DrawFont(temp_font_id,(char*)test_quest_obj->AllQuests[NPCLabel]->QuestBody.c_str(),0,500,0.8f,0.8f,0,0,0,D3DCOLOR_XRGB(0,0,0));
	}
}

void NPC::SetQuest(int q_id) 
{

	sz_QuestTitle = test_quest_obj->AllQuests[q_id - 1]->QuestTitle;
	sz_QuestBody = test_quest_obj->AllQuests[q_id - 1]->QuestBody;

}

bool NPC::CheckCollision(IObjects* pBase) 
{
	return false;
}
void NPC::ShowDialog()
{
	
}
