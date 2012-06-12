#ifndef __DestroyNPC_h__
#define __DestroyNPC_h__

#include "Message.h"

class NPC;
class DestroyNPC: public Message
{
private: 
	NPC* _m_pNPC;
public:
	DestroyNPC(NPC* aNPC);
	NPC* GetNPC(void) {return _m_pNPC; }
	virtual ~DestroyNPC();
};

#endif
