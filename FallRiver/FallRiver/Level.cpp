#include <Windows.h>
#include <vector>
using namespace std;

#include "Level.h"
//#include "Terrain.h"
//#include "GamePlayState.h"
//#include "PickUp.h"
#include "tinyxml.h"
#include "ViewManager.h"

Level::Level() 
{
	m_nBackgroundID = -1;
}

Level* Level::GetInstance() 
{
	static Level s_Instance;
	return &s_Instance;
}

Level::~Level() 
{
}


void Level::Render() 
{
	ViewManager* pView = ViewManager::GetInstance();
	//CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();

	//m_nBackgroundID = pTM->LoadTexture(_T("resource/graphics/test.png"), D3DCOLOR_XRGB(0,0,0));
	//m_nBackgroundID = CSGD_TextureManager::GetInstance()->LoadTexture(buffer, D3DCOLOR_XRGB(0,0,0));
	//pView->RegisterTexture(

	if( m_nBackgroundID == -1)
	{
		return;
	}

	
	//m_nBackgroundID = pTM->LoadTexture(_T("resource/graphics/test.png"));
	pView->DrawStaticTexture(m_nBackgroundID,0, 0 );

	////<level_info x="0" y="0" height="64" width="1024">Wall</level_info>
 //   //<level_info x="0" y="0" height="512" width="64">Wall</level_info>
 //   //<level_info x="0" y="448" height="64" width="1024">Wall</level_info>
 //   //<level_info x="960" y="0" height="512" width="64">Wall</level_info>
 //   //<level_info x="20" y="4" height="64" width="64">Powerup</level_info>

	//RECT tmp1 = { 0, 0, 1024, 64 };
	//RECT tmp2 = { 0, 0, 64, 512 };
	//RECT tmp3 = { 0, 448, 1024, 448+64 };
	//RECT tmp4 = { 960, 0, 960+64, 512 };
	//RECT tmp5 = { 200, 200, 200+64, 200+64 };

	pView->GetSprite()->Flush();
	////pD3D->DrawLine(0,   0,    1024,   0,    1024,    64,   0,    64,     255,255,255);
	////pD3D->DrawLine(0,   0,      64,   0,      64,   512,   0,    512,     255,255,255);

	////pD3D->
	//pD3D->DrawLine(tmp1,255,255,255);
	//pD3D->DrawLine(tmp2,255,255,255);
	//pD3D->DrawLine(tmp3,255,255,255);
	//pD3D->DrawLine(tmp4,255,255,255);
	//pD3D->DrawLine(tmp5,0,255,255);
	
	for( int i = 0; i < m_vCollisions.size(); i++ )
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

		info.m_rCollision.left = tmpX;
		info.m_rCollision.top = tmpY;
		info.m_rCollision.right = tmpX+tmpW;
		info.m_rCollision.bottom = tmpY+tmpH;

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