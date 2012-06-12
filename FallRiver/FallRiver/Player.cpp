#include <Windows.h>
#include <vector>
using namespace std;

#include "Player.h"
#include "Quests.h"
#include "GamePlayState.h"
#include "Enemy.h"
#include "ObjectFactory.h"
#include "Weapon.h"
#include "Light.h"
#include "BaseCharacter.h"

Player::Player()
{
	m_nCharacterType = CHA_PLAYER;
	SetImageID(-1);
}

Player::~Player()
{

}

void Player::Update(float aFElapsedTime) 
{
	
}

void Player::Render()
{
	
}

bool Player::CheckCollision(BaseCharacter* pBase) 
{
	return true;
}

// Check if the player is still alive
bool Player::CheckLifes() {return m_bIsAlive;}

void Player::AddQuest(Quests* pQuest)
{
	// Just in case
	if(pQuest == nullptr)
		return;

	// Add the quest
	m_vpActiveQuests.push_back(pQuest);
}

void Player::AddWeapon(Weapon* pWeapon)
{
	// Just in case
	if(pWeapon == nullptr)
		return;

	// Add the weapon and make it current
	m_vpWeapons.push_back(pWeapon);
	m_currWeapon = pWeapon;
}

void Player::AddLight(Light* pLight) 
{
	// Just in case
	if(pLight == nullptr)
		return;

	// Add the weapon and make it current
	m_vpLights.push_back(pLight);
	m_currLight = pLight;
}

