#include"BaseInclude.h"
#include "ObjMgr.h"

#include "Obj.h"

CObjMgr::CObjMgr(void)
	: m_pObjects(NULL)
	, m_dwRevCnt(0)
	
{

}
CObjMgr::CObjMgr(const int& iRevCnt)
	: m_dwRevCnt(iRevCnt)
{
	m_pObjects = new list<list<PDATA>*>*[iRevCnt];
	ZeroMemory(m_pObjects, sizeof(list<list<PDATA>*>*) * iRevCnt);
}

CObjMgr::~CObjMgr(void)
{
	Release();
}
const INFO* CObjMgr::GetInfo(const TCHAR* pObjKey, const int& iCnt/* = 0*/)
{
	DWORD	dwIndex = Hashing(pObjKey);

	for (list<list<PDATA>*>::iterator iter = m_pObjects[dwIndex]->begin();
		iter != m_pObjects[dwIndex]->end(); ++iter)
	{
		if (!(lstrcmp((*iter)->front()->pKey, pObjKey)))
		{
			list<PDATA>::iterator	iter1 = (*iter)->begin();

			for (int i = 0; i < iCnt; ++i)
				++iter1;

			return (*iter1)->pObject->GetInfo();
		}
	}
	return NULL;
}
HRESULT CObjMgr::AddObject(const TCHAR* pObjKey, CObj* pObject)
{
	DWORD	dwIndex = Hashing(pObjKey);

	if (pObject == NULL)
		return E_FAIL;

	PDATA pData = new DATA;
	pData->pObject = pObject;
	pData->pKey = pObjKey;

	if (m_pObjects[dwIndex] == NULL)
	{
		list<list<PDATA>*>*	pLargeList = new (list<list<PDATA>*>);

		list<PDATA>*	pSmallList = new (list<PDATA>);

		pSmallList->push_back(pData);

		pLargeList->push_back(pSmallList);

		m_pObjects[dwIndex] = pLargeList;
	}
	// Crush
	else
	{
		for (list<list<PDATA>*>::iterator iter = m_pObjects[dwIndex]->begin();
			iter != m_pObjects[dwIndex]->end(); ++iter)
		{
			if (!(lstrcmp((*iter)->front()->pKey, pObjKey)))
			{
				(*iter)->push_back(pData);
				return S_OK;
			}
		}

		// 스몰리스트중에 집어넣으려고하는 키를 가진 리스트가 없었다.
		list<PDATA>*	pSmallList = new list<PDATA>;
		pSmallList->push_back(pData);
		m_pObjects[dwIndex]->push_back(pSmallList);
	}

	return S_OK;
}

DWORD CObjMgr::Hashing(const TCHAR* pObjKey)
{
	DWORD dwLength = lstrlen(pObjKey);

	DWORD dwIndex = -1;

	for (DWORD i = 0; i < dwLength; ++i)
	{
		dwIndex += pObjKey[i];
	}

	return dwIndex %= m_dwRevCnt;
}

const VTXTEX* CObjMgr::GetVtxInfo(const TCHAR* pObjKey, const int& iCnt /*= 0*/)
{
	DWORD	dwIndex = Hashing(pObjKey);

	for (auto iter = m_pObjects[dwIndex]->begin();
		iter != m_pObjects[dwIndex]->end(); ++iter)
	{
		if (!(lstrcmp((*iter)->front()->pKey, pObjKey)))
		{
			list<PDATA>::iterator	iter1 = (*iter)->begin();

			for (int i = 0; i < iCnt; ++i)
				++iter1;

			return (*iter1)->pObject->GetVtxInfo();
		}
	}

	return NULL;
}

const int CObjMgr::GetVtxNumber(const TCHAR * pObjKey, const int & iCnt)
{
	DWORD	dwIndex = Hashing(pObjKey);

	for (list<list<PDATA>*>::iterator iter = m_pObjects[dwIndex]->begin();
		iter != m_pObjects[dwIndex]->end(); ++iter)
	{
		if (!(lstrcmp((*iter)->front()->pKey, pObjKey)))
		{
			list<PDATA>::iterator	iter1 = (*iter)->begin();

			for (int i = 0; i < iCnt; ++i)
				++iter1;

			return (*iter1)->pObject->GetVtxNumber();
		}
	}
	return 0;
}



