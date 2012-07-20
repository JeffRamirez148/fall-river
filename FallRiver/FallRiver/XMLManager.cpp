#include "XMLManager.h"
#include "PauseMenuState.h"
#include "MainMenuState.h"
#include "WinMenuState.h"
#include "OptionsMenuState.h"
#include "GamePlayState.h"
#include "LoadMenuState.h"
#include "ViewManager.h"
#include "Level.h"
#include "Emitter.h"
#include "Player.h"
#include "Weapon.h"
#include "Light.h"
#include "Font.h"
#include <string>

XMLManager* XMLManager::GetInstance(void)
{
	static XMLManager s_Instance;
	return &s_Instance;
}

Level* XMLManager::Parse(string aFile) 
{
	return NULL;
}

float* XMLManager::ParseSound(string aFile) 
{
	return 0;
}

void XMLManager::ParseAnim(char* aFile, Animation& anim)
{

}

Emitter* XMLManager::ParseEmitter(string aFile)
{
	TiXmlDocument doc;
	if( doc.LoadFile( aFile.c_str() ) == false )
		return false;
	TiXmlElement* pRoot = doc.RootElement();
	if( pRoot == nullptr )
		return false;
	TiXmlElement* pEmitter = pRoot->FirstChildElement("emitter_info");
	int blendModeS;
	int blendModeD;
	int endColor;
	double endRot;
	double endScaleX;
	double endScaleY;
	D3DXVECTOR3 endVel;
	int imageID;
	double lifeSpan;
	double lifeTime;
	int loopin;
	int maxParticles;
	RECT rect;
	double spawnRate;
	int startColor;
	double startRot;
	double startScaleX;
	double startScaleY;
	D3DXVECTOR3 startVel;
	int endAlpha;
	int endRed;
	int endGreen;
	int endBlue;
	int startAlpha;
	int startRed;
	int startGreen;
	int startBlue;
	double x;
	double y;
	double z;
	double left;
	double right;
	double top;
	double bottom;

	const char* pText = pEmitter->GetText();
	if( pText != NULL )
	{
		char imageFilePath[100];
		string finalFilePath = pText;
		finalFilePath = "resource/graphics/" + finalFilePath;
		if( pText != nullptr )
		strcpy_s( imageFilePath, 100, finalFilePath.c_str() );
		imageID = ViewManager::GetInstance()->RegisterTexture(imageFilePath);
	}
	else
		imageID = -1;

	pEmitter->Attribute("blendModeS", &blendModeS);
	pEmitter->Attribute("blendModeD", &blendModeD);
	pEmitter->Attribute("spawnRate", &spawnRate);
	pEmitter->Attribute("endAlpha", &endAlpha);
	pEmitter->Attribute("endRed",   &endRed);
	pEmitter->Attribute("endGreen", &endGreen);
	pEmitter->Attribute("endBlue",  &endBlue);
	endColor = (endAlpha << 24) | (endRed << 16) | (endGreen << 8) | endBlue;

	pEmitter->Attribute("endRot", &endRot);
	pEmitter->Attribute("endScaleX", &endScaleX);
	pEmitter->Attribute("endScaleY", &endScaleY);
	pEmitter->Attribute("endVelX", &x);
	pEmitter->Attribute("endVelY", &y);
	pEmitter->Attribute("endVelZ", &z);
	endVel.x = (float)x;
	endVel.y = (float)y;
	endVel.z = (float)z;
	pEmitter->Attribute("lifeSpan", &lifeSpan);
	pEmitter->Attribute("lifeTime", &lifeTime);
	pEmitter->Attribute("loopin", &loopin);
	pEmitter->Attribute("maxParticles", &maxParticles);
	pEmitter->Attribute("rectL", &left);
	pEmitter->Attribute("rectT", &top);
	pEmitter->Attribute("rectR", &right);
	pEmitter->Attribute("rectB", &bottom);
	rect.left = (LONG)left;
	rect.bottom = (LONG)bottom;
	rect.top = (LONG)top;
	rect.right = (LONG)right;
	pEmitter->Attribute("spawnRate",  &spawnRate);
	pEmitter->Attribute("startAlpha", &startAlpha);
	pEmitter->Attribute("startRed",   &startRed);
	pEmitter->Attribute("startGreen", &startGreen);
	pEmitter->Attribute("startBlue",  &startBlue);
	startColor = (startAlpha << 24) | (startRed << 16) | (startGreen << 8) | startBlue;
	pEmitter->Attribute("startRot", &startRot);
	pEmitter->Attribute("startScaleX", &startScaleX);
	pEmitter->Attribute("startScaleY", &startScaleY);
	pEmitter->Attribute("startVelX", &x);
	pEmitter->Attribute("startVelY", &y);
	pEmitter->Attribute("startVelZ", &z);
	startVel.x = (float)x;
	startVel.y = (float)y;
	startVel.z = (float)z;
	bool loop;
	if(loopin == 0)
		loop = false;
	else
		loop = true;

	Emitter* emitter = new Emitter( (float)spawnRate, loop, rect, maxParticles,startVel,endVel, (float)startScaleX, (float)startScaleY, (float)endScaleX, (float)endScaleY, blendModeS, blendModeD, imageID, (float)lifeSpan, (float)lifeTime, startColor, endColor, (float)startRot, (float)endRot);
	return emitter;
}

