#include "XMLManager.h"
#include "PauseMenuState.h"
#include "MainMenuState.h"
#include "WinMenuState.h"
#include "DefeatMenuState.h"
#include "OptionsMenuState.h"
#include "GamePlayState.h"
#include "LoadMenuState.h"
#include "ViewManager.h"
#include "Level.h"
#include "Emitter.h"
#include "Player.h"
#include "Weapon.h"
#include "Light.h"

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

	double x;
	double y;
	double z;
	double left;
	double right;
	double top;
	double bottom;

	const char* pText = pEmitter->GetText();
	char imageFilePath[100];
	if( pText != nullptr )
		strcpy_s( imageFilePath, 100, pText );
	imageID = ViewManager::GetInstance()->RegisterTexture(imageFilePath);

	pEmitter = pEmitter->NextSiblingElement("emitter_info");
	pEmitter->Attribute("blendModeS", &blendModeS);
	pEmitter->Attribute("blendModeD", &blendModeD);
	pEmitter->Attribute("endColor", &endColor);
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
	pEmitter->Attribute("spawnRate", &spawnRate);
	pEmitter->Attribute("startColor", &startColor);
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

	for(unsigned int i = 0; i < player.GetLights().size(); i++)
	{
		TiXmlElement* pLight = new TiXmlElement( "player_lights" );

		// Saving all of the lights info
		pLight->SetDoubleAttribute( "light_radius", player.GetLights()[i]->GetRadius());

		pRoot->LinkEndChild( pLight );
	}

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

	int nScore, nLives;
	double posX, posY;
	pPlayer->Attribute("score", &nScore);
	pPlayer->Attribute( "lives", &nLives );
	pPlayer->Attribute( "PosX", &posX );
	pPlayer->Attribute( "PosY", &posY );
	m_cPlayer->SetScore(nScore);
	m_cPlayer->SetLives(nLives);
	m_cPlayer->SetPosX((float)posX);
	m_cPlayer->SetPosY((float)posY);
	

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
		m_cWeapon->Init( wpnType, ammo, damage, 0 );

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
		m_cLight.SetRadius((float)lightRad);

		m_cPlayer->AddLight(&m_cLight);

		// Move to the next weapon node
		pLight = pLight->NextSiblingElement( "player_lights" );
	}

	return m_cPlayer;
}
