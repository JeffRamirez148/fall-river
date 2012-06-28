//#include <Windows.h>
//using namespace std;

#include "HUD.h"
#include "GamePlayState.h"
#include "ViewManager.h"
#include "Player.h"
#include "Weapon.h"

HUD::HUD() 
{
	m_nFontID = ViewManager::GetInstance()->RegisterFont("resource/graphics/FallRiver_0.png");

}

HUD::~HUD() 
{
}

void HUD::Update(float aTime)
{


	//this->
}

void HUD::Render() 
{

	ViewManager* pVM = ViewManager::GetInstance();

	//pVM->DrawRect(GetRect(), 0, 0, 255);
	char szName[100] = {};
	
	TCHAR buffer[ 100 ];
	//int playerScore = 15;
	_stprintf_s( buffer, 100, _T("Health - %i"), GamePlayState::GetInstance()->GetPlayer()->GetHealth() );

	wcstombs_s( nullptr, szName, 100, buffer, _TRUNCATE );
	
	pVM->DrawFont(m_nFontID,szName,0,0);

	_stprintf_s( buffer, 100, _T("Lives - %i"),  GamePlayState::GetInstance()->GetPlayer()->GetLives() );

	wcstombs_s( nullptr, szName, 100, buffer, _TRUNCATE );

	pVM->DrawFont(m_nFontID,szName,0,20);

	_stprintf_s( buffer, 100, _T("Clip - %i"),  GamePlayState::GetInstance()->GetPlayer()->GetClip() );

	wcstombs_s( nullptr, szName, 100, buffer, _TRUNCATE );

	pVM->DrawFont(m_nFontID,szName,0,40);

	_stprintf_s( buffer, 100, _T("Ammo - %i"),  GamePlayState::GetInstance()->GetPlayer()->GetAmmo() );

	wcstombs_s( nullptr, szName, 100, buffer, _TRUNCATE );

	pVM->DrawFont(m_nFontID,szName,0,60);

	_stprintf_s( buffer, 100, _T("Weapon - %i"),  GamePlayState::GetInstance()->GetPlayer()->GetWeaponType() );

	wcstombs_s( nullptr, szName, 100, buffer, _TRUNCATE );

	pVM->DrawFont(m_nFontID,szName,0,80);

}

void HUD::Input() 
{
}

