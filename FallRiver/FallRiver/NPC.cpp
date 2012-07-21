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
#include "EventSystem.h"
#include "HUD.h"

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
	QuestBoxID = pVM->RegisterTexture("resource/graphics/Paperthingy.png");
	//winLose = true;

	//AnimInfo startup
	m_playerAnim.curAnimation = 0;
	m_playerAnim.curAnimID = 0;
	m_playerAnim.curFrame = 0;
	m_playerAnim.fTime = 0;

	for(int i = 0; i < 10; i++)
		this->AllQuestsAvail[i] = true;
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

	if( distance <= 100 )
	{
		if(tempPlayer->GetPosX() > GetPosX())
	{
		if(tempPlayer->GetPosY() > GetPosY()+20)
			SetDirection(DIRE_DOWNRIGHT);
		else if(tempPlayer->GetPosY() < GetPosY()-20)
			SetDirection(DIRE_UPRIGHT);
		else
			SetDirection(DIRE_RIGHT);
	}
	else if(tempPlayer->GetPosX() < GetPosX()-10)
	{
		if(tempPlayer->GetPosY() > GetPosY()+20)
			SetDirection(DIRE_DOWNLEFT);
		else if(tempPlayer->GetPosY() < GetPosY()-20)
			SetDirection(DIRE_UPLEFT);
		else
			SetDirection(DIRE_LEFT);
	}
	else if(tempPlayer->GetPosY() > GetPosY())
		SetDirection(DIRE_DOWN);
	else if(tempPlayer->GetPosY() < GetPosY())
		SetDirection(DIRE_UP);
	}

	//if( distance >= 200 && pDI->KeyDown(DIK_A))
	if( distance <= 70.0f )
	{
		showQuest = true;
		if(pDI->KeyPressed(DIK_T) || pDI->JoystickButtonPressed(0,0)  )
		{
			//bool questEmpty = true;

			//for(unsigned int i = 0; i < pGPS->GetPlayer()->m_vpActiveQuests.size(); i++)
			//{
			//	if(pGPS->GetPlayer()->m_vpActiveQuests[i]->QuestID == NPCLabel || pGPS->GetPlayer()->m_vpActiveQuests[i] == nullptr )
			//	{
			//		questEmpty = false;
			//		AllQuestsAvail[NPCLabel] = false;
			//	}
			//	/*if(pGPS->GetPlayer()->m_vpActiveQuests[i]->QuestID == NPCLabel + 1)
			//	{
			//	CGame::GetInstance()->ChangeState(WinMenuState::GetInstance());
			//	}*/
			//}
			//if(questEmpty)
			//{
			//	pGPS->GetPlayer()->AddQuest(test_quest_obj->AllQuests[NPCLabel]);
			//	AllQuestsAvail[NPCLabel] = false;
			//}
		}
		if(pDI->KeyPressed(DIK_RETURN) || pDI->JoystickButtonPressed(0,0))
		{
			bool questEmpty = true;
			pGPS->m_pHUD->SetTarget(pGPS->hospitalX,pGPS->hospitalY);


			for(unsigned int i = 0; i < pGPS->GetPlayer()->m_vpActiveQuests.size(); i++)
			{
				if(pGPS->GetPlayer()->m_vpActiveQuests[i]->QuestID == NPCLabel || pGPS->GetPlayer()->m_vpActiveQuests[i] == nullptr )
				{
					questEmpty = false;
					AllQuestsAvail[NPCLabel] = false;
				}
				/*if(pGPS->GetPlayer()->m_vpActiveQuests[i]->QuestID == NPCLabel + 1)
				{
				CGame::GetInstance()->ChangeState(WinMenuState::GetInstance());
				}*/
			}
			if(questEmpty)
			{
				pGPS->GetPlayer()->AddQuest(test_quest_obj->AllQuests[NPCLabel]);
				AllQuestsAvail[NPCLabel] = false;
			}

			for(unsigned int i = 0; i < pGPS->GetPlayer()->m_vpActiveQuests.size(); i++)
			{
				if(pGPS->GetPlayer()->m_vpActiveQuests[i]->QuestID == NPCLabel - 1)
				{
					// temp for first playable
					// Change this to put in next level and complete the quest 
					//CGame::GetInstance()->ChangeState(WinMenuState::GetInstance());
					vector<Quest_Struct*>::iterator temp = pGPS->GetPlayer()->m_vpActiveQuests.begin()+i;					
					//pGPS->GetPlayer()->completedQuest++;
					pGPS->GetPlayer()->m_vpFinishedQuests.push_back(pGPS->GetPlayer()->m_vpActiveQuests[i]);
					if(pGPS->GetPlayer()->m_vpActiveQuests[i+1]->QuestID == pGPS->GetPlayer()->m_vpActiveQuests[i]->QuestID + 1)
						pGPS->GetPlayer()->m_vpFinishedQuests.push_back(pGPS->GetPlayer()->m_vpActiveQuests[i+1]);
					pGPS->GetPlayer()->m_vpActiveQuests.erase(temp + 1);
					pGPS->GetPlayer()->m_vpActiveQuests.erase(temp);
					
				}
			}
		}
		if(GamePlayState::GetInstance()->GetWinLose() == false)
			CGame::GetInstance()->ChangeState(LoseMenuState::GetInstance());


	}
	else
		showQuest = false;

	BaseCharacter::Update(fElapsedTime);

	if((GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT) && m_playerAnim.curAnimation != 1 && GetVelY() == 0)
	{
		m_playerAnim.curAnimation = 1;
		m_playerAnim.curFrame = 0;
		m_playerAnim.fTime = 0;
	}
	else if((GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT) && m_playerAnim.curAnimation != 5 && GetVelY() < 0)
	{
		m_playerAnim.curAnimation = 5;
		m_playerAnim.curFrame = 0;
		m_playerAnim.fTime = 0;
	}
	else if((GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT) && m_playerAnim.curAnimation != 0 && GetVelY() == 0)
	{
		m_playerAnim.curAnimation = 0;
		m_playerAnim.curFrame = 0;
		m_playerAnim.fTime = 0;
	}
	else if((GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT) && m_playerAnim.curAnimation != 4 && GetVelY() > 0)
	{
		m_playerAnim.curAnimation = 4;
		m_playerAnim.curFrame = 0;
		m_playerAnim.fTime = 0;
	}
	else if(GetDirection() == DIRE_RIGHT && m_playerAnim.curAnimation != 2 && GetVelX() == 0)
	{
		m_playerAnim.curAnimation = 2;
		m_playerAnim.curFrame = 0;
		m_playerAnim.fTime = 0;
	}
	else if(GetDirection() == DIRE_RIGHT && m_playerAnim.curAnimation != 6 && GetVelX() > 0)
	{
		m_playerAnim.curAnimation = 6;
		m_playerAnim.curFrame = 0;
		m_playerAnim.fTime = 0;
	}
	else if(GetDirection() == DIRE_LEFT  && m_playerAnim.curAnimation != 3 && GetVelX() == 0)
	{
		m_playerAnim.curAnimation = 3;
		m_playerAnim.curFrame = 0;
		m_playerAnim.fTime = 0;
	}
	else if(GetDirection() == DIRE_LEFT  && m_playerAnim.curAnimation != 7 && GetVelX() < 0)
	{
		m_playerAnim.curAnimation = 7;
		m_playerAnim.curFrame = 0;
		m_playerAnim.fTime = 0;
	}

	//Updating the NPC's frame and timer for animations
	Animation* thisAnim = ViewManager::GetInstance()->GetAnimation(m_playerAnim.curAnimID);
	m_playerAnim.fTime += fElapsedTime;

	if(m_playerAnim.fTime >= thisAnim->frames[m_playerAnim.curAnimation][m_playerAnim.curFrame].duration)
	{
		m_playerAnim.fTime -= thisAnim->frames[m_playerAnim.curAnimation][m_playerAnim.curFrame].duration;
		m_playerAnim.curFrame++;
		if(m_playerAnim.curFrame < (int)thisAnim->frames[m_playerAnim.curAnimation].size())
		{
			if(strcmp(thisAnim->frames[m_playerAnim.curAnimation][m_playerAnim.curFrame].eventMsg,"none") != 0)
				EventSystem::GetInstance()->SendEvent(thisAnim->frames[m_playerAnim.curAnimation][m_playerAnim.curFrame].eventMsg, this);
		}
		if((m_playerAnim.curFrame == thisAnim->frames[m_playerAnim.curAnimation].size()) && thisAnim->looping[m_playerAnim.curAnimation])
			m_playerAnim.curFrame = 0;
		else if(m_playerAnim.curFrame == thisAnim->frames[m_playerAnim.curAnimation].size() && !thisAnim->looping[m_playerAnim.curAnimation])
			m_playerAnim.curFrame--;
	}
}

