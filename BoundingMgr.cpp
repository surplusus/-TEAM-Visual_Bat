#include "BaseInclude.h"
#include "BoundingMgr.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"

CBoundingMgr::CBoundingMgr()
{
}


CBoundingMgr::~CBoundingMgr()
{
	Release();
}

HRESULT CBoundingMgr::AddBounding(LPDIRECT3DDEVICE9 pDevice, BOUNDTYPE Type)
{
	CBound*			pBound = NULL;

	switch (Type)
	{
	case BOUNDTYPE_SPHERE:
		pBound = new CBoundingSphere();
		break;
	case BOUNDTYPE_CUBE:
		pBound = new CBoundingBox();
		break;
	}
	if (FAILED(pBound->InitMesh(pDevice)))
		return E_FAIL;

	m_MapBounding.insert(make_pair(Type, pBound));

	return S_OK;
}

void CBoundingMgr::Bound_Render(BOUNDTYPE Type)
{

	map<BOUNDTYPE, CBound*>::iterator	iter = m_MapBounding.find(Type);

	iter->second->Bound_Render();
}

void CBoundingMgr::Release()
{

	for (map<BOUNDTYPE, CBound*>::iterator	iter = m_MapBounding.begin();
		iter != m_MapBounding.end(); ++iter)
	{
		if (iter->second)
		{
			delete (iter->second);
			(iter->second) = NULL;
		}
	}
}

const D3DXVECTOR3 * CBoundingMgr::GetMin(BOUNDTYPE Type)
{

	map<BOUNDTYPE, CBound*>::iterator	iter = m_MapBounding.find(Type);

	return iter->second->GetMin();
}

const D3DXVECTOR3 * CBoundingMgr::GetMax(BOUNDTYPE Type)
{

	map<BOUNDTYPE, CBound*>::iterator	iter = m_MapBounding.find(Type);

	return iter->second->GetMax();
}