void XMLManager::SaveProgress( const char* szFilename, Player &player)
{
	// Create the TinyXML document
	TiXmlDocument doc;

	// Create the TinyXML declaration (version)
	TiXmlDeclaration* pDec = new TiXmlDeclaration( "1.0", "utf-8", "" );

	// Write the declaration to the document
	doc.LinkEndChild( pDec );

	// Create the root node for the "player"
	TiXmlElement* pRoot = new TiXmlElement( "player" );

	// Add the node to the document
	doc.LinkEndChild( pRoot );

	// Create a node for this player
	TiXmlElement* pPlayer = new TiXmlElement( "player_info" );

	// Fill the node with the player info
	pPlayer->SetAttribute( "score", player.GetScore() );
	pPlayer->SetAttribute( "lives", player.GetLives() );
	pPlayer->SetDoubleAttribute( "PosX", player.GetPosX() );
	pPlayer->SetDoubleAttribute( "PosY", player.GetPosY() );
	pPlayer->SetAttribute( "health", player.GetHealth() );
	pPlayer->SetAttribute( "battery", player.GetBattery() );
	pPlayer->SetDoubleAttribute( "time", player.GetTimePlayed() );
	//pPlayer->SetAttribute( "current_quest", player.Quest

	// Write this node to the root "player"
	pRoot->LinkEndChild( pPlayer );

	for(unsigned int i = 0; i < player.GetWeapons().size(); i++)
	{
		TiXmlElement* pWeapon = new TiXmlElement( "player_weapons" );

		// Saving all of the weapons info
		pWeapon->SetAttribute( "weapon_type", (int)player.GetWeapons()[i]->GetWeaponType());
		pWeapon->SetAttribute( "weapon_ammo", player.GetWeapons()[i]->GetAmmo());
		pWeapon->SetAttribute( "weapon_damage", player.GetWeapons()[i]->GetDamage());

		pRoot->LinkEndChild( pWeapon );
	}

	// TODO: UPDATE CODE
	//for(unsigned int i = 0; i < player.GetLights().size(); i++)
	//{
	//	TiXmlElement* pLight = new TiXmlElement( "player_lights" );
	//
	//	// Saving all of the lights info
	//	pLight->SetDoubleAttribute( "light_radius", player.GetLights()[i]->GetRadius());
	//
	//	pRoot->LinkEndChild( pLight );
	//}

	// Save the XML document
	doc.SaveFile( szFilename );
}

bool XMLManager::CheckSlot( const char* szFilename )
{
	// Create the TinyXML document
	TiXmlDocument doc;

	if(doc.LoadFile(szFilename) == false)
		return false;
	else
		return true;
}

