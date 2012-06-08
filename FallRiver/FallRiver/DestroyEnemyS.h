#include <Windows.h>
using namespace std;

#ifndef __DestroyEnemyS_h__
#define __DestroyEnemyS_h__

// #include "ShootingAi.h"
#include "Message.h"

class ShootingAi;
// class Message;
class DestroyEnemyS;

class DestroyEnemyS: public Message
{
private: 
	ShootingAi* _m_pEnemy;

public: 
	DestroyEnemyS();

	~DestroyEnemyS();
};

#endif
