#pragma once

class CObj;

typedef struct Data
{
	const TCHAR* pKey;
	CObj*		 pObject;
}DATA, *PDATA;


class CObjMgr
{
private:
	list<list<PDATA>*>**	m_pObjects;
	DWORD					m_dwRevCnt;

public:
	const INFO*				GetInfo(const TCHAR* pObjKey, const int& iCnt = 0);
	const VTXTEX*			GetVtxInfo(const TCHAR* pObjKey, const int& iCnt = 0);
	const int				GetVtxNumber(const TCHAR*pObjKey, const int &iCnt = 0);
	void					Progress(void);
	void					Render(void);
	const D3DXVECTOR3*		GetMaxData(const TCHAR* pObjKey, const int& iCnt = 0);
	const D3DXVECTOR3*		GetMinData(const TCHAR* pObjKey, const int& iCnt = 0);

public:
	HRESULT					AddObject(const TCHAR* pObjKey, CObj* pObject);
	DWORD					Hashing(const TCHAR* pObjKey);
	void					Release(void);
	const CObj*				GetObj(const TCHAR* pObjKey, const int& iCnt = 0);
	CObjMgr*				CloneMgr();

public:
	static CObjMgr** GetInstance(void)
	{
		static CObjMgr* pInstance = NULL;
		if (pInstance == NULL)
			pInstance = new CObjMgr(HASH_COUNT);
		return &pInstance;
	}

	static void DestroyInstance(void)
	{
		CObjMgr**	ppInstance = GetInstance();
		delete *ppInstance;
		*ppInstance = NULL;
	}

private:
	CObjMgr(void);
	explicit CObjMgr(const int& iRevCnt);
public:
	~CObjMgr(void);
};