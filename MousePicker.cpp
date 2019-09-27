#include "BaseInclude.h"
#include "MousePicker.h"

CMousePicker::CMousePicker()
	: m_stRay(nullptr),
	m_HittingPoint(0, 0, 0)
{
}

CMousePicker::~CMousePicker()
{
	SAFE_DELETE(m_stRay);
}

bool CMousePicker::GetHittingPoint(OUT D3DXVECTOR3 * hittingpoint)
{
	if (m_HittingPoint == D3DXVECTOR3(0, 0, 0))
		return false;

	hittingpoint = &m_HittingPoint;
	return true;
}

RAY CMousePicker::CalcPickingRay(int x, int y)
{
	D3DVIEWPORT9 vp;
	GET_DEVICE->GetViewport(&vp);

	D3DXMATRIXA16 matProj;
	GET_DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);

	// 마우스 좌표를 투영창의 좌표로 변환한다.
	float px = (((2.f * x) / vp.Width) - 1.f) / (float)matProj(0, 0);
	float py = (((-2.0 * y) / vp.Height) + 1.f) / (float)matProj(1, 1);

	RAY ray(px, py, 1.f);	//ray.direction : (px, py, 1.f)
	return ray;
}

void CMousePicker::TransformRay(RAY * ray, D3DXMATRIXA16 * matT)
{
	// ray origin 좌표변환
	D3DXVec3TransformCoord(&ray->origin, &ray->origin, matT);
	// ray direction 백터변환
	D3DXVec3TransformNormal(&ray->direction, &ray->direction, matT);

	D3DXVec3Normalize(&ray->direction, &ray->direction);
}

bool CMousePicker::CheckIntersectWithSphere(SPHERE sphere)
{
	// 마우스 좌표를 월드로 적용시키는 과정
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(g_hWnd, &mouse);

	if (!m_stRay)
		m_stRay = new RAY;
	*m_stRay = CalcPickingRay(mouse.x, mouse.y);	// PickingRay from CamaraEye

	D3DXMATRIXA16 view;
	GET_DEVICE->GetTransform(D3DTS_VIEW, &view);
	D3DXMATRIXA16 matInv;
	D3DXMatrixInverse(&matInv, NULL, &view);

	TransformRay(m_stRay, &matInv);

	// 매개변수로 받은 구와 ray 판별 과정
	D3DXVECTOR3 vSphere = m_stRay->origin - sphere.vCenter;

	float b = 2.f * D3DXVec3Dot(&m_stRay->direction, &vSphere);
	float r = sphere.fRadius;
	float c = D3DXVec3Dot(&vSphere, &vSphere) - (r * r);

	float discriminant = (b * b) - (4.f * c);

	if (discriminant < 0.f)
		return false;

	discriminant = sqrtf(discriminant);
	float t0 = (-b + discriminant) / 2.f;
	float t1 = (-b - discriminant) / 2.f;

	if (t0 >= 0.f || t1 >= 0.f)
		return true;

	return false;

}

bool CMousePicker::CheckIntersectWithTriangle(const D3DXVECTOR3 * p0, const D3DXVECTOR3 * p1, const D3DXVECTOR3 * p2)
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(g_hWnd, &mouse);

	if (!m_stRay)
		m_stRay = new RAY;
	*m_stRay = CalcPickingRay(mouse.x, mouse.y);	// PickingRay from CamaraEye

	D3DXMATRIXA16 view;
	GET_DEVICE->GetTransform(D3DTS_VIEW, &view);
	D3DXMATRIXA16 matInv;
	D3DXMatrixInverse(&matInv, NULL, &view);

	TransformRay(m_stRay, &matInv);

	float u, v, dist;
	bool result = D3DXIntersectTri(p0, p1, p2, &m_stRay->origin, &m_stRay->direction, &u, &v, &dist);
	D3DXVECTOR3 vDirFromP0ToP1 = *p1 - *p0;
	D3DXVECTOR3 vDirFromP0ToP2 = *p2 - *p0;
	m_HittingPoint = *p0 + (u * (*p1 - *p0)) + v * (*p2 - *p0);

	D3DXVECTOR3 vec = m_HittingPoint;
	return result;
}

bool CMousePicker::CheckIntersectWithTriangleAndGetPosition(IN const D3DXVECTOR3 * p0, IN const D3DXVECTOR3 * p1, IN const D3DXVECTOR3 * p2, OUT D3DXVECTOR3 * hitpoint)
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(g_hWnd, &mouse);

	if (!m_stRay)
		m_stRay = new RAY;
	*m_stRay = CalcPickingRay(mouse.x, mouse.y);	// PickingRay from CamaraEye

	D3DXMATRIXA16 view;
	GET_DEVICE->GetTransform(D3DTS_VIEW, &view);
	D3DXMATRIXA16 matInv;
	D3DXMatrixInverse(&matInv, NULL, &view);

	TransformRay(m_stRay, &matInv);

	float u, v, dist;
	bool result = D3DXIntersectTri(p0, p1, p2, &m_stRay->origin, &m_stRay->direction, &u, &v, &dist);
	D3DXVECTOR3 vDirFromP0ToP1 = *p1 - *p0;
	D3DXVECTOR3 vDirFromP0ToP2 = *p2 - *p0;
	m_HittingPoint = *p0 + (u * (*p1 - *p0)) + v * (*p2 - *p0);

	*hitpoint = m_HittingPoint;
	return result;
}
