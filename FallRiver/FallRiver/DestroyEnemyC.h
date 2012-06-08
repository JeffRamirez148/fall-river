#include <Windows.h>

#ifndef __DestroyEnemyC_h__
#define __DestroyEnemyC_h__

#include "Message.h"

// class Message;
class ChasingAi;

class DestroyEnemyC: public Message
{
private: 
	ChasingAi* m_pEnemy;

public:
	DestroyEnemyC();

	~DestroyEnemyC();
};

#endif
