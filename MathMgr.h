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

public:
	//두 점을 통해 각도를 구한다.
	static void SetAngleFromPostion(OUT float& Angle, IN D3DXVECTOR3 vPos,IN D3DXVECTOR3 vPos2);
};

