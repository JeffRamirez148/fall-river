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

	this->m_fHealth = GamePlayState::GetInstance()->GetPlayer()->GetHealth();
	this->m_nAmmo = GamePlayState::GetInstance()->GetPlayer()->GetAmmo();
	this->m_nClip = GamePlayState::GetInstance()->GetPlayer()->GetClip();
	this->m_nWeapon = GamePlayState::GetInstance()->GetPlayer()->GetWeaponType();
	this->m_nLives = GamePlayState::GetInstance()->GetPlayer()->GetLives();
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
	//pVM->DrawTextW("hello",GamePlayState::GetInstance()->GetCamera().x,GamePlayState::GetInstance()->GetCamera().y,255,255,255);

	//m_pVM->DrawText(szName,0,0,255,255,255);
	pVM->DrawFont(m_nFontID,szName,0,0);

	//char szName1[100] = {};
	//
	//TCHAR buffer1[ 100 ];
	//int playerScore = 15;
	_stprintf_s( buffer, 100, _T("Lives - %i"), m_nLives );

	wcstombs_s( nullptr, szName, 100, buffer, _TRUNCATE );

	pVM->DrawFont(m_nFontID,szName,0,20);

}

void HUD::Input() 
{
}

