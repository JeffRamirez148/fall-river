#include <Windows.h>
using namespace std;

#include "MainMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "DirectInput.h"
#include "XMLManager.h"
#include "IMenuState.h"

void MainMenuState::Enter() 
{
}

void MainMenuState::Exit() 
{
}

bool MainMenuState::Input() 
{
	return true;
}

void MainMenuState::Update(float fElapsedTime) 
{
}

void MainMenuState::Render() 
{
}

MainMenuState* MainMenuState::GetInstance() 
{
	static MainMenuState s_Instance;

	return &s_Instance;
}

