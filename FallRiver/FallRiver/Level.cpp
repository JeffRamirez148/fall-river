#include "Level.h"
#include "DirectInput.h"
#include "tinyxml.h"
#include "ViewManager.h"
#include "GamePlayState.h"

Level::Level() 
{
	m_nBackgroundID = -1;
	m_nPosX = 0;
	m_nPosY = 0;
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
	}

}

void Level::Render() 
{

	ViewManager* pView = ViewManager::GetInstance();
	
	if( m_nBackgroundID == -1)
	{
		return;
	}

	
	//m_nBackgroundID = pTM->LoadTexture(_T("resource/graphics/test.png"));
	pView->DrawStaticTexture(m_nBackgroundID, (int)m_nPosX, (int)m_nPosY );

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
	TiXmlElement* pLevel = pRoot->FirstChildElement( "level_info" );


	//TCHAR buffer[1000];
	//char* filepath;
	//
	//
	//TCHAR sBuffer[10] = {};
	//_stprintf_s( sBuffer, 10, _T("%i"), m_vPlayer[i].nScore);
	//
	//mbstowcs_s( nullptr, buffer, 100, m_vPlayer[i].szName, _TRUNCATE );


	if( pLevel != nullptr )
	{
		const char* pText = pLevel->GetText();
		char filepath[100];
		if( pText != nullptr )
			strcpy_s( filepath, 100, pText );

	
		//TCHAR buffer[100];
		//mbstowcs_s( nullptr, buffer, 100, filepath, _TRUNCATE );
		m_nBackgroundID =  ViewManager::GetInstance()->RegisterTexture(filepath);

		pLevel = pLevel->NextSiblingElement( "level_info" );

	}
	else
	{
		return false;
	}
	
	while( pLevel != nullptr )
	{
		//Read info from the node
		leveldata info = {};


		//Read name
		const char* pText = pLevel->GetText();
		if( pText != nullptr )
			strcpy_s( info.m_cType, 32, pText );
	
		//// Read attributes
		//pLevel->Attribute( "score", &info.nScore );
		double tmpX,tmpY,tmpH,tmpW;
		pLevel->Attribute( "x", &tmpX );
		pLevel->Attribute( "y", &tmpY );
		pLevel->Attribute( "width", &tmpW );
		pLevel->Attribute( "height", &tmpH );

		info.m_rCollision.left = (long)tmpX;
		info.m_rCollision.top = (long)tmpY;
		info.m_rCollision.right = long(tmpX+tmpW);
		info.m_rCollision.bottom = long(tmpY+tmpH);

		info.height = (long)tmpH;
		info.width = (long)tmpW;
		info.x = (long)tmpX;
		info.y = (long)tmpY;

		// Save this info to the vector
		m_vCollisions.push_back( info );

		// Move the next player node
		pLevel = pLevel->NextSiblingElement( "level_info" );
	}

	//m_nBackgroundID = CSGD_TextureManager::GetInstance()->LoadTexture(buffer, D3DCOLOR_XRGB(0,0,0));
	return true;
}



void Level::CheckCollision()
{

}