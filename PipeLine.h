#pragma once
class CPipeLine
{
public:
	CPipeLine();
	~CPipeLine();
public:

	static void MakeMatrix_World(D3DXMATRIX* pMatrix
		, const D3DXVECTOR3* pScale
		, const float* pAngle
		, const D3DXVECTOR3* pPosition);

	static void MakeMatrix_View(D3DXMATRIX* pMatrix
		, const D3DXVECTOR3* pEye
		, const D3DXVECTOR3* pAt
		, const D3DXVECTOR3* pUp);

	static void MakeMatrix_Projection(D3DXMATRIX* pMatrix
		, const float& fFovy
		, const float& fAspect
		, const float& fZn
		, const float& fZf);

	static void MakeMatrix(D3DXMATRIX* pMatrix
		, const D3DXVECTOR3* pRight
		, const D3DXVECTOR3* pUp
		, const D3DXVECTOR3* pLook
		, const D3DXVECTOR3* pPosition);
public:
	static void MySetTransform(D3DXVECTOR3* pOut, const D3DXVECTOR3& vPosition
		, const D3DXMATRIX&	 matTransform);
public:
	static D3DXVECTOR3* MyVec3TransformCoord(D3DXVECTOR3* pOut
		, const D3DXVECTOR3* pVector
		, const D3DXMATRIX* pMatrix);
	static D3DXVECTOR3* MyVec3TransformNormal(D3DXVECTOR3* pOut
		, const D3DXVECTOR3* pVector
		, const D3DXMATRIX* pMatrix);
};

