#include"BaseInclude.h"
#include "SkinnedMesh.h"
#include "AnimationCtrl.h"

CSkinnedMesh::CSkinnedMesh(void)
{
}

CSkinnedMesh::~CSkinnedMesh(void)
{

	Release();

}

HRESULT CSkinnedMesh::CreateMesh(LPDIRECT3DDEVICE9 pDevice
	, const TCHAR* pPathName, const TCHAR* pFileName)
{
	TCHAR			szPath[128] = L"";

	lstrcpy(szPath, pPathName);
	lstrcat(szPath, pFileName);

	m_pLoader = new CHierachyLoader(pPathName);

	m_pAniCtrl = new CAnimationCtrl;

	if (FAILED(D3DXLoadMeshHierarchyFromX(szPath, D3DXMESH_MANAGED
		, pDevice, m_pLoader, NULL, &m_pRootBone, m_pAniCtrl->GetAniCtrl())))
		return E_FAIL;

	D3DXMATRIX		matrix;
	D3DXMatrixIdentity(&matrix);

	UpdateMatrix((BONE*)m_pRootBone, &matrix);
	SetUpBoneMatrixPointer((BONE*)m_pRootBone);
	ID3DXBuffer* adjBuffer;

	return S_OK;
}

void CSkinnedMesh::SetUpBoneMatrixPointer(BONE* pBone)
{
	if (pBone->pMeshContainer)
	{
		BONEMESH*		pBoneMesh = (BONEMESH*)pBone->pMeshContainer;

		if (pBoneMesh->pSkinInfo)
		{
			int		iNumBone = pBoneMesh->pSkinInfo->GetNumBones();

			pBoneMesh->ppBoneMatrix = new D3DXMATRIX*[iNumBone];

			for (int i = 0; i < iNumBone; ++i)
			{
				BONE*		pLinkedBone = (BONE*)D3DXFrameFind(m_pRootBone
					, pBoneMesh->pSkinInfo->GetBoneName(i));

				if (pLinkedBone)
				{
					pBoneMesh->ppBoneMatrix[i] = &pLinkedBone->matWorld;
				}
				else
					pBoneMesh->ppBoneMatrix[i] = NULL;
			}
		}
	}

	if (pBone->pFrameSibling)
	{
		SetUpBoneMatrixPointer((BONE*)pBone->pFrameSibling);
	}

	if (pBone->pFrameFirstChild)
	{
		SetUpBoneMatrixPointer((BONE*)pBone->pFrameFirstChild);
	}


}

void CSkinnedMesh::UpdateMatrix(BONE* pBone, D3DXMATRIX* pParentMatrix)
{
	if (pBone == NULL)
		return;

	//pBone->matWorld = pBone->TransformationMatrix * *pParentMatrix;
	D3DXMatrixMultiply(&pBone->matWorld, &pBone->TransformationMatrix
		, pParentMatrix);

	if (pBone->pFrameSibling)
	{
		UpdateMatrix((BONE*)pBone->pFrameSibling
			, pParentMatrix);
	}

	if (pBone->pFrameFirstChild)
	{
		UpdateMatrix((BONE*)pBone->pFrameFirstChild
			, &pBone->matWorld);
	}
}

void CSkinnedMesh::Render(LPDIRECT3DDEVICE9 pDevice, const BONE* pBone)
{
	if (pBone == NULL)
	{
		pBone = (BONE*)m_pRootBone;
	}

	if (pBone->pMeshContainer)
	{
		BONEMESH*			pBoneMesh = (BONEMESH*)pBone->pMeshContainer;

		if (pBoneMesh->pSkinInfo)
		{
			int		iNumBone = pBoneMesh->pSkinInfo->GetNumBones();

			for (int i = 0; i < iNumBone; ++i)
			{
				D3DXMatrixMultiply(&pBoneMesh->pCurrentBoneMatrix[i]
					, &pBoneMesh->pBoneoffSetMatrix[i]
					, pBoneMesh->ppBoneMatrix[i]);
			}
			 
			BYTE*		pSour;
			BYTE*		pDest;

			pBoneMesh->pOriMesh->LockVertexBuffer(0, (void**)&pSour);

			pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&pDest);

			pBoneMesh->pSkinInfo->UpdateSkinnedMesh(pBoneMesh->pCurrentBoneMatrix
				, NULL, pSour, pDest);

			pBoneMesh->pOriMesh->UnlockVertexBuffer();
			pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();

			for (int i = 0; i < pBoneMesh->NumMaterials; ++i)
			{
				int		mtrl = pBoneMesh->pAttTable[i].AttribId;

				pDevice->SetMaterial(&pBoneMesh->vecMtrl[mtrl]);
				pDevice->SetTexture(0, pBoneMesh->vecTexture[mtrl]);

				pBoneMesh->MeshData.pMesh->DrawSubset(i);
			}
		}
	}
	if (pBone->pFrameSibling)
	{
		Render(pDevice, (BONE*)pBone->pFrameSibling);
	}

	if (pBone->pFrameFirstChild)
	{
		Render(pDevice, (BONE*)pBone->pFrameFirstChild);
	}
}

void CSkinnedMesh::Release(void)
{
	if (m_pLoader)
	{
		m_pLoader->DestroyFrame(m_pRootBone);
		delete m_pLoader;
		m_pLoader = NULL;
	}


	if (m_pAniCtrl)
	{
		delete m_pAniCtrl;
		m_pAniCtrl = NULL;
	}

}

void CSkinnedMesh::InvalidateMesh(D3DXMATRIX* pMatWorld)
{
	UpdateMatrix((BONE*)m_pRootBone, pMatWorld);
}
