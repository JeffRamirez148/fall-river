#include <Windows.h>

#include "CGame.h"
#include "DirectInput.h"
#include "IMenuState.h"

CGame* CGame::GetInstance()
{
	static CGame s_Instance;

	return &s_Instance;
}

CGame::CGame() 
{
}

bool CGame::Input() 
{
	return true;
}

void CGame::Update() 
{
}

void CGame::Render() 
{
}


void CGame::Initialize(HWND HWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bIsWindowed)
{
	
}

bool CGame::Main()
{
	return true;
}

void CGame::ShutDown() 
{

}

void CGame::ChangeState(IGameState* pNewState) 
{
}

void CGame::SetWindowed(bool Is) 
{
}

bool CGame::IsWindowed()
{
	return true;
}