void NPC::Render() 
{
	// Render this NPC
	//ViewManager* pVM = ViewManager::GetInstance();
	pVM->DrawAnimation(&m_playerAnim, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2  ,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight(), 1.5f, 1.5f);

	pVM->GetSprite()->Flush();
	//RECT reRect = {long(GetPosX() - GamePlayState::GetInstance()->GetCamera().x), long(GetPosY() - GamePlayState::GetInstance()->GetCamera().y), long(reRect.left+GetWidth()), long(reRect.top + GetHeight())};

	//pVM->DrawRect(reRect, 0, 255, 0);



	//pVM->DrawRect(GetRect(), 0, 255, 0);



	//char buffer[15];
	//_itoa_s(double(distance), buffer, 10);
	//pVM->DrawFont(temp_font_id,buffer,600,200);
	// left top right bottom
	BaseCharacter::Render();

}

void NPC::RenderQuests(void)
{
	RECT questBox;
	questBox.left = 0;
	questBox.top = CGame::GetInstance()->GetScreenHeight() - 100;
	questBox.right = CGame::GetInstance()->GetScreenWidth();
	questBox.bottom = CGame::GetInstance()->GetScreenHeight();
	RECT src_Rect = {0,200,800,300};

	// Quest starts
	
	if(showQuest == true && NPCLabel == 0 && AllQuestsAvail[0] == true )
		{  
			//pVM->DrawRect(questBox,255,255,255);
			pVM->DrawStaticTexture(QuestBoxID,(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+0,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f),0.9f,1.0f,&src_Rect);
			pVM->DrawFont(temp_font_id,(char*)test_quest_obj->AllQuests[NPCLabel]->QuestBody.c_str(),(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+20,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f)+20,0.6f,0.6f,0,0,0,D3DCOLOR_XRGB(255,0,0));
		}
	if(showQuest == true && NPCLabel == 2 && AllQuestsAvail[2] == true)
		{  
			//pVM->DrawRect(questBox,255,255,255);
			pVM->DrawStaticTexture(QuestBoxID,(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+0,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f),0.9f,1.0f,&src_Rect);
			pVM->DrawFont(temp_font_id,(char*)test_quest_obj->AllQuests[NPCLabel]->QuestBody.c_str(),(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+20,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f)+20,0.6f,0.6f,0,0,0,D3DCOLOR_XRGB(255,0,0));
		}
	if(showQuest == true && NPCLabel == 4 && AllQuestsAvail[4] == true)
		{  
			//pVM->DrawRect(questBox,255,255,255);
			pVM->DrawStaticTexture(QuestBoxID,(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+0,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f),0.9f,1.0f,&src_Rect);
			pVM->DrawFont(temp_font_id,(char*)test_quest_obj->AllQuests[NPCLabel]->QuestBody.c_str(),(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+20,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f)+20,0.6f,0.6f,0,0,0,D3DCOLOR_XRGB(255,0,0));
		}
	if(showQuest == true && NPCLabel == 6 && AllQuestsAvail[6] == true)
		{  
			//pVM->DrawRect(questBox,255,255,255);
			pVM->DrawStaticTexture(QuestBoxID,(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+0,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f),0.9f,1.0f,&src_Rect);
			pVM->DrawFont(temp_font_id,(char*)test_quest_obj->AllQuests[NPCLabel]->QuestBody.c_str(),(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+20,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f)+20,0.6f,0.6f,0,0,0,D3DCOLOR_XRGB(255,0,0));
		}
	if(showQuest == true && NPCLabel == 8 && AllQuestsAvail[8] == true)
		{  
			//pVM->DrawRect(questBox,255,255,255);
			pVM->DrawStaticTexture(QuestBoxID,(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+0,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f),0.9f,1.0f,&src_Rect);
			pVM->DrawFont(temp_font_id,(char*)test_quest_obj->AllQuests[NPCLabel]->QuestBody.c_str(),(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+20,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f)+20,0.6f,0.6f,0,0,0,D3DCOLOR_XRGB(255,0,0));
		}
	
	// Quest ends
	for(unsigned int i = 0;  i < pGPS->GetPlayer()->m_vpActiveQuests.size();i++)
	{
		
		if(showQuest == true && NPCLabel == 1 && pGPS->GetPlayer()->m_vpActiveQuests[i]->QuestID == 0)
		{  
			//pVM->DrawRect(questBox,255,255,255);
			pVM->DrawStaticTexture(QuestBoxID,(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+0,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f),0.9f,1.0f,&src_Rect);
			pVM->DrawFont(temp_font_id,(char*)test_quest_obj->AllQuests[NPCLabel]->QuestBody.c_str(),(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+20,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f)+20,0.6f,0.6f,0,0,0,D3DCOLOR_XRGB(255,0,0));
		}
		if(showQuest == true && NPCLabel == 3 && pGPS->GetPlayer()->m_vpActiveQuests[i]->QuestID == 2 && pGPS->GetPlayer()->questCounter == 10)
		{  
			//pVM->DrawRect(questBox,255,255,255);
			pVM->DrawStaticTexture(QuestBoxID,(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+0,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f),0.9f,1.0f,&src_Rect);
			pVM->DrawFont(temp_font_id,(char*)test_quest_obj->AllQuests[NPCLabel]->QuestBody.c_str(),(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+20,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f)+20,0.6f,0.6f,0,0,0,D3DCOLOR_XRGB(255,0,0));
		}
		if(showQuest == true && NPCLabel == 5 && pGPS->GetPlayer()->m_vpActiveQuests[i]->QuestID == 4)
		{  
			//pVM->DrawRect(questBox,255,255,255);
			pVM->DrawStaticTexture(QuestBoxID,(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+0,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f),0.9f,1.0f,&src_Rect);
			pVM->DrawFont(temp_font_id,(char*)test_quest_obj->AllQuests[NPCLabel]->QuestBody.c_str(),(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+20,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f)+20,0.6f,0.6f,0,0,0,D3DCOLOR_XRGB(255,0,0));
		}
		if(showQuest == true && NPCLabel == 7 && pGPS->GetPlayer()->m_vpActiveQuests[i]->QuestID == 6)
		{  
			//pVM->DrawRect(questBox,255,255,255);
			pVM->DrawStaticTexture(QuestBoxID,(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+0,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f),0.9f,1.0f,&src_Rect);
			pVM->DrawFont(temp_font_id,(char*)test_quest_obj->AllQuests[NPCLabel]->QuestBody.c_str(),(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+20,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f)+20,0.6f,0.6f,0,0,0,D3DCOLOR_XRGB(255,0,0));
		}
		if(showQuest == true && NPCLabel == 9 && pGPS->GetPlayer()->m_vpActiveQuests[i]->QuestID == 8 && pGPS->GetPlayer()->m_bHasMedicine == true)
		{  
			//pVM->DrawRect(questBox,255,255,255);
			pVM->DrawStaticTexture(QuestBoxID,(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+0,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f),0.9f,1.0f,&src_Rect);
			pVM->DrawFont(temp_font_id,(char*)test_quest_obj->AllQuests[NPCLabel]->QuestBody.c_str(),(float(CGame::GetInstance()->GetScreenWidth())*0.05f)+20,(CGame::GetInstance()->GetScreenHeight() - 100.0f)-(float(CGame::GetInstance()->GetScreenHeight())*0.05f)+20,0.6f,0.6f,0,0,0,D3DCOLOR_XRGB(255,0,0));
		}
		
		
	}
}

void NPC::SetQuest(int q_id) 
{
	sz_QuestTitle = test_quest_obj->AllQuests[q_id - 1]->QuestTitle;
	sz_QuestBody = test_quest_obj->AllQuests[q_id - 1]->QuestBody;
}

bool NPC::CheckCollision(IObjects* pBase) 
{
	return BaseCharacter::CheckCollision(pBase);
}
void NPC::ShowDialog()
{

}
