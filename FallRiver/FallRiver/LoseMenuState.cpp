#include <Windows.h>

#include "LoseMenuState.h"
#include "WinMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "DirectInput.h"
#include "XMLManager.h"
#include "IMenuState.h"

using namespace std;
WinMenuState* GetInstance()
{
	static WinMenuState s_Instance;

	return &s_Instance;
}
void Enter()
{

}
void Exit()
{

}
bool Input()
{
	return true;
}
void Update(float aFElapsedTime)
{

}
void Render()
{

}
	