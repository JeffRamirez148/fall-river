//#include <Windows.h>
//using namespace std;

#include "HUD.h"
#include "GamePlayState.h"
#include "ViewManager.h"
#include "Player.h"
#include "Weapon.h"
#include "AudioManager.h"
#include "sound.h"

//#define AniTime .05f

HUD::HUD() 
{
	m_nFontID = ViewManager::GetInstance()->RegisterFont("resource/graphics/FallRiver_0.png");
	m_nHudID = -1;
	m_fTime = 0;
	m_fAniSpeed = 0;
	m_ftest = 0;
	healthID = AudioManager::GetInstance()->RegisterSound("resource/Sounds/ECG.wav");
	FMOD_VECTOR sound1 = { 0, 0, 0 };
	AudioManager::GetInstance()->setSoundVel(healthID, sound1);
	sound1.x = GamePlayState::GetInstance()->GetPlayer()->GetPosX();
	sound1.y = GamePlayState::GetInstance()->GetPlayer()->GetPosY();
	AudioManager::GetInstance()->setSoundPos(healthID, sound1);
	AudioManager::GetInstance()->setSoundLooping(healthID, false);

}

HUD::~HUD() 
{
}

void HUD::Update(float aTime)
{
	FMOD_VECTOR sound1 = { GamePlayState::GetInstance()->GetPlayer()->GetPosX(), GamePlayState::GetInstance()->GetPlayer()->GetPosY(), 0};
	AudioManager::GetInstance()->setSoundPos(healthID, sound1);

	m_fTime += aTime;
	//m_ftest += aTime;
	/*
	if( m_ftest > 10 )
	{
		m_ftest = 0;
	}
	*/
	if( m_fTime > 29*m_fAniSpeed )
	{
		m_fTime = 0;
	}
}

