#include <Windows.h>
using namespace std;

#include "OptionsMenuState.h"
#include "ViewManager.h"
#include "GamePlayState.h"
#include "XMLManager.h"
#include "IMenuState.h"

OptionsMenuState* OptionsMenuState::GetInstance() 
{
	static OptionsMenuState stuff;
	return &stuff;
}

void OptionsMenuState::Enter() 
{
	
}

void OptionsMenuState::Exit() 
{
	
}

bool OptionsMenuState::Input()
{
	return true;
}

void OptionsMenuState::Update(float aFElapsedTime)
{
	
}

void OptionsMenuState::Render()
{
	
}

