#pragma once
class CMathMgr
{
public:
	CMathMgr();
	~CMathMgr();

public:
	static float GetHeight(const VTXTEX* pVtxTex, const D3DXVECTOR3* pPosition);
public:
	static void Rotation_X(D3DXVECTOR3* pOut
		, const D3DXVECTOR3* pVector, const float& fAngle);
	static void Rotation_Y(D3DXVECTOR3* pOut
		, const D3DXVECTOR3* pVector, const float& fAngle);
	static void Rotation_Z(D3DXVECTOR3* pOut
		, const D3DXVECTOR3* pVector, const float& fAngle);
};

