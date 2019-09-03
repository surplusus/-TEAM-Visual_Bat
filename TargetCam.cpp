#include "BaseInclude.h"
#include "TargetCam.h"


CTargetCam::CTargetCam()
	: 
	CCamera(D3DXVECTOR3(0, 5.f, -5.f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 1, 0)),
	m_pvTarget(nullptr), m_fCameraDistance(5.f),
	m_isLButtonDown(false), m_vCamRotAngle(0, 0, 0), m_ptPrevMouse(POINT{ 0,0 }), m_isDirty(true)
{

}


CTargetCam::~CTargetCam()
{
}
void CTargetCam::Setup(D3DXVECTOR3 * pvTarget)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.f, rc.right / (float)rc.bottom, 1.f, 1000.f);
	GET_SINGLE(CDevice)->GetDevice()->SetTransform(D3DTS_PROJECTION, &matProj);

}
void CTargetCam::Update()
{
	if (m_isDirty)
	{
		RECT rc;
		GetClientRect(g_hWnd, &rc);
		D3DXMATRIXA16 matRot;
		D3DXMatrixIdentity(&matRot);

		D3DXMATRIXA16 matR, matRX, matRY;
		D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);
		D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);
		matR = matRX*matRY;
		matR = matRX*matRY;
		m_vEye = D3DXVECTOR3(0, 0, -m_fCameraDistance);
		D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);

		if (m_pvTarget)
		{
			m_vLookAt = *m_pvTarget;
			m_vEye = m_vEye + *m_pvTarget;
		}
		D3DXMATRIXA16 matView;
		D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
		GET_SINGLE(CDevice)->GetDevice()->SetTransform(D3DTS_VIEW,&matView);		
	}
}

void CTargetCam::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		m_isLButtonDown = true;
	}
	break;
	case WM_LBUTTONUP:
	{
		m_isLButtonDown = false;
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (m_isLButtonDown) {
			POINT ptCurMouse;
			ptCurMouse.x = LOWORD(lParam);
			ptCurMouse.y = HIWORD(lParam);
			float fDeltaX = (float)ptCurMouse.x - m_ptPrevMouse.x;
			float fDeltaY = (float)ptCurMouse.y - m_ptPrevMouse.y;
			m_vCamRotAngle.y += (fDeltaX / 100.f);
			m_vCamRotAngle.x += (fDeltaY / 100.f);
			if (m_vCamRotAngle.x < -D3DX_PI / 2.f + 0.0001f)
				m_vCamRotAngle.x = -D3DX_PI / 2.f + 0.0001f;
			if (m_vCamRotAngle.y < D3DX_PI / 2.f + 0.0001f)
				m_vCamRotAngle.y = D3DX_PI / 2.f + 0.0001f;
			m_ptPrevMouse = ptCurMouse;
		}

	}
	break;
	case WM_MOUSEWHEEL:
	{
		m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 30.f);
		if (m_fCameraDistance < 0.0001f)
			m_fCameraDistance = 0.0001f;
	}break;
	}
}
