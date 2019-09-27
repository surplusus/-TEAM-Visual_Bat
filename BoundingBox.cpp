#include "BaseInclude.h"
#include "BoundingBox.h"

CBoundingBox::CBoundingBox(D3DXVECTOR3 min, D3DXVECTOR3 max)
{
	m_vMin.x = min.x; m_vMin.y = min.y; m_vMin.z = min.z;
	m_vMax.x = max.x; m_vMax.y = max.y; m_vMax.z = max.z;
	m_fRadius = max.x - min.x;
	m_vCenter.x = max.x - min.x; m_vCenter.y = max.y - min.y; m_vCenter.z = max.z - min.z;
}

CBoundingBox::~CBoundingBox()
{
}

HRESULT CBoundingBox::InitMesh(LPDIRECT3DDEVICE9 pDevice)
{
	if (FAILED(D3DXCreateBox(pDevice, 1.0f, 1.f, 1.f, &m_pMesh, NULL)))
		return E_FAIL;

	void*			pVtx = NULL;

	m_pMesh->LockVertexBuffer(0, &pVtx);
	
	//메쉬 버텍스 수
	DWORD dwVtxCnt = m_pMesh->GetNumVertices();

	DWORD dwVtxFVF = m_pMesh->GetFVF();

	UINT iVtxSize = D3DXGetFVFVertexSize(dwVtxFVF);

	D3DXComputeBoundingBox((D3DXVECTOR3*)pVtx, dwVtxCnt, iVtxSize
		, &m_vMin, &m_vMax);

	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}
