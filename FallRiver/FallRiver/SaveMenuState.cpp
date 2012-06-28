#include "SaveMenuState.h"
#include "XMLManager.h"
#include "DirectInput.h"
#include "CGame.h"
#include "GamePlayState.h"
#include "ViewManager.h"

SaveMenuState* SaveMenuState::GetInstance()
{
	static SaveMenuState m_sInstance;

	return &m_sInstance;
}

SaveMenuState::SaveMenuState(void)
{
	m_pDI = nullptr;
	m_pVM = nullptr;
	m_nCursPosY = 0;
	m_nCursPosX = 0;
	m_nFontID	= 0;
	m_bSure = false;
	m_bCheck = false;
}


SaveMenuState::~SaveMenuState(void)
{
}

void SaveMenuState::Enter()
{
	m_pDI = DirectInput::GetInstance();
	m_pVM = ViewManager::GetInstance();

	m_nFontID = m_pVM->RegisterFont("resource/graphics/FallRiver_0.png");

	m_nCursPosY = 200;
	m_nCursPosX = 280;
}

void SaveMenuState::Exit()
{
	m_pDI = nullptr;
	m_pVM = nullptr;
	m_nCursPosY = 0;
	m_nCursPosX = 0;
	m_bSure = false;
	m_bCheck = false;
}

bool SaveMenuState::Input()
{
	if( m_pDI->KeyPressed(DIK_DOWNARROW) )
	{
		m_nCursPosY += 50;
		if( m_nCursPosY == 350 )
			m_nCursPosY = 400;
		else if( m_nCursPosY > 400 )
			m_nCursPosY = 200;
	}
	else if( m_pDI->KeyPressed(DIK_UPARROW) )
	{
		m_nCursPosY -= 50;
		if( m_nCursPosY == 350 )
			m_nCursPosY = 300;
		else if( m_nCursPosY < 200 )
			m_nCursPosY = 400;
	}

	if( m_pDI->KeyPressed(DIK_RIGHTARROW) && m_bCheck )
	{
		m_nCursPosX += 100;
		if( m_nCursPosX > 380 )
			m_nCursPosX = 280;
	}
	else if( m_pDI->KeyPressed(DIK_LEFTARROW) && m_bCheck )
	{
		m_nCursPosX -= 100;
		if( m_nCursPosX < 280 )
			m_nCursPosX = 380;
	}

	if(m_pDI->KeyPressed(DIK_RETURN) )
	{
		if(m_bCheck)
		{
			if(m_nCursPosX == 280)
			{
				m_bSure = true;
				m_bCheck = false;
			}
			else if(m_nCursPosX == 380)
			{
				m_bCheck = false;
				m_bSure = false;
				return true;
			}
		}

		if( m_nCursPosY == 200 )
		{
			if( XMLManager::GetInstance()->CheckSlot("save1.xml") && !m_bSure ) 
				m_bCheck = true;
			else
			{
				XMLManager::GetInstance()->SaveProgress("save1.xml", *GamePlayState::GetInstance()->GetPlayer());
				CGame::GetInstance()->RemoveState();
				m_bSure = false;
			}
		}
		else if(m_nCursPosY == 250)
		{
			if( XMLManager::GetInstance()->CheckSlot("save2.xml") && !m_bSure ) 
				m_bCheck = true;
			else
			{
				XMLManager::GetInstance()->SaveProgress("save2.xml", *GamePlayState::GetInstance()->GetPlayer());
				CGame::GetInstance()->RemoveState();
			}
		}
		else if( m_nCursPosY == 300 )
		{
			if( XMLManager::GetInstance()->CheckSlot("save3.xml") && !m_bSure ) 
				m_bCheck = true;
			else
			{
				XMLManager::GetInstance()->SaveProgress("save3.xml", *GamePlayState::GetInstance()->GetPlayer());
				CGame::GetInstance()->RemoveState();
			}
		}
		else if( m_nCursPosY == 400 )
			CGame::GetInstance()->RemoveState();

		return true;
	}

	if(m_pDI->KeyDown(DIK_ESCAPE) && !m_bCheck )
		CGame::GetInstance()->RemoveState();

	return true;
}

void SaveMenuState::Update(float fElapsedTime)
{

}

void SaveMenuState::Render()
{

	m_pVM->GetSprite()->Flush();
	m_pVM->Clear();

	m_pVM->DrawFont(m_nFontID, "Save Progress", 20, 20);

	if( m_bCheck )
	{
		RECT cRect = {200, 200, 600, 350};

		m_pVM->DrawRect(cRect, 0, 100, 100, 100);

		m_pVM->DrawFont(m_nFontID, "You are about to overwrite a previous save...", 200, 200, 0.5f, 0.5f);
		m_pVM->DrawFont(m_nFontID, "Do you want to continue", 260, 220, 0.5f, 0.5f);
		m_pVM->DrawFont(m_nFontID, "Yes", 300, 280, 0.5f, 0.5f);
		m_pVM->DrawFont(m_nFontID, "No", 400, 280, 0.5f, 0.5f);

		RECT xRect = {m_nCursPosX, 280, m_nCursPosX+10, 290};

		m_pVM->DrawRect(xRect, 0, 255, 255, 100);
	}
	else
	{
		m_pVM->DrawFont(m_nFontID, "Save 1", 250, 200);
		m_pVM->DrawFont(m_nFontID, "Save 2", 250, 250);
		m_pVM->DrawFont(m_nFontID, "Save 3", 250, 300);
		m_pVM->DrawFont(m_nFontID, "Exit Game", 300, 400);

		RECT rRect = {225, m_nCursPosY, 235, m_nCursPosY+10};

		m_pVM->DrawRect(rRect, 0, 255, 255, 100);
	}
}
