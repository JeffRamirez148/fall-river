#include <Windows.h>
using namespace std;

#ifndef __DestroyNPC_h__
#define __DestroyNPC_h__

// #include "NPC.h"
#include "Message.h"

class NPC;
// class Message;
class DestroyNPC;

class DestroyNPC: public Message
{
private: 
	NPC* _m_pNPC;
public:
	NPC* _unnamed_NPC_;

	DestroyNPC();

	~DestroyNPC();
};

#endif
