#include "PauseMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "XMLManager.h"
#include "DirectInput.h"
#include "OptionsMenuState.h"
#include "SaveMenuState.h"
#include "XMLManager.h"
#include "CGame.h"
#include "MainMenuState.h"

PauseMenuState::PauseMenuState()
{
	m_pDI = nullptr;
	m_pVM = nullptr;
	m_nPauseID = -1;
	m_nCursPosY = 150;
}

PauseMenuState::~PauseMenuState()
{

}

PauseMenuState* PauseMenuState::GetInstance() 
{
	static PauseMenuState m_sInstance;

	return &m_sInstance;
}

void PauseMenuState::Enter() 
{
	m_pDI = DirectInput::GetInstance();
	m_pVM = ViewManager::GetInstance();

	m_nPauseID = m_pVM->RegisterTexture("resource/graphics/sprites_pauseMenu.png");
}

void PauseMenuState::Exit()
{
	m_pDI = nullptr;
	m_pVM = nullptr;
	m_nCursPosY = 150;
}

bool PauseMenuState::Input() 
{
	if( m_pDI->KeyPressed(DIK_DOWNARROW) )
	{
		m_nCursPosY += 50;
		if( m_nCursPosY > 300 )
			m_nCursPosY = 150;
	}
	else if( m_pDI->KeyPressed(DIK_UPARROW) )
	{
		m_nCursPosY -= 50;
		if( m_nCursPosY < 150 )
			m_nCursPosY = 300;
	}

	if(m_pDI->KeyPressed(DIK_RETURN) )
	{
		if( m_nCursPosY == 150 )
			CGame::GetInstance()->RemoveState();
		else if(m_nCursPosY == 200)
			CGame::GetInstance()->ChangeState(SaveMenuState::GetInstance());
		else if( m_nCursPosY == 250 )
			CGame::GetInstance()->ChangeState(OptionsMenuState::GetInstance());
		else if( m_nCursPosY == 300 )
		{
			CGame::GetInstance()->RemoveState(2);
			CGame::GetInstance()->ChangeState(MainMenuState::GetInstance());
		}

		return true;
	}

	if(m_pDI->KeyPressed(DIK_ESCAPE) )
		m_nCursPosY = 300;

	return true;
}

void PauseMenuState::Update(float fElapsedTime) 
{

}

void PauseMenuState::Render() 
{
	//1535
	// Do Rendering here
	RECT backRect = { 12, 12, backRect.left+1200, backRect.top+700};
	m_pVM->DrawStaticTexture(m_nPauseID, 0, 0,  0.7f, 0.9f, &backRect);

	RECT resumeRect = {1219, 13, resumeRect.left+287, resumeRect.top+44};
	RECT saveRect = { 1219, 83, saveRect.left+287, saveRect.top+44};
	RECT optionsRect = {1219, 153, optionsRect.left+287, optionsRect.top+44};
	RECT ExitRect = {1219, 223, ExitRect.left+287, ExitRect.top+44};

	if(m_nCursPosY == 150)
	{resumeRect.left = 1535; resumeRect.right = resumeRect.left+287;}
	else if(m_nCursPosY == 200)
	{saveRect.left = 1535; saveRect.right = saveRect.left+287;}
	else if(m_nCursPosY == 250)
	{optionsRect.left = 1535; optionsRect.right = optionsRect.left+287;}
	else if(m_nCursPosY == 300)
	{ExitRect.left = 1535; ExitRect.right = ExitRect.left+287;}

	m_pVM->DrawStaticTexture(m_nPauseID, 320, 200,  0.7f, 0.9f, &resumeRect);
	m_pVM->DrawStaticTexture(m_nPauseID, 330, 300,  0.7f, 0.9f, &saveRect);
	m_pVM->DrawStaticTexture(m_nPauseID, 350, 400,  0.7f, 0.9f, &optionsRect);
	m_pVM->DrawStaticTexture(m_nPauseID, 370, 500,  0.7f, 0.9f, &ExitRect);

	//RECT cRect = { 100, 100, 500, 400 };
	//RECT cursRect = { 225, m_nCursPosY, 235, m_nCursPosY+10 };
	//m_pVM->DrawRect(cRect, 100, 100, 100, 255);
	//m_pVM->DrawRect(cursRect, 255, 0, 0);

	//m_pVM->DrawTextW("Resume", 250, 150, 255, 255, 0);
	//m_pVM->DrawTextW("Save Game", 250, 200, 255, 255, 0);
	//m_pVM->DrawTextW("Optons", 250, 250, 255, 255, 0);
	//m_pVM->DrawTextW("Back To Main Menu", 250, 300, 255, 255, 0);
}

