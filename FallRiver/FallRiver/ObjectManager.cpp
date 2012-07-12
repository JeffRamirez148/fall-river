#include "ObjectManager.h"
#include "GamePlayState.h"
#include "BaseObject.h"
#include "CGame.h"
#include "BaseCharacter.h"
#include "Player.h"
#include "ViewManager.h"
#include <math.h>

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
		{
			if((*iter)->GetObjectType() == OBJ_CHARACTER)
			{
				BaseCharacter* tmpCharacter = (BaseCharacter*)(*iter);
				if(tmpCharacter->GetCharacterType() != CHA_PLAYER)
				{
					Player* tmp = GamePlayState::GetInstance()->GetPlayer();
					if(tmpCharacter->GetShadow())
					{
						if( tmp->IsOn() && tmp->GetLightType() < 2 )
						{
							if(tmp->GetDirection() == 1)
								ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth()/2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()) - 15, 1.0f, 1.25f, 16, 32, (tmp->GetDirection() - 1) * 1.57079f, D3DCOLOR_ARGB( 200, 0, 0, 0));
							else if(tmp->GetDirection() < 4 && tmp->GetDirection() != 1)
								ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth()/2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()) - 15, 1.0f, 1.25f, 16, 32, (tmp->GetDirection() - 1) * 1.57079f, D3DCOLOR_ARGB( 200, 0, 0, 0));
							else
							{
								switch(tmp->GetDirection())
								{
								case 4:
									ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth()/2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()) - 15, 1.0f, 1.25f, 16, 32, -0.78539f, D3DCOLOR_ARGB( 200, 0, 0, 0));
									break;
								case 5:
									ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth()/2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()) - 15, 1.0f, 1.25f, 16, 32, 0.78539f, D3DCOLOR_ARGB( 200, 0, 0, 0));
									break;
								case 6:
									ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth()/2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()) - 15, 1.0f, 1.25f, 16, 32, 2.35619f, D3DCOLOR_ARGB( 200, 0, 0, 0));
									break;
								case 7:
									ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth()/2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()) - 15, 1.0f, 1.25f, 16, 32, -2.35619f, D3DCOLOR_ARGB( 200, 0, 0, 0));
									break;
								default:
									break;
								}		
							}
						}
					}
					else if( tmp->IsOn() && tmp->GetLightType() > 2 )
					{
						float angle = 0;
						if( tmpCharacter->GetPosY() > tmp->GetPosY() && tmpCharacter->GetPosX() > tmp->GetPosX())
							angle = 0.78539f;
						else if( tmpCharacter->GetPosY() < tmp->GetPosY() && tmpCharacter->GetPosX() > tmp->GetPosX())
							angle = -0.78539f;
						else if( tmpCharacter->GetPosY() > tmp->GetPosY() && tmpCharacter->GetPosX() < tmp->GetPosX())
							angle = 2.35619f;
						else if( tmpCharacter->GetPosY() < tmp->GetPosY() && tmpCharacter->GetPosX() < tmp->GetPosX())
							angle = -2.35619f;
						else if(tmpCharacter->GetPosY() < tmp->GetPosY() && tmpCharacter->GetPosX() == tmp->GetPosX())
							angle = 0.0f;
						else if(tmpCharacter->GetPosY() > tmp->GetPosY() && tmpCharacter->GetPosX() == tmp->GetPosX())
							angle = 3.14159f;
						else if(tmpCharacter->GetPosY() == tmp->GetPosY() && tmpCharacter->GetPosX() < tmp->GetPosX())
							angle = -1.57079f;
						else if(tmpCharacter->GetPosY() == tmp->GetPosY() && tmpCharacter->GetPosX() > tmp->GetPosX())
							angle = 1.57079f;

						if( angle == 0)
							ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth()/2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()) - 15, 1.0f, 1.25f, 16, 32, angle, D3DCOLOR_ARGB( 200, 0, 0, 0));
						else
							ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth()/2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()) - 15, 1.0f, 1.25f, 16, 32, angle, D3DCOLOR_ARGB( 200, 0, 0, 0));
					}
				}
			}
			(*iter)->Render();
		}
	}
}

