#include <Windows.h>
using namespace std;

#ifndef __IListener_h__
#define __IListener_h__

// #include "EventSystem.h"
// #include "Event.h"
#include "Enemy.h"
#include "Bullet.h"

class EventSystem;
class Event;
// class Enemy;
// class Bullet;
class IListener;

class IListener: public Enemy, public Bullet
{
	IListener();
	~IListener();
	public: 
		virtual void HandleEvent(Event* aPEvent) = 0;
};

#endif
