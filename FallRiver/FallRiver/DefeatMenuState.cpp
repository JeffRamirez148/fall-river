#include <Windows.h>
using namespace std;

#include "DefeatMenuState.h"
#include "AudioManager.h"
#include "ViewManager.h"
#include "DirectInput.h"
#include "XMLManager.h"
#include "IMenuState.h"

DefeatMenuState* DefeatMenuState::GetInstance() 
{
	static DefeatMenuState s_Instance;

	return &s_Instance;
}

void DefeatMenuState::Enter() 
{
}

void DefeatMenuState::ReEnter()
{

}

void DefeatMenuState::Exit() 
{
}

bool DefeatMenuState::Input()
{
	return true;
}

void DefeatMenuState::Update(float fElapsedTime)
{
}

void DefeatMenuState::Render() 
{
}

