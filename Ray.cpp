#include "BaseInclude.h"
#include "Ray.h"


CRay::CRay()
{

}

CRay::~CRay()
{

}

CRay CRay::RayAtViewSpace(int nScreenX, int nScreenY)
{
	D3DVIEWPORT9 vp;
	GET_SINGLE(CDevice)->GetDevice()->GetViewport(&vp);

	D3DXMATRIXA16 matProj;
	GetTransform(D3DTS_PROJECTION, &matProj);

	CRay r;
	r.m_vDir.x = ((2.0 * nScreenX) / vp.Width - 1.0f) / matProj._11;
	r.m_vDir.y = ((-2.0 * nScreenY) / vp.Height + 1.0f) / matProj._22;
	r.m_vDir.z = 1.0f;

	r.m_eRaySpace = E_VIEW;
	r.m_vOrg = { 0,0,0 };
	return r;
}

CRay CRay::RayAtWorldSpace(int nScreenX, int nScreenY)
{
	CRay r = CRay::RayAtViewSpace(nScreenX, nScreenY);

	assert(r.m_eRaySpace == E_VIEW);

	D3DXMATRIXA16 matView, matInvView;
	GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixInverse(&matInvView, 0, &matView);

	D3DXVec3TransformCoord(&r.m_vOrg, &r.m_vOrg, &matInvView);
	D3DXVec3TransformNormal(&r.m_vDir, &r.m_vDir, &matInvView);

	D3DXVec3Normalize(&r.m_vDir, &r.m_vDir);

	r.m_eRaySpace = E_WORLD;
	return r;
}

bool CRay::IntersectTri(IN D3DXVECTOR3 & v0, IN D3DXVECTOR3 & v1, IN D3DXVECTOR3 & v2, OUT D3DXVECTOR3 & vPickedPosition)
{

	float u, v, t;
	bool b = D3DXIntersectTri(&v0, &v1, &v2, &m_vOrg, &m_vDir, &u, &v, &t);
	vPickedPosition = m_vOrg + t * m_vDir;
	return b;
}

bool CRay::IsPicked(D3DXVECTOR3& vPos,D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2)
{
	CRay r = (*this);
	assert(r.m_eRaySpace == E_WORLD);

	D3DXMATRIX matInvWorld;

	D3DXMATRIX matWorld;
	GetTransform(D3DTS_WORLD, &matWorld);
	D3DXMatrixIdentity(&matInvWorld);
	D3DXMatrixInverse(&matInvWorld,0,&matWorld);
	
	D3DXVec3TransformCoord(&r.m_vOrg, &r.m_vOrg, &matInvWorld);
	D3DXVec3TransformNormal(&r.m_vDir, &r.m_vDir, &matInvWorld);

	//r.m_eRaySpace = E_LOCAL;

	// (Q.V)^2 - V.V*(Q.Q - r*r) > 0
	if (IntersectTri(v0, v1, v2, m_vMousePos))
	{
		vPos = m_vMousePos;
		return true;
	}
	return false;
}

