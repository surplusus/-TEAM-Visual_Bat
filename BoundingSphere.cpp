#include "BaseInclude.h"
#include "BoundingSphere.h"

CBoundingSphere::CBoundingSphere(float r, D3DXVECTOR3 p)
{
	m_fRadius = r;
	m_vCenter.x = p.x; m_vCenter.y = p.y; m_vCenter.z = p.z;
	m_vMin.x = p.x - r; m_vMin.y = p.y - r; m_vMin.z = p.z - r;
	m_vMax.x = p.x + r; m_vMax.y = p.y + r; m_vMax.z = p.z + r;
}

CBoundingSphere::~CBoundingSphere()
{
}

HRESULT CBoundingSphere::InitMesh(LPDIRECT3DDEVICE9 pDevice)
{
	if (FAILED(D3DXCreateSphere(pDevice,m_fRadius,10,10,&m_pMesh,NULL)))
		return E_FAIL;

	void*			pVtx = NULL;

	m_pMesh->LockVertexBuffer(0, &pVtx);

	//메쉬 버텍스 수
	DWORD dwVtxCnt = m_pMesh->GetNumVertices();

	DWORD dwVtxFVF = m_pMesh->GetFVF();

	UINT iVtxSize = D3DXGetFVFVertexSize(dwVtxFVF);

	D3DXComputeBoundingSphere((D3DXVECTOR3*)pVtx, dwVtxCnt, iVtxSize
		, &m_vCenter, &m_fRadius);

	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}
