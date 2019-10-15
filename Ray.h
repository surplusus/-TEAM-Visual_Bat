#pragma once
class CRay
{
public:
	CRay();
	~CRay();
public:
	enum eRaySpace
	{
		E_NONE,
		E_VIEW,
		E_WORLD,
		E_LOCAL
	};


protected:
	D3DXVECTOR3 m_vOrg;
	D3DXVECTOR3 m_vDir;
	eRaySpace	m_eRaySpace;
	D3DXVECTOR3 m_vMousePos;
public:
	static CRay RayAtViewSpace(int nScreenX, int nScreenY);
	static CRay RayAtWorldSpace(int nScreenX, int nScreenY);

	bool IntersectTri(IN D3DXVECTOR3& v0,
		IN D3DXVECTOR3& v1,
		IN D3DXVECTOR3& v2,
		OUT D3DXVECTOR3& vPickedPosition);

	bool IsPicked(D3DXVECTOR3& vPos, D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2);

	D3DXVECTOR3 GetOrigin() { return m_vOrg; }
	void SetOrigin(D3DXVECTOR3 v) { m_vOrg = v; }
	D3DXVECTOR3 m_vDest;
	D3DXVECTOR3 GetDest() { return m_vDest; }
	void SetDest(D3DXVECTOR3 v) { m_vDest = v; }
};

