#include "BaseInclude.h"
#include "TextureMgr.h"
#include"CubeTexture.h"
#include"NormalTexture.h"

HRESULT CTextureMgr::InsertTexture(LPDIRECT3DDEVICE9 pDevice, TEXTYPE Type, const TCHAR * pFileName, const TCHAR * pObjectKey, const TCHAR * pStateKey, const int & iCnt, TERRIAN_INSERTTYPE InType)
{
	map<const TCHAR*, CTexture*>::iterator	iter = m_MapTexture.find(pObjectKey);

	if (iter != m_MapTexture.end())
	{
		if (FAILED(iter->second->InsertTexture(pDevice, pFileName, pStateKey, iCnt)))
			return E_FAIL;
	}

	else
	{
		CTexture*		pTexture = NULL;

		switch (Type)
		{
		case TEXTYPE_NORMAL:
			pTexture = new CNormalTexture;
			break;
		case TEXTYPE_CUBE:
			pTexture = new CCubeTexture;
			break;
		}

		if (FAILED(pTexture->InsertTexture(pDevice, pFileName, pStateKey, iCnt, InType)))
			return E_FAIL;

		m_MapTexture.insert(map<const TCHAR*, CTexture*>::value_type(pObjectKey, pTexture));

	}

	return S_OK;
}

const TEXINFO * CTextureMgr::GetTexture(const TCHAR * pObjectKey, const TCHAR * pStateKey, const int & iCnt)
{
	map<const TCHAR*, CTexture*>::iterator	iter = m_MapTexture.find(pObjectKey);

	if (iter == m_MapTexture.end())
		return NULL;
	else
		return iter->second->GetTexture(pStateKey, iCnt);
}

void CTextureMgr::Release()
{

	for (map<const TCHAR*, CTexture*>::iterator	iter = m_MapTexture.begin();
		iter != m_MapTexture.end(); ++iter)
	{
		if ((iter->second))
		{
			delete iter->second;
			iter->second = NULL;
		}
	}
	m_MapTexture.clear();
}

CTextureMgr::CTextureMgr()
{

}


CTextureMgr::~CTextureMgr()
{
	Release();
}
