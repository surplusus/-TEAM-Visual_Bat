#include "BaseInclude.h"
#include "MeshMgr.h"
#include "Mesh.h"
#include "StaticMesh.h"
#include "SkinnedMesh.h"

map<string, const TCHAR*> g_mapObjMeshName;
int g_iTotalSubSet = -1;
int g_iLoadingSubSet = -1;

CMeshMgr::CMeshMgr()
{
}


CMeshMgr::~CMeshMgr()
{
}

void CMeshMgr::GetBoneMatrix(const TCHAR * pMeshKey, const CHAR * pBoneName, D3DXMATRIX * pOut)
{
	map<const TCHAR*, CMesh*>::iterator iter = m_MapMesh.find(pMeshKey);
	if (iter == m_MapMesh.end()) return;

	iter->second->GetBoneMatrix(pBoneName, pOut);
}

HRESULT CMeshMgr::AddMesh(LPDIRECT3DDEVICE9 pDevice, const TCHAR * pPath, const TCHAR * pFileName, const TCHAR * pMeshKey, MESHTYPE MeshType)
{

	map<const TCHAR*, CMesh*>::iterator iter = m_MapMesh.find(pMeshKey);

	CMesh* pMesh = NULL;
	if (iter == m_MapMesh.end())
	{
		// 로딩 정보
		g_iTotalSubSet = 0;
		g_iLoadingSubSet = 0;

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

		// 로딩 정보
		//CMeshMgr::g_iTotalSubSet = -1;
		//CMeshMgr::g_iLoadingSubSet = -1;
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
	for (map<const TCHAR*, CMesh*>::iterator iter = m_MapMesh.begin();
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

CMesh* CMeshMgr::GetMesh(const TCHAR * pMeshKey)
{
	map<const TCHAR*, CMesh*>::iterator	iter = m_MapMesh.find(pMeshKey);
	if (iter == m_MapMesh.end()) return NULL;
	return iter->second;
}
