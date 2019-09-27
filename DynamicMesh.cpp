#include "BaseInclude.h"
#include "DynamicMesh.h"
#include"AnimationCtrl.h"

void CDynamicMesh::GetBoneMatrix(const CHAR * pBoneName, D3DXMATRIX * pOut)
{

	FindBone(pBoneName, (BONE*)m_pRootBone, pOut);
}

void CDynamicMesh::FindBone(const CHAR * pBoneName, BONE * pBone, D3DXMATRIX * pOut)
{
	if (pBone->Name)
	{
		if (!strcmp(pBone->Name, pBoneName))
		{
			*pOut = pBone->matWorld;
		}
	}
	if (pBone->pFrameSibling)
		FindBone(pBoneName, (BONE*)pBone->pFrameSibling, pOut);
	if (pBone->pFrameFirstChild)
		FindBone(pBoneName, (BONE*)pBone->pFrameFirstChild, pOut);
}

HRESULT CDynamicMesh::CreateMesh(LPDIRECT3DDEVICE9 pDevice, const TCHAR * pPath, const TCHAR * pFileName)
{
	return E_FAIL;
}

HRESULT CDynamicMesh::CloneMesh(LPDIRECT3DDEVICE9 pDevice, CAnimationCtrl ** ppAniCtrl)
{
	*ppAniCtrl = m_pAniCtrl->Clone();
	return S_OK;
}

void CDynamicMesh::Render(LPDIRECT3DDEVICE9 pDevice, const BONE * pRootBone)
{
}

CDynamicMesh::CDynamicMesh()
{
}


CDynamicMesh::~CDynamicMesh()
{
}
