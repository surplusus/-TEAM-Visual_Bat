#pragma once
template<typename T, typename U>
class CFactory
{
public:
	CFactory() {};
	~CFactory() {};
public:
	static T* CreateObject(void)
	{
		T*	pObject = new U;
		pObject->Initialize();
		return pObject;
	}

	static T* CreateObject(const D3DXMATRIX* pMatrix)
	{
		T*	pObject = new U(pMatrix);
		pObject->Initialize();
		return pObject;
	}

};

