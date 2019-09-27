#include "BaseInclude.h"
#include "PipeLine.h"
#include"MathMgr.h"

CPipeLine::CPipeLine()
{
}


CPipeLine::~CPipeLine()
{
}

void CPipeLine::MakeMatrix_Projection(D3DXMATRIX* pMatrix
	, const float& fFovy
	, const float& fAspect
	, const float& fZn
	, const float& fZf)
{
	D3DXMatrixIdentity(pMatrix);

	float	fTmp = pMatrix->_34;
	pMatrix->_34 = pMatrix->_44;
	pMatrix->_44 = fTmp;

	pMatrix->_11 = (1.f / tanf(fFovy / 2.f)) / fAspect;
	pMatrix->_22 = 1.f / tanf(fFovy / 2.f);
	pMatrix->_33 = fZf / (fZf - fZn);
	pMatrix->_43 = -fZn * fZf / (fZf - fZn);
}

void CPipeLine::MakeMatrix_World(D3DXMATRIX* pMatrix
	, const D3DXVECTOR3* pScale
	, const float* pAngle
	, const D3DXVECTOR3* pPosition)
{
	D3DXVECTOR3		vRight, vUp, vLook, vPosition;

	vRight = D3DXVECTOR3(1.f, 0.f, 0.f);
	vUp = D3DXVECTOR3(0.f, 1.f, 0.f);
	vLook = D3DXVECTOR3(0.f, 0.f, 1.f);
	vPosition = D3DXVECTOR3(0.f, 0.f, 0.f);

	// 스케일 적용
	vRight *= pScale->x;
	vUp *= pScale->y;
	vLook *= pScale->z;

	// x축 회전
	CMathMgr::Rotation_X(&vRight, &vRight, pAngle[ANGLE_X]);
	CMathMgr::Rotation_X(&vUp, &vUp, pAngle[ANGLE_X]);
	CMathMgr::Rotation_X(&vLook, &vLook, pAngle[ANGLE_X]);

	// Y축 회전
	CMathMgr::Rotation_Y(&vRight, &vRight, pAngle[ANGLE_Y]);
	CMathMgr::Rotation_Y(&vUp, &vUp, pAngle[ANGLE_Y]);
	CMathMgr::Rotation_Y(&vLook, &vLook, pAngle[ANGLE_Y]);

	// Z축 회전
	CMathMgr::Rotation_Z(&vRight, &vRight, pAngle[ANGLE_Z]);
	CMathMgr::Rotation_Z(&vUp, &vUp, pAngle[ANGLE_Z]);
	CMathMgr::Rotation_Z(&vLook, &vLook, pAngle[ANGLE_Z]);

	vPosition = *pPosition;

	MakeMatrix(pMatrix, &vRight, &vUp, &vLook, &vPosition);
}

void CPipeLine::MakeMatrix_View(D3DXMATRIX* pMatrix
	, const D3DXVECTOR3* pEye
	, const D3DXVECTOR3* pAt
	, const D3DXVECTOR3* pUp)
{
	D3DXVECTOR3		vRight, vUp, vLook, vPosition;

	vLook = *pAt - *pEye;
	D3DXVec3Normalize(&vLook, &vLook);

	D3DXVec3Cross(&vRight, pUp, &vLook);
	D3DXVec3Normalize(&vRight, &vRight);

	D3DXVec3Cross(&vUp, &vLook, &vRight);
	D3DXVec3Normalize(&vUp, &vUp);

	vPosition = *pEye;

	MakeMatrix(pMatrix, &vRight, &vUp, &vLook, &vPosition);

	D3DXMatrixInverse(pMatrix, 0, pMatrix);
}

void CPipeLine::MakeMatrix(D3DXMATRIX* pMatrix
	, const D3DXVECTOR3* pRight
	, const D3DXVECTOR3* pUp
	, const D3DXVECTOR3* pLook
	, const D3DXVECTOR3* pPosition)
{
	D3DXMatrixIdentity(pMatrix);

	pMatrix->_11 = pRight->x;
	pMatrix->_12 = pRight->y;
	pMatrix->_13 = pRight->z;

	pMatrix->_21 = pUp->x;
	pMatrix->_22 = pUp->y;
	pMatrix->_23 = pUp->z;

	pMatrix->_31 = pLook->x;
	pMatrix->_32 = pLook->y;
	pMatrix->_33 = pLook->z;

	pMatrix->_41 = pPosition->x;
	pMatrix->_42 = pPosition->y;
	pMatrix->_43 = pPosition->z;
}


void CPipeLine::MySetTransform(D3DXVECTOR3* pOut, const D3DXVECTOR3& vPosition
	, const D3DXMATRIX&	 matTransform)
{
	MyVec3TransformCoord(pOut, &vPosition, &matTransform);
}

D3DXVECTOR3* CPipeLine::MyVec3TransformCoord(D3DXVECTOR3* pOut
	, const D3DXVECTOR3* pVector
	, const D3DXMATRIX* pMatrix)
{
	D3DXVECTOR4		vVector = D3DXVECTOR4(pVector->x, pVector->y, pVector->z, 1.f);

	pOut->x = vVector.x * pMatrix->_11
		+ vVector.y * pMatrix->_21
		+ vVector.z * pMatrix->_31
		+ vVector.w * pMatrix->_41;
	pOut->y = vVector.x * pMatrix->_12
		+ vVector.y * pMatrix->_22
		+ vVector.z * pMatrix->_32
		+ vVector.w * pMatrix->_42;
	pOut->z = vVector.x * pMatrix->_13
		+ vVector.y * pMatrix->_23
		+ vVector.z * pMatrix->_33
		+ vVector.w * pMatrix->_43;

	float		fW = vVector.x * pMatrix->_14
		+ vVector.y * pMatrix->_24
		+ vVector.z * pMatrix->_34
		+ vVector.w * pMatrix->_44;

	pOut->x /= fW;
	pOut->y /= fW;
	pOut->z /= fW;

	return pOut;
}


D3DXVECTOR3* CPipeLine::MyVec3TransformNormal(D3DXVECTOR3* pOut
	, const D3DXVECTOR3* pVector
	, const D3DXMATRIX* pMatrix)
{

	D3DXVECTOR4		vVector = D3DXVECTOR4(pVector->x, pVector->y, pVector->z, 0.f);

	pOut->x = vVector.x * pMatrix->_11
		+ vVector.y * pMatrix->_21
		+ vVector.z * pMatrix->_31
		+ vVector.w * pMatrix->_41;
	pOut->y = vVector.x * pMatrix->_12
		+ vVector.y * pMatrix->_22
		+ vVector.z * pMatrix->_32
		+ vVector.w * pMatrix->_42;
	pOut->z = vVector.x * pMatrix->_13
		+ vVector.y * pMatrix->_23
		+ vVector.z * pMatrix->_33
		+ vVector.w * pMatrix->_43;

	return pOut;
}