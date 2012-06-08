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

void Player::Update(float aFElapsedTime) 
{
	
}

void Player::Render()
{
	
}

bool Player::CheckCollision(BaseCharacter* aPBase) 
{
	return true;
}

bool Player::CheckLifes() 
{
	return true;
}

void Player::AddQuest(Quests* aPQuest)
{
	
}

void Player::AddWeapon(Weapon* aPWeapon)
{
	
}

void Player::AddLight(Light* aPLight) 
{
	
}

