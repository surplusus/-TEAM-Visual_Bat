#pragma once
template<typename T, typename T1>
class CFactory
{
public:
	CFactory() {};
	~CFactory() {};
public:
	static T* CreateObject(void)
	{
		T*	pObject = new T1;
		pObject->Initialize();
		return pObject;
	}

	static T* CreateObject(const D3DXMATRIX* pMatrix)
	{
		T*	pObject = new T1(pMatrix);
		pObject->Initialize();
		return pObject;
	}

};

