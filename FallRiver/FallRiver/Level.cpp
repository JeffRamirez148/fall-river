#include "Level.h"
#include "DirectInput.h"
#include "tinyxml.h"
#include "ViewManager.h"
#include "GamePlayState.h"
#include <string>
#include "CGame.h"
Level::Level() 
{
	m_nObjectType = OBJ_LEVEL;
}

Level* Level::GetInstance() 
{
	static Level s_Instance;
	return &s_Instance;
}

Level::~Level() 
{
}

void Level::Update(float fElapsedTime)
{
	DirectInput* pDI = DirectInput::GetInstance();

	//float time = fElapsedTime;
	LONG test = long(100.0f * fElapsedTime);
	if(pDI->KeyDown(DIK_RIGHT) && GamePlayState::GetInstance()->CanMoveRight() )
	{
		m_nPosX -= 100 * fElapsedTime;


		for(unsigned int i = 0; i < m_vCollisions.size(); i++)
		{
			int tmpPosX = (int)m_nPosX + m_vCollisions[i].x;
			int tmpPosY = (int)m_nPosY + m_vCollisions[i].y;

			m_vCollisions[i].m_rCollision.right = tmpPosX+m_vCollisions[i].width;
			m_vCollisions[i].m_rCollision.left	= tmpPosX;
			m_vCollisions[i].m_rCollision.top	= tmpPosY;
			m_vCollisions[i].m_rCollision.bottom= tmpPosY+m_vCollisions[i].height;
		}


		for(unsigned int i = 0; i < m_vTiles.size(); i++)
		{
			m_vTiles[i].m_nWorldPosX -= 100 * fElapsedTime;
			//m_vTiles[i].m_nWorldPosY -=  100 * fElapsedTime;
		}

	}
	else if(pDI->KeyDown(DIK_LEFT) && GamePlayState::GetInstance()->CanMoveLeft() )
	{
		m_nPosX += 100 * fElapsedTime;
		for(unsigned int i = 0; i < m_vCollisions.size(); i++)
		{
			int tmpPosX = (int)m_nPosX + m_vCollisions[i].x;
			int tmpPosY = (int)m_nPosY + m_vCollisions[i].y;

			m_vCollisions[i].m_rCollision.right = tmpPosX+m_vCollisions[i].width;
			m_vCollisions[i].m_rCollision.left	= tmpPosX;
			m_vCollisions[i].m_rCollision.top	= tmpPosY;
			m_vCollisions[i].m_rCollision.bottom= tmpPosY+m_vCollisions[i].height;

		}

	
		for(unsigned int i = 0; i < m_vTiles.size(); i++)
		{
			m_vTiles[i].m_nWorldPosX +=  100 * fElapsedTime;
			//m_vTiles[i].m_nWorldPosY +=  100 * fElapsedTime;
		}


	}

	if(pDI->KeyDown(DIK_UP) && GamePlayState::GetInstance()->CanMoveUp() )
	{
		m_nPosY += 100 * fElapsedTime;
		for(unsigned int i = 0; i < m_vCollisions.size(); i++)
		{
			int tmpPosX = (int)m_nPosX + m_vCollisions[i].x;
			int tmpPosY = (int)m_nPosY + m_vCollisions[i].y;

			m_vCollisions[i].m_rCollision.right = tmpPosX+m_vCollisions[i].width;
			m_vCollisions[i].m_rCollision.left	= tmpPosX;
			m_vCollisions[i].m_rCollision.top	= tmpPosY;
			m_vCollisions[i].m_rCollision.bottom= tmpPosY+m_vCollisions[i].height;
		}
		
		for(unsigned int i = 0; i < m_vTiles.size(); i++)
		{
			//m_vTiles[i].m_nWorldPosX +=  100 * fElapsedTime;
			m_vTiles[i].m_nWorldPosY += 100 * fElapsedTime;
		}

	}
	else if(pDI->KeyDown(DIK_DOWN) && GamePlayState::GetInstance()->CanMoveDown() )
	{
		m_nPosY -= 100 * fElapsedTime;
		for(unsigned int i = 0; i < m_vCollisions.size(); i++)
		{
			int tmpPosX = (int)m_nPosX + m_vCollisions[i].x;
			int tmpPosY = (int)m_nPosY + m_vCollisions[i].y;

			m_vCollisions[i].m_rCollision.right = tmpPosX+m_vCollisions[i].width;
			m_vCollisions[i].m_rCollision.left	= tmpPosX;
			m_vCollisions[i].m_rCollision.top	= tmpPosY;
			m_vCollisions[i].m_rCollision.bottom= tmpPosY+m_vCollisions[i].height;
		}

		for(unsigned int i = 0; i < m_vTiles.size(); i++)
		{
			//m_vTiles[i].m_nWorldPosX -=  100 * fElapsedTime;
			m_vTiles[i].m_nWorldPosY -= 100 * fElapsedTime;
		}

	}

}

