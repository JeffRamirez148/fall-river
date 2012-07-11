#include "ObjectManager.h"
#include "GamePlayState.h"
#include "BaseObject.h"
#include "CGame.h"
#include "BaseCharacter.h"

// Instantiate the staic data member
ObjectManager* ObjectManager::s_Instance = nullptr;


ObjectManager* ObjectManager::GetInstance( void )
{
	if( s_Instance == nullptr )
		s_Instance = new ObjectManager;

	return s_Instance;
}

void ObjectManager::DeleteInstance( void )
{
	delete s_Instance;
	s_Instance = nullptr;
}

ObjectManager::ObjectManager(void)
{
}


ObjectManager::~ObjectManager(void)
{
}

void ObjectManager::AddObject( BaseObject* ptr )
{
	if( ptr == nullptr )
		return;

	m_Objects.push_back(ptr);

	ptr->AddRef();
}

void ObjectManager::RemoveObject( BaseObject* ptr )
{
	if(ptr == nullptr)
		return;

	for( OListIterator iter = m_Objects.begin(); iter != m_Objects.end(); ++iter)
	{
		if( (*iter) == ptr)
		{
			ptr->Release();

			iter = m_Objects.erase(iter);
			break;
		}
	}
}

void ObjectManager::RemoveAllObjects( void )
{
	for( OListIterator iter = m_Objects.begin(); iter != m_Objects.end(); ++iter)
		(*iter)->Release();

	m_Objects.clear();
}

void ObjectManager::UpdateAllObjects( float fElapsedTime )
{
	for( OListIterator iter = m_Objects.begin(); iter != m_Objects.end(); ++iter)
	{
		if(((*iter)->GetPosX() - GamePlayState::GetInstance()->GetCamera().x > CGame::GetInstance()->GetScreenWidth() || (*iter)->GetPosY() - GamePlayState::GetInstance()->GetCamera().y > CGame::GetInstance()->GetScreenHeight() ||
			(*iter)->GetPosX() - GamePlayState::GetInstance()->GetCamera().x + (*iter)->GetWidth() < 0 || (*iter)->GetPosY() - GamePlayState::GetInstance()->GetCamera().y + (*iter)->GetHeight() < 0) && (*iter)->GetObjectType() != OBJ_LEVEL)
			continue;
		else
		(*iter)->Update(fElapsedTime);
	}
}

void ObjectManager::RenderAllObjects( void )
{
	for( OListIterator iter = m_Objects.begin(); iter != m_Objects.end(); ++iter)
	{
		if(((*iter)->GetPosX() - GamePlayState::GetInstance()->GetCamera().x > CGame::GetInstance()->GetScreenWidth() || (*iter)->GetPosY() - GamePlayState::GetInstance()->GetCamera().y > CGame::GetInstance()->GetScreenHeight() ||
			(*iter)->GetPosX() - GamePlayState::GetInstance()->GetCamera().x + (*iter)->GetWidth() < 0 || (*iter)->GetPosY() - GamePlayState::GetInstance()->GetCamera().y + (*iter)->GetHeight() < 0) && (*iter)->GetObjectType() != OBJ_LEVEL || (*iter)->GetObjectType() == OBJ_BUSH)
			continue;
		else
			(*iter)->Render();
	}
}

void ObjectManager::CheckCollisions( void )
{
	for( OListIterator iter1 = m_Objects.begin(); iter1 != m_Objects.end(); ++iter1)
	{
		if(((*iter1)->GetPosX() - GamePlayState::GetInstance()->GetCamera().x > CGame::GetInstance()->GetScreenWidth() || (*iter1)->GetPosY() - GamePlayState::GetInstance()->GetCamera().y > CGame::GetInstance()->GetScreenHeight() ||
			(*iter1)->GetPosX() - GamePlayState::GetInstance()->GetCamera().x + (*iter1)->GetWidth() < 0 || (*iter1)->GetPosY() - GamePlayState::GetInstance()->GetCamera().y + (*iter1)->GetHeight() < 0) && (*iter1)->GetObjectType() != OBJ_LEVEL)
		{	
			continue;
		}
		for( OListIterator iter2 = m_Objects.begin(); iter2 != m_Objects.end(); ++iter2)
		{
			if((*iter1) == (*iter2) )
				continue;

			if((*iter1)->CheckCollision((*iter2)))
			{
				break;
			}
		}
	}
}
