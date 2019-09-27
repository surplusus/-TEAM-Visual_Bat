#include"BaseInclude.h"
#include "Mouse.h"

#include "ObjMgr.h"

CMouse::CMouse(void)
{
}

CMouse::~CMouse(void)
{
}

void CMouse::MouseToView(void)
{
	POINT		ptMouse;
	GetCursorPos(&ptMouse);

	// 뷰포트변환된 마우스 좌표
	ScreenToClient(g_hWnd, &ptMouse);

	// 투영공간으로 변환
	/*ptMouse.x = (2.f * ptMouse.x / WINSIZEX - 1.f);
	ptMouse.y = (-2.f * ptMouse.y / WINSIZEY + 1.f);*/

	D3DXMATRIX		matProj;
	GetTransform(D3DTS_PROJECTION, &matProj);

	// 뷰스페이스 영역성의 마우스 좌표
	vViewMousePt.x = (2.f * ptMouse.x / WINSIZEX - 1.f) / matProj._11;
	vViewMousePt.y = (-2.f * ptMouse.y / WINSIZEY + 1.f) / matProj._22;
	vViewMousePt.z = 1.f;

	vPivot = D3DXVECTOR3(0.f, 0.f, 0.f);
	vRay = vViewMousePt - vPivot;
}

void CMouse::RayToLocal(const TCHAR* pObjKey)
{
	D3DXMATRIX		matView;
	GetTransform(D3DTS_VIEW, &matView);
	const INFO* pInfo = GET_SINGLE(CObjMgr)->GetInfo(pObjKey);

	D3DXMATRIX		matWorld = pInfo->matWorld;

	D3DXMatrixInverse(&matView, 0, &matView);
	D3DXMatrixInverse(&matWorld, 0, &matWorld);


	// 월드영역으로
	D3DXVec3TransformCoord(&vPivot, &vPivot, &matView);
	D3DXVec3TransformNormal(&vRay, &vRay, &matView);

	// 로컬영역으로
	D3DXVec3TransformCoord(&vPivot, &vPivot, &matWorld);
	D3DXVec3TransformNormal(&vRay, &vRay, &matWorld);

	D3DXVec3Normalize(&vRay, &vRay);
}


bool CMouse::CollisionMouseToTerrain(void)
{
	MouseToView();
	RayToLocal(L"Terrain");

	float		fU, fV, fDist;

	const VTXTEX* pVtxTex = GET_SINGLE(CObjMgr)->GetVtxInfo(L"Terrain");

	for (int z = 0; z < VTXCNTZ - 1; ++z)
	{
		for (int x = 0; x < VTXCNTX - 1; ++x)
		{
			int			iIndex = z * VTXCNTX + x;
			// 오른쪽위
			if (D3DXIntersectTri(&pVtxTex[iIndex + VTXCNTX + 1].vPosition
				, &pVtxTex[iIndex + VTXCNTX].vPosition
				, &pVtxTex[iIndex + 1].vPosition
				, &vPivot, &vRay, &fU, &fV, &fDist))
			{
				vMousePos = pVtxTex[iIndex + VTXCNTX + 1].vPosition
					+ fU * (pVtxTex[iIndex + VTXCNTX].vPosition - pVtxTex[iIndex + VTXCNTX + 1].vPosition)
					+ fV * (pVtxTex[iIndex + 1].vPosition - pVtxTex[iIndex + VTXCNTX + 1].vPosition);
				return true;
			}


			// 왼쪽 아래
			if (D3DXIntersectTri(&pVtxTex[iIndex].vPosition
				, &pVtxTex[iIndex + 1].vPosition
				, &pVtxTex[iIndex + VTXCNTX].vPosition
				, &vPivot, &vRay, &fU, &fV, &fDist))
			{
				vMousePos = pVtxTex[iIndex].vPosition
					+ fU * (pVtxTex[iIndex + 1].vPosition - pVtxTex[iIndex].vPosition)
					+ fV * (pVtxTex[iIndex + VTXCNTX].vPosition - pVtxTex[iIndex].vPosition);
				return true;
			}
		}
	}
	return false;
}