Player* XMLManager::LoadProgress(const char* szFilename)
{
	// Create the TinyXML document
	TiXmlDocument doc;

	// Attempt to load the file
	if( doc.LoadFile( szFilename ) == false )
		return nullptr;

	
	// Access the root element ("player")
	TiXmlElement* pRoot = doc.RootElement();

	if( pRoot == nullptr )
		return nullptr;

	// Iterate through the nodes to load player data
	TiXmlElement* pPlayer = pRoot->FirstChildElement( "player_info" );

	Player* m_cPlayer = new Player();

	int nScore, nLives, nHealth, nBattery;
	double posX, posY, fTime;
	pPlayer->Attribute("score", &nScore);
	pPlayer->Attribute( "lives", &nLives );
	pPlayer->Attribute( "PosX", &posX );
	pPlayer->Attribute( "PosY", &posY );
	pPlayer->Attribute( "health", &nHealth );
	pPlayer->Attribute( "battery", &nBattery );
	pPlayer->Attribute( "time", &fTime);
	m_cPlayer->SetScore(nScore);
	m_cPlayer->SetLives(nLives);
	m_cPlayer->SetPosX((float)posX);
	m_cPlayer->SetPosY((float)posY);
	m_cPlayer->SetHealth(nHealth);
	m_cPlayer->SetBattery(nBattery);
	m_cPlayer->SetScore(nScore);
	m_cPlayer->SetTimePlayed((float)fTime);

	// Iterate through the nodes to load weapon data
	TiXmlElement* pWeapon = pPlayer->NextSiblingElement( "player_weapons" );

	while(pWeapon != nullptr)
	{
		Weapon* m_cWeapon = new Weapon();

		m_cWeapon->SetOwner(m_cPlayer);

		int wpnType, ammo, damage;
		pWeapon->Attribute("weapon_type", &wpnType); 
		pWeapon->Attribute("weapon_ammo", &ammo); 
		pWeapon->Attribute("weapon_damage", &damage);
		m_cWeapon->Init( wpnType, ammo, 0 );

		m_cPlayer->AddWeapon(m_cWeapon);

		// Move to the next weapon node
		pWeapon = pWeapon->NextSiblingElement( "player_weapons" );
	}

	// Iterate through the nodes to load weapon data
	TiXmlElement* pLight = pWeapon;

	while(pLight != nullptr)
	{
		Light m_cLight;

		int lightRad;
		pWeapon->Attribute("light_radius", &lightRad); 
		// TODO: UPDATE CODE
		//m_cLight.SetRadius((float)lightRad);

		m_cPlayer->AddLight(&m_cLight);

		// Move to the next weapon node
		pLight = pLight->NextSiblingElement( "player_lights" );
	}

	return m_cPlayer;
}

bool XMLManager::LoadFont( char* szFilename,  vector<Font>&fonts, vector<Kerning>&kerns)
{
	// Create the TinyXML document
	TiXmlDocument doc;

	// Attempt to load the file
	if( doc.LoadFile( szFilename ) == false )
		return false;
	
	// Access the root element ("player")
	TiXmlElement* pRoot = doc.RootElement();

	if( pRoot == nullptr )
		return nullptr;

	fonts.clear();
	
	// Iterate through the nodes to load player data
	TiXmlElement* pInfo = pRoot->FirstChildElement( "info" );
	pInfo = pInfo->NextSiblingElement("common");
	pInfo = pInfo->NextSiblingElement("pages");
	pInfo = pInfo->NextSiblingElement("chars");
	TiXmlElement* pChar = pInfo->FirstChildElement("char");

	while(pChar != nullptr)
	{
		Font pFont;

		pChar->Attribute("id", &pFont.id);
		pChar->Attribute("yoffset", &pFont.yoffset);
		pChar->Attribute("xoffset", &pFont.xoffset);
		pChar->Attribute("height", &pFont.height);
		pChar->Attribute("width", &pFont.width);
		pChar->Attribute("x", &pFont.x);
		pChar->Attribute("y", &pFont.y);

		fonts.push_back(pFont);

		pChar = pChar->NextSiblingElement( "char" );
	}

	TiXmlElement* pKerns = pInfo->NextSiblingElement("kernings");
	pKerns = pKerns->FirstChildElement("kerning");

	kerns.clear();

	while(pKerns != nullptr)
	{
		Kerning m_pKern;

		pKerns->Attribute("amount", &m_pKern.amount);
		pKerns->Attribute("second", &m_pKern.secondID);
		pKerns->Attribute("first", &m_pKern.firstID);

		kerns.push_back(m_pKern);

		pKerns = pKerns->NextSiblingElement("kerning");
	}
	

	return true;
}

				
void XMLManager::GeneratePlayers( vector< tHighscore >& vHighscore )
{
	vHighscore.clear();

	for( int i = 5; i > 0; i-- )
	{
		tHighscore p1 = {"Default", i };
		vHighscore.push_back(p1);
	}
}