void Level::Render() 
{

	ViewManager* pView = ViewManager::GetInstance();
	
	//if( m_nBackgroundID == -1)
	//{
	//	return;
	//}

	
	//m_nBackgroundID = pTM->LoadTexture(_T("resource/graphics/test.png"));
	//pView->DrawStaticTexture(m_nBackgroundID, (int)m_nPosX, (int)m_nPosY );


	CGame* pGame = CGame::GetInstance();

	RECT cull;
	cull.left = 0;
	cull.top = 0;
	cull.right = pGame->GetScreenWidth();
	cull.bottom = pGame->GetScreenHeight(); 


	for(unsigned int i = 0; i < m_vTiles.size(); i++)
	{
		RECT tmp;
		tmp.left =(LONG)m_vTiles[i].m_nWorldPosX;
		tmp.top = (LONG)m_vTiles[i].m_nWorldPosY;
		tmp.right = LONG(m_vTiles[i].m_nWorldPosX+m_vTiles[i].width);
		tmp.bottom = LONG(m_vTiles[i].m_nWorldPosY+m_vTiles[i].height);

		RECT intersect;
		if( IntersectRect(&intersect,&tmp, &cull) == TRUE )
		{
			if( m_vTiles[i].m_Layer == 1)
			{

				pView->DrawStaticTexture(m_vTiles[i].m_nTileID, (int)m_vTiles[i].m_nWorldPosX, (int)m_vTiles[i].m_nWorldPosY,1,1, &m_vTiles[i].m_rImageRect );
			}
		}
	}

	for(unsigned int i = 0; i < m_vTiles.size(); i++)
	{
		RECT tmp;
		tmp.left = (LONG)m_vTiles[i].m_nWorldPosX;
		tmp.top = (LONG)m_vTiles[i].m_nWorldPosY;
		tmp.right = LONG(m_vTiles[i].m_nWorldPosX+m_vTiles[i].width);
		tmp.bottom = LONG(m_vTiles[i].m_nWorldPosY+m_vTiles[i].height);

		RECT intersect;
		if( IntersectRect(&intersect,&tmp, &cull) == TRUE )
		{
			if( m_vTiles[i].m_Layer == 2)
			{

				pView->DrawStaticTexture(m_vTiles[i].m_nTileID, (int)m_vTiles[i].m_nWorldPosX, (int)m_vTiles[i].m_nWorldPosY,1,1, &m_vTiles[i].m_rImageRect );
			}
		}
	}

	for(unsigned int i = 0; i < m_vTiles.size(); i++)
	{
		RECT tmp;
		tmp.left = (LONG)m_vTiles[i].m_nWorldPosX;
		tmp.top = (LONG)m_vTiles[i].m_nWorldPosY;
		tmp.right = LONG(m_vTiles[i].m_nWorldPosX+m_vTiles[i].width);
		tmp.bottom = LONG(m_vTiles[i].m_nWorldPosY+m_vTiles[i].height);

		RECT intersect;
		if( IntersectRect(&intersect,&tmp, &cull) == TRUE )
		{
			if( m_vTiles[i].m_Layer == 3)
			{

				pView->DrawStaticTexture(m_vTiles[i].m_nTileID, (int)m_vTiles[i].m_nWorldPosX, (int)m_vTiles[i].m_nWorldPosY,1,1, &m_vTiles[i].m_rImageRect );
			}
		}
	}

	for(unsigned int i = 0; i < m_vTiles.size(); i++)
	{
		RECT tmp;
		tmp.left = (LONG)m_vTiles[i].m_nWorldPosX;
		tmp.top = (LONG)m_vTiles[i].m_nWorldPosY;
		tmp.right = LONG(m_vTiles[i].m_nWorldPosX+m_vTiles[i].width);
		tmp.bottom = LONG(m_vTiles[i].m_nWorldPosY+m_vTiles[i].height);

		RECT intersect;
		if( IntersectRect(&intersect,&tmp, &cull) == TRUE )
		{
			if( m_vTiles[i].m_Layer == 4)
			{

				pView->DrawStaticTexture(m_vTiles[i].m_nTileID, (int)m_vTiles[i].m_nWorldPosX, (int)m_vTiles[i].m_nWorldPosY,1,1, &m_vTiles[i].m_rImageRect );
			}
		}
	}

	for(unsigned int i = 0; i < m_vTiles.size(); i++)
	{
		RECT tmp;
		tmp.left = (LONG)m_vTiles[i].m_nWorldPosX;
		tmp.top = (LONG)m_vTiles[i].m_nWorldPosY;
		tmp.right = LONG(m_vTiles[i].m_nWorldPosX+m_vTiles[i].width);
		tmp.bottom = LONG(m_vTiles[i].m_nWorldPosY+m_vTiles[i].height);

		RECT intersect;
		if( IntersectRect(&intersect,&tmp, &cull) == TRUE )
		{
			if( m_vTiles[i].m_Layer == 5)
			{

				pView->DrawStaticTexture(m_vTiles[i].m_nTileID, (int)m_vTiles[i].m_nWorldPosX, (int)m_vTiles[i].m_nWorldPosY,1,1, &m_vTiles[i].m_rImageRect );
			}
		}
	}

	pView->GetSprite()->Flush();


	for( unsigned int i = 0; i < m_vCollisions.size(); i++ )
	{
		//m_vCollisions[i].m_cType;
		if( _stricmp(m_vCollisions[i].m_cType,"Wall") == 0 )
		{
			pView->DrawUnfilledRect(m_vCollisions[i].m_rCollision,255,255,255);
		}

		if( _stricmp(m_vCollisions[i].m_cType,"powerup") == 0 )
		{
			pView->DrawUnfilledRect(m_vCollisions[i].m_rCollision,0,255,255);
		}

	}

}



