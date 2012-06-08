#include <Windows.h>
using namespace std;

#include "PauseMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "XMLManager.h"
#include "DirectInput.h"
#include "IMenuState.h"

PauseMenuState* PauseMenuState::GetInstance() 
{
	static PauseMenuState stuff;
	return &stuff;
}

void PauseMenuState::Enter() 
{
	
}

void PauseMenuState::Exit()
{
	
}

bool PauseMenuState::Input() 
{
	return true;
}

void PauseMenuState::Update(float fElapsedTime) 
{
	
}

void PauseMenuState::Render() 
{
	
}

