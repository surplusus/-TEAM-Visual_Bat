#pragma once


class CMouse
{
	DECLARE_SINGLETON(CMouse);
private:
	D3DXVECTOR3			vViewMousePt;

	D3DXVECTOR3			vMousePos;

	D3DXVECTOR3			vPivot;
	D3DXVECTOR3			vRay;
public:
	const D3DXVECTOR3* GetMousePos(void) {
		return &vMousePos;
	}
public:
	void MouseToView(void);
	void RayToLocal(const TCHAR* pObjKey);
	bool CollisionMouseToTerrain(void);

private:
	CMouse(void);
public:
	~CMouse(void);
};
