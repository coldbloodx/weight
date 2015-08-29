#include "StdAfx.h"
#include <cassert>

#ifndef _SINGLETON_HEADER_
#define _SINGLETON_HEADER_

template<typename T>
class SingletonTemplateBase
{
private:
	static T* sm_instance;
protected:
	SingletonTemplateBase()
	{
		assert(sm_instance == NULL);
		sm_instance = static_cast<T*>(this);
	}
	virtual ~SingletonTemplateBase()
	{
		assert(sm_instance != NULL);
		sm_instance = 0;
	}	

public:
	static T* getInstancePtr()
	{
		if(sm_instance == NULL)
		{
			sm_instance = new T();
		}
		return sm_instance;
	}

	static T& getInstanceRef()
	{
		if(sm_instance == NULL)
		{
			sm_instance = new T();
		}
		return *sm_instance;
	}

	static void RemoveInstance()
	{
		assert(sm_instance);
		if(sm_instance)
		{
			delete sm_instance;
		}
		assert(sm_instance == NULL);
	}
};

template<typename T>
T* SingletonTemplateBase<T>::sm_instance = 0;
#endif