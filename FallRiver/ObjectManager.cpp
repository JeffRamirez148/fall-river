#include <Windows.h>
#include <vector>
using namespace std;

#include "ObjectManager.h"
#include "GamePlayState.h"
#include "BaseObject.h"

void ObjectManager::Enter() 
{
}

void ObjectManager::Exit() 
{
}

bool ObjectManager::Input() 
{
	return true;
}

void ObjectManager::Update(float fElapsedTime) 
{
}

void ObjectManager::Render() 
{
}

ObjectManager* ObjectManager::GetInstance() 
{
	static ObjectManager s_Instance;

	return &s_Instance;
}

