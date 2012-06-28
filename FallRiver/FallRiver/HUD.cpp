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
	m_nHudID = -1;
}

HUD::~HUD() 
{
}

void HUD::Update(float aTime)
{
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

	_stprintf_s( buffer, 100, _T("Battery - %i"),  GamePlayState::GetInstance()->GetPlayer()->battery);

	wcstombs_s( nullptr, szName, 100, buffer, _TRUNCATE );

	pVM->DrawFont(m_nFontID,szName,0,100);


	/*RECT test;
	test.top = 16;
	test.right = 270;
	test.left = 18;
	test.bottom = 264;

	RECT test1;
	test1.top = 317;
	test1.right = 312;
	test1.left = 18;
	test1.bottom = 452;

	RECT test2;
	test2.top = 654;
	test2.right = 691;
	test2.left = 410;
	test2.bottom = 790;


	pVM->DrawStaticTexture(m_nHudID,0,0,0.5f,0.5f,&test);
	pVM->DrawStaticTexture(m_nHudID,200,200,0.5f,0.5f,&test1);
	pVM->DrawStaticTexture(m_nHudID,400,400,0.5f,0.5f,&test2);



*/
}

void HUD::Input() 
{
}

