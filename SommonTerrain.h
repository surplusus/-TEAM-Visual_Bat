#pragma once
#include "Obj.h"
class CSommonTerrain :
	public CObj
{
public:
	CSommonTerrain();
	~CSommonTerrain();
private:
	LPD3DXMESH m_pMesh;
	INDEX* m_pIndex;
	LPDIRECT3DTEXTURE9 m_pAlphtexture;
public:	
	float m_fCamDistance;
public:
	virtual HRESULT			Initialize(void) override;
	virtual void			Progress(void)   override;
	virtual void			Render(void)     override;
	virtual void			Release(void)    override;



private:
	bool IsPicking();
	bool IntersectTriangle(const D3DXVECTOR3& ori, const D3DXVECTOR3& dir,
		D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2, float *t, float*u, float *v);
	void GetDeviceInformation();
	void SetRayViewSpace(float fx, float fy);
	void SetRayWorldSpace(float fx, float fy);
	bool IntersectTri(IN D3DXVECTOR3& v0, IN D3DXVECTOR3& v1, IN D3DXVECTOR3& v2, OUT D3DXVECTOR3& vPickedPosition);
private:
	D3DXMATRIXA16	m_matProj;
	D3DXMATRIXA16	m_matView;
	D3DXVECTOR3		m_vView;
	D3DVIEWPORT9	m_ViewPort;
	POINT			m_ptCursor;
	RAY				m_ray;
};

