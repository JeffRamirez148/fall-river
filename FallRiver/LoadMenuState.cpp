#include <Windows.h>
using namespace std;

#include "LoadMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "XMLManager.h"
#include "DirectInput.h"
#include "IMenuState.h"

LoadMenuState* LoadMenuState::GetInstance() 
{
	static LoadMenuState s_Instance;

	return &s_Instance;
}

void LoadMenuState::Enter() 
{
}

void LoadMenuState::Exit() 
{
}

void LoadMenuState::Input() 
{
}

void LoadMenuState::Update(float fElapsedTime) 
{
}

void LoadMenuState::Render() 
{
}

