#include <Windows.h>
using namespace std;

#include "HowToPlayMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "DirectInput.h"
#include "IMenuState.h"

HowToPlayMenuState* HowToPlayMenuState::GetInstance() 
{
	static HowToPlayMenuState s_Instance;

	return &s_Instance;
}

void HowToPlayMenuState::Enter() 
{
}

void HowToPlayMenuState::Exit() 
{
}

bool HowToPlayMenuState::Input() 
{
	return true;
}

void HowToPlayMenuState::Update(float fElapsedTime) 
{
}

void HowToPlayMenuState::Render() 
{
}

