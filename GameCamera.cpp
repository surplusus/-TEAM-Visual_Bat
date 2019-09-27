#include "BaseInclude.h"
#include "GameCamera.h"


CGameCamera::CGameCamera()
{
	m_fCamSpeed = 30.0f;
}


CGameCamera::~CGameCamera()
{
}

void CGameCamera::Progress(void)
{




	POINT		ptMouse = { WINSIZEX >> 1, WINSIZEY >> 1 };
	ClientToScreen(g_hWnd, &ptMouse);

	Joom_Mouse();
	Move_KeyBoard();
	SetCamPosition(&m_vEye, &m_vAt);

	CCamera::Progress();

}

void CGameCamera::Joom_Mouse(void)
{
	DIMOUSESTATE MouseState = MyGetMouseState();
	D3DXVECTOR3		vUp = D3DXVECTOR3(0.f, 1.f, 0.f);
	D3DXVECTOR3		vLook;

	if (MouseState.lZ>0)
	{
		vLook = m_vAt - m_vEye;
		D3DXVec3Normalize(&vLook, &vLook);
		m_vEye += vLook * m_fCamSpeed * GetTime();
		m_vAt += vLook * m_fCamSpeed * GetTime();
	}
	if (MouseState.lZ<0)
	{
		vLook = m_vAt - m_vEye;
		D3DXVec3Normalize(&vLook, &vLook);
		m_vEye -= vLook * m_fCamSpeed * GetTime();
		m_vAt -= vLook * m_fCamSpeed * GetTime();
	}

	if (!(MouseState.rgbButtons[1] & 0x80))
		return;


	
	
}


void CGameCamera::Move_KeyBoard(void)
{
	D3DXVECTOR3		vLook, vRight, vUp;
	D3DXVECTOR3     vZ(0.0f, 0.0f, 1.0f);
	if (CheckPushKey(DIK_UP))
	{
		vLook = m_vAt - m_vEye;
		D3DXVec3Cross(&vUp, &vZ, &vLook);
		D3DXVec3Normalize(&vUp, &vUp);
		m_vEye += vZ * m_fCamSpeed * GetTime();
		m_vAt  += vZ * m_fCamSpeed * GetTime();
	}
	if (CheckPushKey(DIK_DOWN))
	{
		vLook = m_vAt - m_vEye;
		D3DXVec3Cross(&vUp, &vZ, &vLook);
		D3DXVec3Normalize(&vUp, &vUp);

		m_vEye -= vZ * m_fCamSpeed * GetTime();
		m_vAt -=  vZ * m_fCamSpeed * GetTime();
	}

	if (CheckPushKey(DIK_LEFT))
	{
		vLook = m_vAt - m_vEye;

		D3DXVec3Cross(&vRight, &m_vUp, &vLook);
		D3DXVec3Normalize(&vRight, &vRight);

		m_vEye -= vRight * m_fCamSpeed * GetTime();
		m_vAt -= vRight * m_fCamSpeed * GetTime();
	}
	if (CheckPushKey(DIK_RIGHT))
	{
		vLook = m_vAt - m_vEye;

		D3DXVec3Cross(&vRight, &m_vUp, &vLook);
		D3DXVec3Normalize(&vRight, &vRight);

		m_vEye += vRight * m_fCamSpeed * GetTime();
		m_vAt += vRight * m_fCamSpeed * GetTime();
	}
}