void HUD::Render() 
{
	

	ViewManager* pVM = ViewManager::GetInstance();

	
	RECT test;
	test.top = 16;
	test.right = 270;
	test.left = 18;
	test.bottom = 264;

	RECT test1;
	test1.top = 316;
	test1.right = 676;
	test1.left = 376;
	test1.bottom = 453;

	RECT test2;
	test2.top = 818;
	test2.right = 691;
	test2.left = 410;
	test2.bottom = 954;

	RECT test3;
	test3.top = 64;
	test3.right = 512;
	test3.left = 115;
	test3.bottom = 256;

	RECT test4;
	test4.top = 353;
	test4.right = 824;
	test4.left = 724;
	test4.bottom = 417;


	pVM->DrawStaticTexture(m_nHudID,0,0,0.5f,0.5f,&test,0,0,0,D3DCOLOR_ARGB(180,255,255,255));
	pVM->DrawStaticTexture(m_nHudID,125,65,0.5f,0.5f,&test1,0,0,0,D3DCOLOR_ARGB(180,255,255,255));
	//pVM->DrawStaticTexture(m_nHudID,270,0,0.5f,0.5f,&test1,0,0,0,D3DCOLOR_ARGB(180,255,255,255));

	//pVM->DrawStaticTexture(m_nHudID,155,94,0.5f,0.5f,&test4,80,50,GamePlayState::GetInstance()->GetPlayer()->battery*0.021f,D3DCOLOR_ARGB(180,255,255,255));
	pVM->DrawStaticTexture(m_nHudID,155,94,0.5f,0.5f,&test4,80,50,GamePlayState::GetInstance()->GetPlayer()->battery*0.021f,D3DCOLOR_ARGB(180,255,255,255));

	//pVM->DrawStaticTexture(m_nHudID,400,400,0.5f,0.5f,&test4,0,0,0,D3DCOLOR_ARGB(180,255,255,255));

	pVM->DrawStaticTexture(m_nHudID,125,0,0.5f,0.5f,&test2,0,0,0,D3DCOLOR_ARGB(180,255,255,255));


	if( m_fTime < 0*m_fAniSpeed  || m_fTime > 0*m_fAniSpeed && m_fTime < 1*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[0],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[0],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[0],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 1*m_fAniSpeed && m_fTime < 2*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[1],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[1],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[1],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 2*m_fAniSpeed && m_fTime < 3*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[2],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[2],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[2],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 3*m_fAniSpeed && m_fTime < 4*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[3],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[3],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[3],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 4*m_fAniSpeed && m_fTime < 5*m_fAniSpeed )
	{
				AudioManager::GetInstance()->GetSoundChannel(healthID)->stop();
		AudioManager::GetInstance()->playSound(healthID);
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[4],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[4],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[4],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 5*m_fAniSpeed && m_fTime < 6*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[5],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[5],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[5],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 6*m_fAniSpeed && m_fTime < 7*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[6],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[6],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[6],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 7*m_fAniSpeed && m_fTime < 8*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[7],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[7],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[7],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 8*m_fAniSpeed && m_fTime < 9*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[8],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[8],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[8],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 9*m_fAniSpeed && m_fTime < 10*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[9],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[9],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[9],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 10*m_fAniSpeed && m_fTime < 11*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[10],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[10],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[10],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 11*m_fAniSpeed && m_fTime < 12*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[11],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[11],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[11],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 12*m_fAniSpeed && m_fTime < 13*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[12],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[12],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[12],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 13*m_fAniSpeed && m_fTime < 14*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[13],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[13],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[13],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 14*m_fAniSpeed && m_fTime < 15*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[14],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[14],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[14],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 15*m_fAniSpeed && m_fTime < 16*m_fAniSpeed )
	{
		AudioManager::GetInstance()->GetSoundChannel(healthID)->stop();
		AudioManager::GetInstance()->playSound(healthID);
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[15],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[15],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[15],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 16*m_fAniSpeed && m_fTime < 17*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[16],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[16],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[16],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 17*m_fAniSpeed && m_fTime < 18*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[17],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[17],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[17],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 18*m_fAniSpeed && m_fTime < 19*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[18],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[18],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[18],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 19*m_fAniSpeed && m_fTime < 20*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[19],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[19],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[19],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 20*m_fAniSpeed && m_fTime < 21*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[20],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[20],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[20],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 21*m_fAniSpeed && m_fTime < 22*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[21],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[21],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[21],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 22*m_fAniSpeed && m_fTime < 23*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[22],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[22],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[22],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 23*m_fAniSpeed && m_fTime < 24*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[23],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[23],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[23],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 24*m_fAniSpeed && m_fTime < 25*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[24],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[24],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[24],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 25*m_fAniSpeed && m_fTime < 26*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[25],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[25],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[25],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 26*m_fAniSpeed && m_fTime < 27*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[26],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[26],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[26],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	else if( m_fTime > 27*m_fAniSpeed && m_fTime < 28*m_fAniSpeed )
	{
		if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[27],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		}
		else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
		{
			pVM->DrawStaticTexture(m_vFrameIDs[27],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		}
		else
		{
			pVM->DrawStaticTexture(m_vFrameIDs[27],125,0,0.5f,0.5f,&test3,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		}
	}
	

	char szName[100] = {}; 
	
	TCHAR buffer[ 100 ];
	int x = GamePlayState::GetInstance()->GetPlayer()->GetHealth() ;
	if( x > 0 )
	{
		_stprintf_s( buffer, 100, _T("%i"), GamePlayState::GetInstance()->GetPlayer()->GetHealth() );
	}
	else
	{
		_stprintf_s( buffer, 100, _T("%i"), 0);
	}


	wcstombs_s( nullptr, szName, 100, buffer, _TRUNCATE );
	
	if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 50 )
	{
		m_fAniSpeed = .07f;
		pVM->DrawFont(m_nFontID,szName,210,0,1,1,0,0,0,D3DCOLOR_ARGB(180,0,255,0));
		AudioManager::GetInstance()->GetSound(healthID)->noise->setMusicSpeed( 1 );
	}
	else if( GamePlayState::GetInstance()->GetPlayer()->GetHealth() > 25 )
	{
		m_fAniSpeed = .05f;
		pVM->DrawFont(m_nFontID,szName,210,0,1,1,0,0,0,D3DCOLOR_ARGB(180,255,255,0));
		AudioManager::GetInstance()->GetSound(healthID)->noise->setMusicSpeed( 2 );
	}
	else
	{
		m_fAniSpeed = .02f;
		pVM->DrawFont(m_nFontID,szName,210,0,1,1,0,0,0,D3DCOLOR_ARGB(180,255,0,0));
		AudioManager::GetInstance()->GetSound(healthID)->noise->setMusicSpeed( 4 );
	}
	


}

void HUD::Input() 
{
}

