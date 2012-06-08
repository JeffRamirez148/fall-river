#include <Windows.h>
using namespace std;

#include "CreditsMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "DirectInput.h"
#include "IMenuState.h"

CreditsMenuState* CreditsMenuState::GetInstance()
{
	static CreditsMenuState s_Instance;

	return &s_Instance;
}

void CreditsMenuState::Enter() 
{
}

void CreditsMenuState::Exit() 
{
}

bool CreditsMenuState::Input() 
{
	return true;
}

void CreditsMenuState::Update(float fElapsedTime) 
{
}

void CreditsMenuState::Render() 
{
}

