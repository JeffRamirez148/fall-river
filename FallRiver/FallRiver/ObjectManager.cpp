#include "ObjectManager.h"
#include "GamePlayState.h"
#include "BaseObject.h"
#include "CGame.h"
#include "BaseCharacter.h"
#include "Player.h"
#include "ViewManager.h"
#include <math.h>
#include "Particle_Manager.h"
#include "Emitter.h"
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
	vector<POINTFLOAT> lightsToRender;
	RECT cRect;
	RECT camRect = { (LONG)GamePlayState::GetInstance()->GetCamera().x - CGame::GetInstance()->GetScreenWidth(), (LONG)GamePlayState::GetInstance()->GetCamera().y - CGame::GetInstance()->GetScreenHeight(), LONG(GamePlayState::GetInstance()->GetCamera().x + CGame::GetInstance()->GetScreenWidth() * 2), LONG(GamePlayState::GetInstance()->GetCamera().y + CGame::GetInstance()->GetScreenHeight() * 2)};
	vector<int> fireEffects = GamePlayState::GetInstance()->GetFireA();
	for( unsigned int i = 0; lightsToRender.size() < 6 && i < fireEffects.size(); i += 3)
	{
		RECT fire = Particle_Manager::GetInstance()->GetActiveEmitter(fireEffects[i])->GetRect();
		if(
			IntersectRect( &cRect, &camRect, &fire ) == TRUE && CGame::GetInstance()->GetState() == GamePlayState::GetInstance()
			//float cY 
			)
	
		{
			//if(!GamePlayState::GetInstance()->GetPlayer())
			//	break;
	
			POINTFLOAT tmp;
			tmp.x = (((((fire.left + fire.right) * .5f) - GamePlayState::GetInstance()->GetPlayer()->GetPosX() )));

			tmp.y = (((((fire.bottom + fire.top) *.5f) - GamePlayState::GetInstance()->GetPlayer()->GetPosY() )));
			lightsToRender.push_back(tmp);
		}
	}
	vector<RECT> streetLights = GamePlayState::GetInstance()->GetStreelights();
	for( unsigned int i = 0; lightsToRender.size() < 6 && i < streetLights.size(); ++i)
	{
		if(
			IntersectRect( &cRect, &camRect, &streetLights[i] ) == TRUE && CGame::GetInstance()->GetState() == GamePlayState::GetInstance()
			//float cY 
			)
		{
			//if(!GamePlayState::GetInstance()->GetPlayer())
			//	break;
	
			POINTFLOAT tmp;	
			tmp.x = (((((streetLights[i].left + streetLights[i].right) * .5f) - GamePlayState::GetInstance()->GetPlayer()->GetPosX() )));
			tmp.y = (((((streetLights[i].bottom + streetLights[i].top) *.5f) - GamePlayState::GetInstance()->GetPlayer()->GetPosY() )));
			lightsToRender.push_back(tmp);
		}
	}

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
					//if(tmpCharacter->GetShadow())
					//{
					//	if( tmp->IsOn() && tmp->GetLightType() < 2 )
					//	{
					//		 if(tmp->GetDirection() < 4)
					//			ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth()/2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()) - 15, 1.0f, 1.25f, 16, 32, (tmp->GetDirection() - 1) * 1.57079f, D3DCOLOR_ARGB( 200, 0, 0, 0));
					//		else
					//		{
					//			switch(tmp->GetDirection())
					//			{
					//			case 4:
					//				ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth()/2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()) - 15, 1.0f, 1.25f, 16, 32, -0.78539f, D3DCOLOR_ARGB( 200, 0, 0, 0));
					//				break;
					//			case 5:
					//				ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth()/2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()) - 15, 1.0f, 1.25f, 16, 32, 0.78539f, D3DCOLOR_ARGB( 200, 0, 0, 0));
					//				break;
					//			case 6:
					//				ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth()/2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()) - 15, 1.0f, 1.25f, 16, 32, -2.35619f, D3DCOLOR_ARGB( 200, 0, 0, 0));
					//				break;
					//			case 7:
					//				ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth()/2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()) - 15, 1.0f, 1.25f, 16, 32, 2.35619f, D3DCOLOR_ARGB( 200, 0, 0, 0));
					//				break;
					//			default:
					//				break;
					//			}		
					//		}
					//	}
					//}
					if( tmp->IsOn() && ( tmp->GetLightType() > 1 ||  tmpCharacter->GetShadow()))
					{
						float angle = 0;
						float x2 = tmp->GetPosX() - tmpCharacter->GetPosX();
						float x = x2;
						float y2 = tmp->GetPosY() - tmpCharacter->GetPosY();
						float y = y2;
						x2 *= x2;
						y2 *= y2;
						float distance = sqrt(x2 + y2);

						angle = acos(x/distance);
						if( y < 0)
							angle *=  -1;

						angle -= 1.57079f;

						//angle = abs(angle);
						//if(y < 0)
						//angle *=  -1;
						//if( tmpCharacter->GetPosY() > tmp->GetPosY() && tmpCharacter->GetPosX() > tmp->GetPosX())
						//	angle = 0.78539f;
						//else if( tmpCharacter->GetPosY() < tmp->GetPosY() && tmpCharacter->GetPosX() > tmp->GetPosX())
						//	angle = -0.78539f;
						//else if( tmpCharacter->GetPosY() > tmp->GetPosY() && tmpCharacter->GetPosX() < tmp->GetPosX())
						//	angle = -2.35619f;
						//else if( tmpCharacter->GetPosY() < tmp->GetPosY() && tmpCharacter->GetPosX() < tmp->GetPosX())
						//	angle = 2.35619f;
						//else if(tmpCharacter->GetPosY() < tmp->GetPosY() && tmpCharacter->GetPosX() == tmp->GetPosX())
						//	angle = 0.0f;
						//else if(tmpCharacter->GetPosY() > tmp->GetPosY() && tmpCharacter->GetPosX() == tmp->GetPosX())
						//	angle = 3.14159f;
						//else if(tmpCharacter->GetPosY() == tmp->GetPosY() && tmpCharacter->GetPosX() < tmp->GetPosX())
						//	angle = -1.57079f;
						//else if(tmpCharacter->GetPosY() == tmp->GetPosY() && tmpCharacter->GetPosX() > tmp->GetPosX())
						//	angle = 1.57079f;

						if( tmpCharacter->GetCharacterType() == CHA_CHASING || tmpCharacter->GetCharacterType() == CHA_BOSS2 )
							ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth() /2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()) - 16, 1.0f, 1.25f, 16, 64, angle, D3DCOLOR_ARGB( 200, 0, 0, 0));
						else if(tmpCharacter->GetCharacterType() == CHA_NPC || tmpCharacter->GetCharacterType() == CHA_COMPANION )
							ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth() /2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()), 1.0f, 1.25f, 8, 32, angle, D3DCOLOR_ARGB( 200, 0, 0, 0));
						else
							ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth() /2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()), 1.0f, 1.25f, 16, 64, angle, D3DCOLOR_ARGB( 200, 0, 0, 0));

					}
				for(unsigned int i = 0; i < lightsToRender.size();++i)
				for(unsigned int i = 0; i < lightsToRender.size();++i)
				{
					float angle = 0;
					float x2 = lightsToRender[i].x - tmpCharacter->GetPosX();
					float x = x2;
					float y2 =lightsToRender[i].y - tmpCharacter->GetPosY();
					float y = y2;
					x2 *= x2;
					y2 *= y2;
					float distance = sqrt(x2 + y2);

					angle = acos(x/distance);
					if( y < 0)
						angle *=  -1;

					angle -= 1.57079f;
					if( tmpCharacter->GetCharacterType() == CHA_CHASING || tmpCharacter->GetCharacterType() == CHA_BOSS2 )
						ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth() - 16, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()) - 16, 1.0f, 1.25f, 16, 64, angle, D3DCOLOR_ARGB( 200, 0, 0, 0));
					else if(tmpCharacter->GetCharacterType() == CHA_NPC || tmpCharacter->GetCharacterType() == CHA_COMPANION )
							ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth() /2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()), 1.0f, 1.25f, 8, 32, angle, D3DCOLOR_ARGB( 200, 0, 0, 0));
					else if( tmpCharacter->GetCharacterType() == CHA_PLAYER)
					{
						if(tmpCharacter->GetDirection() == DIRE_LEFT)
							ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) - tmpCharacter->GetWidth() /2 - 10, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()) + 16, -1.0f, 1.25f, 16, 64, angle, D3DCOLOR_ARGB( 200, 0, 0, 0));
						else
							ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth() /2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()), -1.0f, 1.25f, 16, 64, angle, D3DCOLOR_ARGB( 200, 0, 0, 0));
					}
					else
						ViewManager::GetInstance()->DrawAnimation(tmpCharacter->GetAnimation(), (tmpCharacter->GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + tmpCharacter->GetWidth() /2, ((tmpCharacter->GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + tmpCharacter->GetHeight()), 1.0f, 1.25f, 16, 64, angle, D3DCOLOR_ARGB( 200, 0, 0, 0));
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

void ObjectManager::CheckTriangleCollisions()
{
	GamePlayState* gamePlay = GamePlayState::GetInstance();
	CGame* game = CGame::GetInstance();
	Player* player = gamePlay->GetPlayer();
	POINTFLOAT cam = gamePlay->GetCamera();
	int height = game->GetScreenHeight();
	int width = game->GetScreenWidth();

	float angleA = acos(ViewManager::GetInstance()->GetInnerCone());
	float angleB = 1.57079f;
	float angleC = 3.14159f - (angleA + angleB);
	angleC = (float)sin(double(angleC));
	angleA = (float)sin(double(angleA));
	float playerX = player->GetPosX();
	float playerY = player->GetPosY();
	float lightEndX=0, lightEndY=0, distanceC=0, distanceA=0;
	int playerDirection = player->GetDirection();
	bool a=false, b=false, c=false;
	float point1X=0, point1Y=0, point2X=0, point2Y=0, point3X=0, point3Y=0;
	for( OListIterator iter1 = m_Objects.begin(); iter1 != m_Objects.end(); ++iter1)
	{
		RECT iter1RECT = (*iter1)->GetRect();
		if((*iter1)->GetObjectType() != OBJ_LEVEL )
		{
			if((*iter1)->GetObjectType() == OBJ_CHARACTER)
			{
				BaseCharacter* tmpPlayer = (BaseCharacter*)(*iter1);
				if(tmpPlayer->GetCharacterType() == CHA_PLAYER)
					continue;
			}

			switch(playerDirection)
			{

			case 0:
				{
					lightEndX = (cam.x);
					lightEndY = playerY;
				}
				break;
			case 1:
				{
					lightEndX = playerX;
					lightEndY = (cam.y);
				}
				break;
			case 2:
				{
					lightEndX = playerX + (width >> 1);
					lightEndY = playerY;
				}
				break;
			case 3:
				{
					lightEndX = playerX;
					lightEndY = playerY + (height >> 1);
				}
				break;
			case 4:
				{
					lightEndX = cam.x;
					lightEndY = cam.y;
				}
				break;
			case 5:
				{
					lightEndX = cam.x + width;
					lightEndY = cam.y;
				}
				break;
			case 6:
				{
					lightEndX = cam.x;
					lightEndY = cam.y + height;
				}
				break;
			case 7:
				{
					lightEndX = cam.x + width;
					lightEndY = cam.y + height;
				}
				break;
			default:
				break;
			}


			float x2 = (lightEndX - playerX);
			x2 *= x2;
			float y2 = (lightEndY - playerY);
			y2 *= y2;
			distanceC = (float)sqrt(double(x2 + y2));
			distanceA = (distanceC/angleC) * angleA;

			// Make final triangle
			switch(playerDirection)
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
				point1X = lightEndX + distanceA;
				point1Y = lightEndY;
				point2X = lightEndX - distanceA;
				point2Y = lightEndY;
				break;
			case 4:
			case 7:
				point1X = lightEndX + (distanceA * .5f);
				point1Y = lightEndY + (distanceA * .5f);
				point2X = lightEndX - (distanceA * .5f);
				point2Y = lightEndY - (distanceA * .5f);
				break;
			case 5:
			case 6:
				point1X = lightEndX - (distanceA * .5f);
				point1Y = lightEndY + (distanceA * .5f);
				point2X = lightEndX + (distanceA * .5f);
				point2Y = lightEndY - (distanceA * .5f);
				break;
			default:
				break;
			}
			point3X = playerX;
			point3Y = playerY;

			// left, top
			a = ((iter1RECT.left /*+ cam.x*/ - point2X) * (point1Y - point2Y) - (point1X - point2X) * (iter1RECT.top /*+ cam.y*/ - point2Y)) < 0.0f;
			b = ((iter1RECT.left /*+ cam.x*/ - point3X) * (point2Y - point3Y) - (point2X - point3X) * (iter1RECT.top /*+ cam.y*/ - point3Y)) < 0.0f;
			c = ((iter1RECT.left /*+ cam.x*/ - point1X) * (point3Y - point1Y) - (point3X - point1X) * (iter1RECT.top /*+ cam.y*/ - point1Y)) < 0.0f;
			(*iter1)->SetShadow((a == b) && (b == c));
			if((*iter1)->GetShadow())
				continue;

			// left, bottom
			a = ((iter1RECT.left /*+ cam.x*/ - point2X) * (point1Y - point2Y) - (point1X - point2X) * (iter1RECT.bottom /*+ cam.y*/ - point2Y)) < 0.0f;
			b = ((iter1RECT.left /*+ cam.x*/ - point3X) * (point2Y - point3Y) - (point2X - point3X) * (iter1RECT.bottom /*+ cam.y*/ - point3Y)) < 0.0f;
			c = ((iter1RECT.left /*+ cam.x*/ - point1X) * (point3Y - point1Y) - (point3X - point1X) * (iter1RECT.bottom /*+ cam.y*/ - point1Y)) < 0.0f;
			(*iter1)->SetShadow((a == b) && (b == c));
			if((*iter1)->GetShadow())
				continue;

			// right, top
			a = ((iter1RECT.right /*+ cam.x*/ - point2X) * (point1Y - point2Y) - (point1X - point2X) * (iter1RECT.top /*+ cam.y*/ - point2Y)) < 0.0f;
			b = ((iter1RECT.right /*+ cam.x*/ - point3X) * (point2Y - point3Y) - (point2X - point3X) * (iter1RECT.top /*+ cam.y*/ - point3Y)) < 0.0f;
			c = ((iter1RECT.right /*+ cam.x*/ - point1X) * (point3Y - point1Y) - (point3X - point1X) * (iter1RECT.top /*+ cam.y*/ - point1Y)) < 0.0f;
			(*iter1)->SetShadow((a == b) && (b == c));
			if((*iter1)->GetShadow())
				continue;

			// right, bottom;
			a = ((iter1RECT.right /*+ cam.x*/ - point2X) * (point1Y - point2Y) - (point1X - point2X) * (iter1RECT.bottom /*+ cam.y*/ - point2Y)) < 0.0f;
			b = ((iter1RECT.right /*+ cam.x*/ - point3X) * (point2Y - point3Y) - (point2X - point3X) * (iter1RECT.bottom /*+ cam.y*/ - point3Y)) < 0.0f;
			c = ((iter1RECT.right /*+ cam.x*/ - point1X) * (point3Y - point1Y) - (point3X - point1X) * (iter1RECT.bottom /*+ cam.y*/ - point1Y)) < 0.0f;
			(*iter1)->SetShadow((a == b) && (b == c));
		}
	}
}
