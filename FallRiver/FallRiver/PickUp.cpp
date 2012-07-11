#include "PickUp.h"
#include "DestroyPickUp.h"
#include "DirectInput.h"
#include "AudioManager.h"
#include "GamePlayState.h"
#include "Player.h"

PickUp::PickUp()
{
	m_nObjectType = OBJ_PICKUP;
	audio = AudioManager::GetInstance();
	ammoID = audio->RegisterSound("resource/Sounds/reload.wav");
	batteriesID = audio->RegisterSound("resource/Sounds/PowerUpBattery.wav");
	medicineID = audio->RegisterSound("resource/Sounds/pillBottle.mp3");
	healthID = audio->RegisterSound("resource/Sounds/PowerUpHealth.wav");

	FMOD_VECTOR sound1 = { 0, 0, 0 };
	AudioManager::GetInstance()->setSoundVel(healthID, sound1);
	AudioManager::GetInstance()->setSoundVel(medicineID, sound1);
	AudioManager::GetInstance()->setSoundVel(batteriesID, sound1);
	AudioManager::GetInstance()->setSoundVel(ammoID, sound1);


	sound1.x = GamePlayState::GetInstance()->GetPlayer()->GetPosX();
	sound1.y = GamePlayState::GetInstance()->GetPlayer()->GetPosY();

	AudioManager::GetInstance()->setSoundPos(healthID, sound1);
	AudioManager::GetInstance()->setSoundLooping(healthID, false);
	AudioManager::GetInstance()->setSoundPos(medicineID, sound1);
	AudioManager::GetInstance()->setSoundLooping(medicineID, false);
	AudioManager::GetInstance()->setSoundPos(batteriesID, sound1);
	AudioManager::GetInstance()->setSoundLooping(batteriesID, false);
	AudioManager::GetInstance()->setSoundPos(ammoID, sound1);
	AudioManager::GetInstance()->setSoundLooping(ammoID, false);
}

PickUp::~PickUp()
{

}

void PickUp::Update(float fElapsedTime)
{
	FMOD_VECTOR sound1 = { GamePlayState::GetInstance()->GetPlayer()->GetPosX(), GamePlayState::GetInstance()->GetPlayer()->GetPosY(), 0};
	AudioManager::GetInstance()->setSoundPos(healthID, sound1);
	AudioManager::GetInstance()->setSoundPos(medicineID, sound1);
	AudioManager::GetInstance()->setSoundPos(batteriesID, sound1);
	AudioManager::GetInstance()->setSoundPos(ammoID, sound1);
}

void PickUp::Render() 
{
}

RECT PickUp::GetRect()
{
	RECT cRect = {long(GetPosX()), long(GetPosY()), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight()) };
	return cRect;
}

bool PickUp::CheckCollision(BaseObject* pBase)
{
	RECT cRect;
	if( IntersectRect( &cRect, &GetRect(), &pBase->GetRect() ) == false  )
		return false;
	return true;
}
