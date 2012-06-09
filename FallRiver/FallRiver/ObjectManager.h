#ifndef __ObjectManager_h__
#define __ObjectManager_h__

class BaseObject;
#include <vector>
using namespace std;

class ObjectManager
{
private: 
	static ObjectManager * s_Instance;

	ObjectManager(void);
	virtual ~ObjectManager(void);
	ObjectManager(const ObjectManager&);
	ObjectManager& operator=(const ObjectManager&);

	typedef std::vector< BaseObject* >	ObjectList;
	typedef ObjectList::iterator	OListIterator;

	ObjectList m_Objects;

public: 
	void Enter();

	void Exit();

	bool Input();

	void AddObject( BaseObject* ptr );
	void RemoveObject( BaseObject* ptr );
	void RemoveAllObjects( void );

	void UpdateAllObjects(float fElapsedTime);

	void RenderAllObjects();

	void CheckCollisions();

	static ObjectManager* GetInstance();
	static void DeleteInstance( void );
};

#endif
