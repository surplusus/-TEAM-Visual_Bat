#include "BaseInclude.h"
#include "MathMgr.h"


CMathMgr::CMathMgr()
{
}


CMathMgr::~CMathMgr()
{
}
float CMathMgr::GetHeight(const VTXTEX* pVtxTex, const D3DXVECTOR3* pPosition)
{
	int iIndex = ((int(pPosition->z) / GAP) * VTXCNTX + int(pPosition->x) / GAP);

	float fRatioX = (pPosition->x - pVtxTex[iIndex + VTXCNTX].vPosition.x) / GAP;
	float fRatioZ = (pVtxTex[iIndex + VTXCNTX].vPosition.z - pPosition->z) / GAP;

	float	fHeight[4] = { pVtxTex[iIndex + VTXCNTX].vPosition.y
		, pVtxTex[iIndex + VTXCNTX + 1].vPosition.y
		, pVtxTex[iIndex + 1].vPosition.y
		, pVtxTex[iIndex].vPosition.y };

	// 우상
	if (fRatioX > fRatioZ)
	{
		return fHeight[0] + (fHeight[1] - fHeight[0]) * fRatioX + (fHeight[2] - fHeight[1]) * fRatioZ;
	}

	// 좌하
	else
	{
		return fHeight[0] + (fHeight[2] - fHeight[3]) * fRatioX + (fHeight[3] - fHeight[0]) * fRatioZ;
	}
}

void CMathMgr::Rotation_X(D3DXVECTOR3* pOut
	, const D3DXVECTOR3* pVector, const float& fAngle)
{
	// x 축 회전행렬
	/*
	1	0	0	0
	0	c	s	0
	0	-s	c	0
	0	0	0	1*/

	D3DXVECTOR3		vTmp = *pVector;

	pOut->x = vTmp.x;
	pOut->y = vTmp.y * cosf(fAngle) - vTmp.z * sinf(fAngle);
	pOut->z = vTmp.y * sinf(fAngle) + vTmp.z * cosf(fAngle);
}


void CMathMgr::Rotation_Y(D3DXVECTOR3* pOut, const D3DXVECTOR3* pVector, const float& fAngle)
{
	// Y 축 회전행렬
	/*
	C	0	-S	0
	0	1	0	0
	S	0	C	0
	0	0	0	1*/

	D3DXVECTOR3		vTmp = *pVector;

	pOut->x = vTmp.x * cosf(fAngle) + vTmp.z * sinf(fAngle);
	pOut->y = vTmp.y;
	pOut->z = vTmp.x * -sinf(fAngle) + vTmp.z * cosf(fAngle);
}

void CMathMgr::Rotation_Z(D3DXVECTOR3* pOut, const D3DXVECTOR3* pVector, const float& fAngle)
{
	//Z 축 회전행렬
	/*
	C	S	0	0
	-S	C	0	0
	0	0	1	0
	0	0	0	1*/

	D3DXVECTOR3		vTmp = *pVector;

	pOut->x = vTmp.x * cosf(fAngle) - vTmp.y * sinf(fAngle);
	pOut->y = vTmp.x * sinf(fAngle) + vTmp.y * cosf(fAngle);
	pOut->z = vTmp.z;
}