void CObjMgr::Progress(void)
{
	for (DWORD i = 0; i < m_dwRevCnt; ++i)
	{
		if (m_pObjects[i] == NULL)
			continue;
		for (list<list<PDATA>*>::iterator	iter = m_pObjects[i]->begin();
			iter != m_pObjects[i]->end(); ++iter)
		{
			for (list<PDATA>::iterator	iter1 = (*iter)->begin();
				iter1 != (*iter)->end(); ++iter1)
			{
				(*iter1)->pObject->Progress();
			}
		}
	}
}

void CObjMgr::Render(void)
{
	for (DWORD i = 0; i < m_dwRevCnt; ++i)
	{
		if (m_pObjects[i] == NULL)
			continue;
		for (list<list<PDATA>*>::iterator	iter = m_pObjects[i]->begin();
			iter != m_pObjects[i]->end(); ++iter)
		{
			for (list<PDATA>::iterator	iter1 = (*iter)->begin();
				iter1 != (*iter)->end(); ++iter1)
			{
				(*iter1)->pObject->Render();
			}
		}
	}
}

const D3DXVECTOR3* CObjMgr::GetMaxData(const TCHAR* pObjKey
	, const int& iCnt/* = 0*/)
{
	DWORD	dwIndex = Hashing(pObjKey);

	for (list<list<PDATA>*>::iterator iter = m_pObjects[dwIndex]->begin();
		iter != m_pObjects[dwIndex]->end(); ++iter)
	{
		if (!(lstrcmp((*iter)->front()->pKey, pObjKey)))
		{
			list<PDATA>::iterator	iter1 = (*iter)->begin();

			for (int i = 0; i < iCnt; ++i)
				++iter1;

			return (*iter1)->pObject->GetMaxData();
		}
	}
	return NULL;
}

const D3DXVECTOR3* CObjMgr::GetMinData(const TCHAR* pObjKey
	, const int& iCnt/* = 0*/)
{
	DWORD	dwIndex = Hashing(pObjKey);

	for (list<list<PDATA>*>::iterator iter = m_pObjects[dwIndex]->begin();
		iter != m_pObjects[dwIndex]->end(); ++iter)
	{
		if (!(lstrcmp((*iter)->front()->pKey, pObjKey)))
		{
			list<PDATA>::iterator	iter1 = (*iter)->begin();

			for (int i = 0; i < iCnt; ++i)
				++iter1;

			return (*iter1)->pObject->GetMinData();
		}
	}
	return NULL;
}

void CObjMgr::Release(void)
{
	for (DWORD i = 0; i < m_dwRevCnt; ++i)
	{
		if (m_pObjects[i] == NULL)
			continue;
		for (list<list<PDATA>*>::iterator	iter = m_pObjects[i]->begin();
			iter != m_pObjects[i]->end(); ++iter)
		{
			for (list<PDATA>::iterator	iter1 = (*iter)->begin();
				iter1 != (*iter)->end(); ++iter1)
			{
				if ((*iter1))
				{
					if ((*iter1)->pObject)
					{
						delete (*iter1)->pObject;
						(*iter1)->pObject = NULL;
					}
					delete *iter1;
					*iter1 = NULL;
				}
			}
			(*iter)->clear();

			delete (*iter);
			(*iter) = NULL;
		}

		m_pObjects[i]->clear();

		delete m_pObjects[i];
		m_pObjects[i] = NULL;
	}

	delete[] m_pObjects;
	m_pObjects = NULL;
}

const CObj * CObjMgr::GetObj(const TCHAR * pObjKey, const int & iCnt)
{
	DWORD	dwIndex = Hashing(pObjKey);

	for (list<list<PDATA>*>::iterator iter = m_pObjects[dwIndex]->begin();
		iter != m_pObjects[dwIndex]->end(); ++iter)
	{
		if (!(lstrcmp((*iter)->front()->pKey, pObjKey)))
		{
			list<PDATA>::iterator	iter1 = (*iter)->begin();

			for (int i = 0; i < iCnt; ++i)
				++iter1;

			return (*iter1)->pObject;
		}
	}
	return nullptr;
}

CObjMgr * CObjMgr::CloneMgr()
{
	return this;
}