bool Level::LoadLevel( const char* szFilename )
{
	m_nPosX = 0;
	m_nPosY = 0;
	//CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();

	// Create the TinyXML document
	TiXmlDocument doc;

	//Attempt to load the file
	if( doc.LoadFile( szFilename ) == false )
		return false;


	// Access the root element ( "players_list")
	TiXmlElement* pRoot = doc.RootElement();

	if( pRoot == nullptr )
		return false;

	// Clear the existing player data in the vector (if any)
	m_vCollisions.clear();


	//Iterate through the nodes to load player data
	TiXmlElement* pLevel = pRoot->FirstChildElement();


	vector<TwoInts> ids;


	if( pLevel != nullptr )
	{
		string p = pLevel->Value();

		if( p != "Assets")
		{
			return false;
		}

		while( pLevel != nullptr )
		{

			const char* pText = pLevel->GetText();

			string test;
			if( pText != nullptr )
			{
				test = pText;
			}
			else
			{
				return false;
			}
			test = "resource/graphics/"+test;
			
			TwoInts tmp;
			
			pLevel->Attribute("TileID",&tmp.x);

			//ids.push_back(tmp);

			char filepath[100];
			if( pText != nullptr )
				strcpy_s( filepath, 100, test.c_str() );


			//TCHAR buffer[100];
			//mbstowcs_s( nullptr, buffer, 100, filepath, _TRUNCATE );
			
			tmp.y =  ViewManager::GetInstance()->RegisterTexture(filepath);

			ids.push_back(tmp);

			pLevel = pLevel->NextSiblingElement();

			string tmp123 = pLevel->Value();

			if( tmp123 == "Tile")
			{
				break;
			}
		}


		while( pLevel != nullptr )
		{
			//Read info from the node
			mapTiles info = {};

			TiXmlElement* pTiles = pLevel->FirstChildElement();

			int tmpX,tmpY,tmpH,tmpW,tmpX2,tmpY2,tmpID,tmpLayer;
			pLevel->Attribute("layer",&tmpLayer);
			pTiles->Attribute( "x", &tmpX );
			pTiles->Attribute( "y", &tmpY );
			pTiles->Attribute( "width", &tmpW );
			pTiles->Attribute( "height", &tmpH );

			info.m_Layer = tmpLayer;
			info.m_rImageRect.left = (long)tmpX;
			info.m_rImageRect.top = (long)tmpY;
			info.m_rImageRect.right = long(tmpX+tmpW);
			info.m_rImageRect.bottom = long(tmpY+tmpH);
			info.height = (float)tmpH;
			info.width = (float)tmpW;

			pTiles = pTiles->NextSiblingElement();


			pTiles->Attribute("x", &tmpX2);
			pTiles->Attribute("y", &tmpY2);

			info.m_nWorldPosX = (float)tmpX2;
			info.m_nWorldPosY = (float)tmpY2;



			pTiles = pTiles->NextSiblingElement();

			pTiles->Attribute("ID",&tmpID);

			for(unsigned int i = 0; i < ids.size(); i++)
			{
				if( tmpID == ids[i].x )
				{
					tmpID = ids[i].y;
					break;
				}
			}
			info.m_nTileID = tmpID;


			m_vTiles.push_back(info);

			pLevel = pLevel->NextSiblingElement();
			string tmp123 = pLevel->Value();

			if( tmp123 == "Collision")
			{
				break;
			}

		}

		while( pLevel != nullptr )
		{
			leveldata info = {};
			TiXmlElement* pCollision = pLevel->FirstChildElement();

			//Read name
			const char* pText = pCollision->GetText();
			if( pText != nullptr )
				strcpy_s( info.m_cType, 32, pText );

			pCollision = pCollision->NextSiblingElement();

			//// Read attributes
			//pLevel->Attribute( "score", &info.nScore );
			int tmpX,tmpY,tmpH,tmpW;
			pCollision->Attribute( "x", &tmpX );
			pCollision->Attribute( "y", &tmpY );
			pCollision->Attribute( "width", &tmpW );
			pCollision->Attribute( "height", &tmpH );

			info.m_rCollision.left = (LONG)tmpX;
			info.m_rCollision.top = (LONG)tmpY;
			info.m_rCollision.right = (LONG)(tmpX+tmpW);
			info.m_rCollision.bottom = (LONG)(tmpY+tmpH);

			info.height = tmpH;
			info.width = tmpW;
			info.x = tmpX;
			info.y = tmpY;

			// Save this info to the vector
			m_vCollisions.push_back( info );

			pLevel = pLevel->NextSiblingElement();
		}


	}
	else
	{
		return false;
	}
	
	
	return true;
}



bool Level::CheckCollision(IObjects* pBase)
{
	return true;
}