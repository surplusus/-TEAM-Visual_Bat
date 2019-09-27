#pragma once
class CBound
{
public:
	CBound();
	virtual ~CBound();
protected:
	LPD3DXMESH m_pMesh;
	D3DXVECTOR3 m_vMin, m_vMax;
	D3DXVECTOR3 m_vCenter;
	float		m_fRadius;
public:
	virtual HRESULT InitMesh(LPDIRECT3DDEVICE9) PURE;
	virtual void Bound_Render();
	virtual const D3DXVECTOR3* GetMin();
	virtual const D3DXVECTOR3* GetMax();
	virtual const D3DXVECTOR3* GetCenter();
	virtual const float		   GetRadius();
	void Release();
};

