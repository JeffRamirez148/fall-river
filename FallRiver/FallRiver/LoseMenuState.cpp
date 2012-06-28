#include <Windows.h>

#include "LoseMenuState.h"
#include "WinMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "DirectInput.h"
#include "XMLManager.h"
#include "IMenuState.h"

using namespace std;

WinMenuState* LoseMenuState::GetInstance()
{
	static WinMenuState s_Instance;

	return &s_Instance;
}
void LoseMenuState::Enter()
{
	pVM	= ViewManager::GetInstance();
	pDI	= DirectInput::GetInstance();
	pAM	= AudioManager::GetInstance();

	youLose_ID = pVM->RegisterTexture("resource/graphics/youLose.png");

}
void LoseMenuState::Exit()
{
	pVM	= nullptr;
	pDI	= nullptr;
	pAM	= nullptr;
}
bool LoseMenuState::Input()
{
	if( pDI->KeyPressed(DIK_DOWNARROW) )
	{
	}
	if(pDI->KeyPressed(DIK_RETURN))
	{

	}
	return true;
}
void LoseMenuState::Update(float aFElapsedTime)
{

}
void LoseMenuState::Render()
{

}
	