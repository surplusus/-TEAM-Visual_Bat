#pragma once
class CBound
{
public:
	CBound();
	virtual ~CBound();
protected:
	LPD3DXMESH m_pMesh;
	D3DXVECTOR3 m_vMin, m_vMax;
public:
	virtual HRESULT InitMesh(LPDIRECT3DDEVICE9) PURE;
	virtual void Bound_Render();
	virtual const D3DXVECTOR3* GetMin() {
		return &m_vMin;
	}
	virtual const D3DXVECTOR3* GetMax()
	{
		return &m_vMax;
	}
	void Release();
};

