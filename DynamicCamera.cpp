#include "BaseInclude.h"
#include "DynamicCamera.h"


void CDynamicCamera::Progress(void)
{
	POINT		ptMouse = { WINSIZEX >> 1, WINSIZEY >> 1 };
	ClientToScreen(g_hWnd, &ptMouse);

	//SetCursorPos(ptMouse.x, ptMouse.y);
	Rotation_Mouse();
	Move_KeyBoard();
	SetCamPosition(&m_vEye, &m_vAt);
	CCamera::Progress();

}

void CDynamicCamera::Rotation_Mouse(void)
{
	DIMOUSESTATE MouseState = MyGetMouseState();

	if (!(MouseState.rgbButtons[1] & 0x80))
		return;


	D3DXMATRIX		matRot;
	D3DXVECTOR3		vUp = D3DXVECTOR3(0.f, 1.f, 0.f);

	if (MouseState.lX)
	{
		D3DXVECTOR3 vLook = m_vAt - m_vEye;

		D3DXMatrixRotationAxis(&matRot, &vUp, D3DXToRadian(MouseState.lX / 5.0f));
		D3DXVec3TransformNormal(&vLook, &vLook, &matRot);

		m_vAt = m_vEye + vLook;
	}

	if (MouseState.lY)
	{
		D3DXVECTOR3	vRight;
		D3DXVECTOR3 vLook = m_vAt - m_vEye;
		D3DXVec3Cross(&vRight, &m_vUp, &vLook);
		D3DXMatrixRotationAxis(&matRot, &vRight, D3DXToRadian(MouseState.lY / 5.0f));
		D3DXVec3TransformNormal(&vLook, &vLook, &matRot);
		m_vAt = m_vEye + vLook;
	}
}

void CDynamicCamera::Move_KeyBoard(void)
{
	D3DXVECTOR3		vLook, vRight, vUp;

	if (CheckPushKey(DIK_W))
	{
		vLook = m_vAt - m_vEye;
		D3DXVec3Normalize(&vLook, &vLook);
		m_vEye += vLook * m_fCamSpeed * GetTime();
		m_vAt += vLook * m_fCamSpeed * GetTime();
	}
	if (CheckPushKey(DIK_S))
	{
		vLook = m_vAt - m_vEye;
		D3DXVec3Normalize(&vLook, &vLook);
		m_vEye -= vLook * m_fCamSpeed * GetTime();
		m_vAt -= vLook * m_fCamSpeed * GetTime();
	}

	if (CheckPushKey(DIK_A))
	{
		vLook = m_vAt - m_vEye;

		D3DXVec3Cross(&vRight, &m_vUp, &vLook);
		D3DXVec3Normalize(&vRight, &vRight);

		m_vEye -= vRight * m_fCamSpeed * GetTime();
		m_vAt -= vRight * m_fCamSpeed * GetTime();
	}
	if (CheckPushKey(DIK_D))
	{
		vLook = m_vAt - m_vEye;

		D3DXVec3Cross(&vRight, &m_vUp, &vLook);
		D3DXVec3Normalize(&vRight, &vRight);

		m_vEye += vRight * m_fCamSpeed * GetTime();
		m_vAt += vRight * m_fCamSpeed * GetTime();
	}
}

CDynamicCamera::CDynamicCamera()
{
}


CDynamicCamera::~CDynamicCamera()
{
}
