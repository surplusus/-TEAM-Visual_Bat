#include "BaseInclude.h"
#include "Camera.h"


CCamera::CCamera()
	:m_fCamSpeed(10.0f)
	
{
}


CCamera::~CCamera()
{
}

void CCamera::SetCamPosition(const D3DXVECTOR3 * pEye, const D3DXVECTOR3 * pAt)
{
	D3DXMatrixLookAtLH(&m_matView, pEye, pAt, &m_vUp);
	SetTransform(D3DTS_VIEW, &m_matView);
}

HRESULT CCamera::InitCamera(const D3DXVECTOR3 & vEye, const D3DXVECTOR3 & vAt, const D3DXVECTOR3 & vUp, const float & fFov, const float & fAspect, const float& fNear, const float & fFar)
{
	m_vEye = vEye;
	m_vAt = vAt;
	m_vUp = vUp;

	//CPipeLine::MakeMatrix_View(&m_matView, &vEye, &vAt, &vUp);	
	D3DXMatrixLookAtLH(&m_matView, &vEye, &vAt, &vUp);

	//CPipeLine::MakeMatrix_Projection(&m_matProj, fFov, fAspect, fNear, fFar);
	D3DXMatrixPerspectiveFovLH(&m_matProj, fFov, fAspect, fNear, fFar);

	SetTransform(D3DTS_VIEW, &m_matView);
	SetTransform(D3DTS_PROJECTION, &m_matProj);
	return S_OK;
}

void CCamera::Progress()
{
	DIMOUSESTATE MouseState = MyGetMouseState();

}
