#include "BaseInclude.h"
#include "MeshMgr.h"
#include "Mesh.h"
#include "StaticMesh.h"
#include "SkinnedMesh.h"


CMeshMgr::CMeshMgr()
{
}


CMeshMgr::~CMeshMgr()
{
}

void CMeshMgr::GetBonMatrix(const TCHAR * pMeshKey, const CHAR * pBoneName, D3DXMATRIX * pOut)
{
	map<const TCHAR*, CMesh*>::iterator iter = m_MapMesh.find(pMeshKey);
	if (iter == m_MapMesh.end()) return;
	
	iter->second->GetBonMatrix(pBoneName, pOut);
}

HRESULT CMeshMgr::AddMesh(LPDIRECT3DDEVICE9 pDevice, const TCHAR * pPath, const TCHAR * pFileName, const TCHAR * pMeshKey, MESHTYPE MeshType)
{
	map<const TCHAR*, CMesh*>::iterator iter = m_MapMesh.find(pMeshKey);
	
	CMesh* pMesh = NULL;
	if (iter == m_MapMesh.end())
	{
		switch (MeshType)
		{
		case MESHTYPE_STATIC:
			pMesh = new CStaticMesh;
			break;
		case MESHTYPE_DYNAMIC:
			pMesh = new CSkinnedMesh;
			break;
		}
		if (FAILED(pMesh->CreateMesh(pDevice, pPath, pFileName)))
			return E_FAIL;
		m_MapMesh.insert(make_pair(pMeshKey, pMesh));
	}
	else return E_FAIL;
	return S_OK;
}

void CMeshMgr::InvalidateMesh(const TCHAR * pMeshKey, D3DXMATRIX * pMatWorld)
{
	map<const TCHAR*, CMesh*>::iterator	iter = m_MapMesh.find(pMeshKey);

	if (iter == m_MapMesh.end())
		return;
	iter->second->InvalidateMesh(pMatWorld);
}

HRESULT CMeshMgr::CloneMesh(LPDIRECT3DDEVICE9 pDevice, const TCHAR * pMeshKey, CAnimationCtrl ** ppAniCtrl)
{
	map<const TCHAR*, CMesh*>::iterator	iter = m_MapMesh.find(pMeshKey);
	if (iter == m_MapMesh.end())
		return E_FAIL;
	return iter->second->CloneMesh(pDevice, ppAniCtrl);
}

void CMeshMgr::Release()
{

	for (map<const TCHAR*, CMesh*>::iterator iter =m_MapMesh.begin();
		iter != m_MapMesh.end(); ++iter)
	{
		if (iter->second)
		{
			delete iter->second;
			iter->second = NULL;
		}
	}
	m_MapMesh.clear();
}

void CMeshMgr::Mesh_Render(LPDIRECT3DDEVICE9 pDevice, const TCHAR * pMeshKey)
{

	map<const TCHAR*, CMesh*>::iterator	iter = m_MapMesh.find(pMeshKey);

	if (iter == m_MapMesh.end())
		return;

	iter->second->Render(pDevice);
}

LPD3DXMESH CMeshMgr::GetMesh(const TCHAR * pMeshKey)
{
	map<const TCHAR*, CMesh*>::iterator	iter = m_MapMesh.find(pMeshKey);
	if (iter == m_MapMesh.end()) return NULL;
	return iter->second->GetMesh();
}