void ObjectManager::CheckCollisions( void )
{
	for( OListIterator iter1 = m_Objects.begin(); iter1 != m_Objects.end(); ++iter1)
	{
		if(((*iter1)->GetPosX() - GamePlayState::GetInstance()->GetCamera().x > CGame::GetInstance()->GetScreenWidth() || (*iter1)->GetPosY() - GamePlayState::GetInstance()->GetCamera().y > CGame::GetInstance()->GetScreenHeight() ||
			(*iter1)->GetPosX() - GamePlayState::GetInstance()->GetCamera().x + (*iter1)->GetWidth() < 0 || (*iter1)->GetPosY() - GamePlayState::GetInstance()->GetCamera().y + (*iter1)->GetHeight() < 0) && (*iter1)->GetObjectType() != OBJ_LEVEL)
			continue;
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

void ObjectManager::CheckTriangleCollisions()
{
	float angleA = ViewManager::GetInstance()->GetInnerCone() * .5f;
	float angleB = 1.57079f;
	float angleC = 3.14159f - (angleA + angleB);
	angleC = sin(double(angleC));
	angleA = sin(double(angleA));
	float playerX = GamePlayState::GetInstance()->GetPlayer()->GetPosX();
	float playerY = GamePlayState::GetInstance()->GetPlayer()->GetPosY();
	float lightEndX, lightEndY, distanceC, distanceA;

	for( OListIterator iter1 = m_Objects.begin(); iter1 != m_Objects.end(); ++iter1)
	{
		if((*iter1)->GetObjectType() != OBJ_LEVEL )
		{
			if((*iter1)->GetObjectType() == OBJ_CHARACTER)
			{
				BaseCharacter* tmpPlayer = (BaseCharacter*)(*iter1);
				if(tmpPlayer->GetCharacterType() == CHA_PLAYER)
					continue;
				if(tmpPlayer->GetCharacterType() == CHA_NPC)
					int s = 1;
			}
			bool a, b, c;

			switch(GamePlayState::GetInstance()->GetPlayer()->GetDirection())
			{

			case 0:
				{
					lightEndX = (GamePlayState::GetInstance()->GetCamera().x);
					lightEndY = playerY;
				}
				break;
			case 1:
				{
					lightEndX = playerX;
					lightEndY = (GamePlayState::GetInstance()->GetCamera().y);
				}
				break;
			case 2:
				{
					lightEndX = playerX + (CGame::GetInstance()->GetScreenWidth() >> 1);
					lightEndY = playerY;
				}
				break;
			case 3:
				{
					lightEndX = playerX;
					lightEndY = playerY + (CGame::GetInstance()->GetScreenHeight() >> 1);
				}
				break;
			case 4:
			case 5:
				lightEndX = playerX;
				lightEndY = playerY - (CGame::GetInstance()->GetScreenHeight() >> 1);
				break;
			case 6:
			case 7:
				lightEndX = playerX;
				lightEndY = playerY + (CGame::GetInstance()->GetScreenHeight() >> 1);
				break;
			default:
				{

				}
				break;
			}


			float x2 = (lightEndX - playerX);
			x2 *= x2;
			float y2 = (lightEndY - playerY);
			y2 *= y2;
			distanceC = sqrt(double(x2 + y2));
			distanceA = (distanceC/angleC) * angleA;

			// Make final triangle
			float point1X, point1Y, point2X, point2Y, point3X, point3Y;
			switch(GamePlayState::GetInstance()->GetPlayer()->GetDirection())
			{
			case 0:
			case 2:
				point1X = lightEndX;
				point1Y = lightEndY + distanceA;
				point2X = lightEndX;
				point2Y = lightEndY - distanceA;
				break;
			case 1:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
				point1X = lightEndX + distanceA;
				point1Y = lightEndY;
				point2X = lightEndX - distanceA;
				point2Y = lightEndY;
				break;
			default:
				break;
			}
			point3X = playerX;
			point3Y = playerY;

			// left, top
			a = (((*iter1)->GetRect().left /*+ GamePlayState::GetInstance()->GetCamera().x*/ - point2X) * (point1Y - point2Y) - (point1X - point2X) * ((*iter1)->GetRect().top /*+ GamePlayState::GetInstance()->GetCamera().y*/ - point2Y)) < 0.0f;
			b = (((*iter1)->GetRect().left /*+ GamePlayState::GetInstance()->GetCamera().x*/ - point3X) * (point2Y - point3Y) - (point2X - point3X) * ((*iter1)->GetRect().top /*+ GamePlayState::GetInstance()->GetCamera().y*/ - point3Y)) < 0.0f;
			c = (((*iter1)->GetRect().left /*+ GamePlayState::GetInstance()->GetCamera().x*/ - point1X) * (point3Y - point1Y) - (point3X - point1X) * ((*iter1)->GetRect().top /*+ GamePlayState::GetInstance()->GetCamera().y*/ - point1Y)) < 0.0f;
			(*iter1)->SetShadow((a == b) && (b == c));
			if((*iter1)->GetShadow())
				continue;

			// left, bottom
			a = (((*iter1)->GetRect().left /*+ GamePlayState::GetInstance()->GetCamera().x*/ - point2X) * (point1Y - point2Y) - (point1X - point2X) * ((*iter1)->GetRect().bottom /*+ GamePlayState::GetInstance()->GetCamera().y*/ - point2Y)) < 0.0f;
			b = (((*iter1)->GetRect().left /*+ GamePlayState::GetInstance()->GetCamera().x*/ - point3X) * (point2Y - point3Y) - (point2X - point3X) * ((*iter1)->GetRect().bottom /*+ GamePlayState::GetInstance()->GetCamera().y*/ - point3Y)) < 0.0f;
			c = (((*iter1)->GetRect().left /*+ GamePlayState::GetInstance()->GetCamera().x*/ - point1X) * (point3Y - point1Y) - (point3X - point1X) * ((*iter1)->GetRect().bottom /*+ GamePlayState::GetInstance()->GetCamera().y*/ - point1Y)) < 0.0f;
			(*iter1)->SetShadow((a == b) && (b == c));
			if((*iter1)->GetShadow())
				continue;

			// right, top
			a = (((*iter1)->GetRect().right /*+ GamePlayState::GetInstance()->GetCamera().x*/ - point2X) * (point1Y - point2Y) - (point1X - point2X) * ((*iter1)->GetRect().top /*+ GamePlayState::GetInstance()->GetCamera().y*/ - point2Y)) < 0.0f;
			b = (((*iter1)->GetRect().right /*+ GamePlayState::GetInstance()->GetCamera().x*/ - point3X) * (point2Y - point3Y) - (point2X - point3X) * ((*iter1)->GetRect().top /*+ GamePlayState::GetInstance()->GetCamera().y*/ - point3Y)) < 0.0f;
			c = (((*iter1)->GetRect().right /*+ GamePlayState::GetInstance()->GetCamera().x*/ - point1X) * (point3Y - point1Y) - (point3X - point1X) * ((*iter1)->GetRect().top /*+ GamePlayState::GetInstance()->GetCamera().y*/ - point1Y)) < 0.0f;
			(*iter1)->SetShadow((a == b) && (b == c));
			if((*iter1)->GetShadow())
				continue;
			
			// right, bottom;
			a = (((*iter1)->GetRect().right /*+ GamePlayState::GetInstance()->GetCamera().x*/ - point2X) * (point1Y - point2Y) - (point1X - point2X) * ((*iter1)->GetRect().bottom /*+ GamePlayState::GetInstance()->GetCamera().y*/ - point2Y)) < 0.0f;
			b = (((*iter1)->GetRect().right /*+ GamePlayState::GetInstance()->GetCamera().x*/ - point3X) * (point2Y - point3Y) - (point2X - point3X) * ((*iter1)->GetRect().bottom /*+ GamePlayState::GetInstance()->GetCamera().y*/ - point3Y)) < 0.0f;
			c = (((*iter1)->GetRect().right /*+ GamePlayState::GetInstance()->GetCamera().x*/ - point1X) * (point3Y - point1Y) - (point3X - point1X) * ((*iter1)->GetRect().bottom /*+ GamePlayState::GetInstance()->GetCamera().y*/ - point1Y)) < 0.0f;
			(*iter1)->SetShadow((a == b) && (b == c));
		}
	}
}
