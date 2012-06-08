#include <Windows.h>

#include "WinMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "DirectInput.h"
#include "XMLManager.h"
#include "IMenuState.h"

void WinMenuState::Enter()
{
	
}

void WinMenuState::Exit() 
{
	
}

bool WinMenuState::Input() 
{
	return true;
}

void WinMenuState::Update(float aFElapsedTime) 
{
	
}

void WinMenuState::Render()
{
	
}

WinMenuState* WinMenuState::GetInstance() 
{
	static WinMenuState s_Instance;

	return &s_Instance;
}

