#include "BaseInclude.h"
#include "Frustum.h"

CFrustum::CFrustum(void)
{
	ZeroMemory(m_vPoint, sizeof(D3DXVECTOR3) * 8);
}

CFrustum::~CFrustum(void)
{
}

void CFrustum::InitFrustum(void)
{
	// 여덟개의 점은 투영공간상의 점이다.
	// -z
	m_vPoint[0] = D3DXVECTOR3(-1.f, 1.f, 0.f);
	m_vPoint[1] = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_vPoint[2] = D3DXVECTOR3(1.f, -1.f, 0.f);
	m_vPoint[3] = D3DXVECTOR3(-1.f, -1.f, 0.f);

	// +z
	m_vPoint[4] = D3DXVECTOR3(-1.f, 1.f, 1.f);
	m_vPoint[5] = D3DXVECTOR3(1.f, 1.f, 1.f);
	m_vPoint[6] = D3DXVECTOR3(1.f, -1.f, 1.f);
	m_vPoint[7] = D3DXVECTOR3(-1.f, -1.f, 1.f);

	// 투영공간상의 점을 뷰 공간상의 점으로 변환한다.
	D3DXMATRIX		matProj, matView;
	GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProj, 0, &matProj);

	GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, 0, &matView);


	for (int i = 0; i < 8; ++i)
	{
		// 뷰스페이스 영역상의 점으로 변환했다!
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &matProj);

		// 월드스페이스 영역으로 변환했다.
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &matView);
	}
}

void CFrustum::ConvertFrustum(VTXTEX* pVtxTex, const D3DXMATRIX* pMatrix)
{
	D3DXMATRIX		matWorld = *pMatrix;

	D3DXMatrixInverse(&matWorld, 0, &matWorld);

	for (int i = 0; i < 8; ++i)
		// 로컬 영역상의 점으로 변환했다!
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &matWorld);

	D3DXVECTOR3		vTmp[2];

	// +y
	D3DXPlaneFromPoints(&m_Plane[0], &m_vPoint[0], &m_vPoint[4], &m_vPoint[5]);
	// -y
	D3DXPlaneFromPoints(&m_Plane[1], &m_vPoint[7], &m_vPoint[3], &m_vPoint[2]);
	// +x
	D3DXPlaneFromPoints(&m_Plane[2], &m_vPoint[1], &m_vPoint[5], &m_vPoint[6]);
	// -x
	D3DXPlaneFromPoints(&m_Plane[3], &m_vPoint[4], &m_vPoint[0], &m_vPoint[3]);
	// +z
	D3DXPlaneFromPoints(&m_Plane[4], &m_vPoint[6], &m_vPoint[5], &m_vPoint[4]);
	// -z 
	D3DXPlaneFromPoints(&m_Plane[5], &m_vPoint[0], &m_vPoint[1], &m_vPoint[2]);
}


int CFrustum::Culling(VTXTEX* pVtxTex, INDEX* pIndex)
{
	DWORD			dwIndex[4];
	bool			bIn[4];
	int				iTriCnt = 0;

	for (int i = 0; i < (VTXCNTZ - 1); ++i)
	{
		for (int j = 0; j < VTXCNTX - 1; ++j)
		{
			int			iIndex = i * VTXCNTX + j;

			dwIndex[0] = iIndex + VTXCNTX;
			dwIndex[1] = iIndex + VTXCNTX + 1;
			dwIndex[2] = iIndex + 1;
			dwIndex[3] = iIndex;

			bIn[0] = VertexInFrustum(&pVtxTex[dwIndex[0]].vPosition);
			bIn[1] = VertexInFrustum(&pVtxTex[dwIndex[1]].vPosition);
			bIn[2] = VertexInFrustum(&pVtxTex[dwIndex[2]].vPosition);
			bIn[3] = VertexInFrustum(&pVtxTex[dwIndex[3]].vPosition);

			if (bIn[0] || bIn[1] || bIn[2])
			{
				pIndex[iTriCnt]._1 = dwIndex[0];
				pIndex[iTriCnt]._2 = dwIndex[1];
				pIndex[iTriCnt]._3 = dwIndex[2];
				++iTriCnt;
			}

			if (bIn[0] || bIn[2] || bIn[3])
			{
				pIndex[iTriCnt]._1 = dwIndex[0];
				pIndex[iTriCnt]._2 = dwIndex[2];
				pIndex[iTriCnt]._3 = dwIndex[3];
				++iTriCnt;
			}
		}
	}
	return iTriCnt;
}

bool CFrustum::VertexInFrustum(const D3DXVECTOR3* pPoint)
{
	for (int i = 0; i < 6; ++i)
	{
		float fDistance = D3DXPlaneDotCoord(&m_Plane[i], pPoint);

		if (fDistance > 0)
			return false;
	}
	return true;
}

bool CFrustum::SphereInFrustum(float fRadius, const D3DXVECTOR3* pPoint)
{
	float		fDistance;
	for (int i = 0; i < 6; ++i)
	{
		fDistance = D3DXPlaneDotCoord(&m_Plane[i], pPoint);
		if (fDistance > fRadius)
			return false;
	}
	return true;
}

bool CFrustum::SphereInFrustum(SPHERE * pSphere)
{
	float		fDistance;
	for (int i = 0; i < 6; ++i)
	{
		fDistance = D3DXPlaneDotCoord(&m_Plane[i], pSphere->vpCenter);
		if (fDistance > pSphere->fRadius)
			return false;
	}
	return true;
}
