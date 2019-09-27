#include "BaseInclude.h"
#include "StaticCamera.h"


CStaticCamera::CStaticCamera()
{
}


CStaticCamera::~CStaticCamera()
{
}

void CStaticCamera::Rotation_Mouse(void)
{
	DIMOUSESTATE MouseState = MyGetMouseState();

	D3DXMATRIX	matRot;

	if (MouseState.lZ)
	{
		m_fDistance += MouseState.lZ * 3.0f * GetTime();
	}

	if (MouseState.lY)
	{
		m_fAngle[ANGLE_X] += D3DXToRadian(MouseState.lY / 3.f);
	}

	if (MouseState.rgbButtons[2])
	{
		D3DXVECTOR3	vDir = m_vEye - m_pObjectInfo->vPos;

		D3DXMatrixRotationY(&matRot, D3DXToRadian(MouseState.lX / 3.f));

		D3DXVec3TransformNormal(&vDir, &vDir, &matRot);

		D3DXVec3Normalize(&vDir, &vDir);

		m_vEye = m_pObjectInfo->vPos + vDir * m_fDistance;
	}

	else
	{
		D3DXVECTOR3		vAxis = D3DXVECTOR3(m_pObjectInfo->matWorld._11
			, m_pObjectInfo->matWorld._12
			, m_pObjectInfo->matWorld._13);

		D3DXVECTOR3		vDir = m_pObjectInfo->vDir;

		D3DXMATRIX		matRot;

		D3DXMatrixRotationAxis(&matRot, &vAxis, m_fAngle[ANGLE_X]);
		D3DXVec3TransformNormal(&vDir, &vDir, &matRot);

		m_vEye = vDir * m_fDistance * -1.f + m_pObjectInfo->vPos;
		m_vAt = m_pObjectInfo->vPos;
		m_vUp = D3DXVECTOR3(0.f, 1.f, 0.f);
	}
}

void CStaticCamera::Progress(void)
{

	POINT		ptMouse = { WINSIZEX >> 1, WINSIZEY >> 1 };
	ClientToScreen(g_hWnd, &ptMouse);

	Rotation_Mouse();

	SetCamPosition(&m_vEye, &m_vAt);

	CCamera::Progress();
}
