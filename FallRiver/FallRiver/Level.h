#include <Windows.h>
#include <vector>
using namespace std;
#include "BaseObject.h"

#ifndef __Level_h__
#define __Level_h__

// #include "Terrain.h"
// #include "GamePlayState.h"
// #include "PickUp.h"

//class Terrain;
//class GamePlayState;
//class PickUp;
//class Level;

struct leveldata
{
	RECT m_rCollision;
	int height, width, x,y;
	char m_cType[ 32 ];
	bool m_bPrevColliding;
	int test;
};

struct mapTiles
{
	RECT m_rImageRect;
	float m_nWorldPosX,m_nWorldPosY;
	float height, width;
	int m_Layer;
	int m_nTileID;
	bool shadow;
};

struct TwoInts
{
	int x;
	int y;
};

class Level :  public BaseObject
{
private:
	vector<leveldata> m_vCollisions;
	vector<mapTiles> m_vTiles;
	//int m_nBackgroundID;
	float m_nPosX;
	float m_nPosY;
	TCHAR buffer[100];
	bool m_bNoClip;

public: 
	Level();

	~Level();

	//void Update(float time);
	bool LoadLevel( const char* szFilename );

	virtual void Update(float fElapsed);
	virtual void Render();
	static Level* GetInstance();

	virtual bool CheckCollision(IObjects* pBase);

	vector<leveldata> GetCollision() { return m_vCollisions;};
	void SetCollision(vector<leveldata> x) { m_vCollisions = x; };

	vector<mapTiles> GetTiles() { return m_vTiles;};
	void CheckTriangleCollisions();
	//void SetCollision(vector<mapTiles> x) { m_vTiles = x; };

};

#endif