bool XMLManager::LoadHighScores( const char* szFilename, vector< tHighscore >& vHighscore )
{
	TiXmlDocument doc;
	if( doc.LoadFile( szFilename ) == false )
		return false;
	TiXmlElement* pRoot = doc.RootElement();
	if( pRoot == nullptr )
		return false;
	vHighscore.clear();
	TiXmlElement* pHighscore = pRoot->FirstChildElement();
	while( pHighscore != nullptr )
	{
		tHighscore info = {};
		const char* pText = pHighscore->GetText();
		if( pText != nullptr )
			strcpy_s( info.szName, 32, pText );
		pHighscore->Attribute( "score", &info.nScore );
		vHighscore.push_back( info );
		pHighscore = pHighscore->NextSiblingElement();
	}
	return true;
}

void XMLManager::SaveHighScores( const char* szFilename, const vector<tHighscore>& vHighscore)
{
	TiXmlDocument doc;

	TiXmlDeclaration* pDec = new TiXmlDeclaration( "1.0","utf-8", "" );

	doc.LinkEndChild( pDec );
	TiXmlElement* pRoot = new TiXmlElement( "Highscore" );

	doc.LinkEndChild( pRoot );
	vector< tHighscore>::const_iterator iter;
	for(unsigned int i = 0; i < vHighscore.size(); i++)
	{
		TiXmlElement* pHighscore = new TiXmlElement( "Highscore_info");
		pHighscore->SetAttribute( "score", vHighscore[i].nScore );
		TiXmlText* pText = new TiXmlText( vHighscore[i].szName );
		pHighscore->LinkEndChild( pText );
		pRoot->LinkEndChild( pHighscore );
	}
	doc.SaveFile( szFilename );
}

bool XMLManager::LoadSettings( const char* szFilename, vector< int >& vSettings )
{
	TiXmlDocument doc;
	if( doc.LoadFile( szFilename ) == false )
		return false;
	TiXmlElement* pRoot = doc.RootElement();
	if( pRoot == nullptr )
		return false;
	vSettings.clear();
	TiXmlElement* pSetting = pRoot->FirstChildElement();

	if( pSetting != nullptr )
	{
		int info;
		pSetting->Attribute( "Music:", &info );
		vSettings.push_back( info );
		pSetting = pSetting->NextSiblingElement();
		pSetting->Attribute( "SFX:", &info );
		vSettings.push_back( info );
		pSetting = pSetting->NextSiblingElement();
		pSetting->Attribute( "Resolution:", &info );
		vSettings.push_back( info );
		pSetting = pSetting->NextSiblingElement();
	}

	return true;
}
void XMLManager::SaveSettings( const char* szFilename, const vector<int>& vSettings)
{
	TiXmlDocument doc;
	TiXmlDeclaration* pDec = new TiXmlDeclaration( "1.0","utf-8", "" );
	doc.LinkEndChild( pDec );
	TiXmlElement* pRoot = new TiXmlElement( "Setting" );
	doc.LinkEndChild( pRoot );
	if( !vSettings.empty() )
	{
		TiXmlElement* pSetting = new TiXmlElement( "setting_info");
		pSetting->SetAttribute( "Music:", vSettings[0] );
		pRoot->LinkEndChild( pSetting );
		pSetting = new TiXmlElement( "setting_info");
		pSetting->SetAttribute( "SFX:", vSettings[1] );
		pRoot->LinkEndChild( pSetting );
		pSetting = new TiXmlElement( "setting_info");
		pSetting->SetAttribute( "Resolution:", vSettings[2] );
		pRoot->LinkEndChild( pSetting );
	}
	doc.SaveFile( szFilename );

}

