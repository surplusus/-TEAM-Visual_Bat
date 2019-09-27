#include "BaseInclude.h"
#include "CameraMgr.h"
#include"DynamicCamera.h"
#include"StaticCamera.h"
#include "GameCamera.h"
HRESULT CCameraMgr::SetCamera(CAMMODE Mode, const D3DXVECTOR3 & vEye, const D3DXVECTOR3 & vAt, const D3DXVECTOR3 & vUp, const float & fFov, const float & fAspect, const float & fNear, const float & fFar)
{
	if (m_pCamera)
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}

	switch (Mode)
	{
	case CAMMODE_DYNAMIC:
		m_pCamera = new CDynamicCamera;		break;
	case CAMMODE_STATIC:
		m_pCamera = new CStaticCamera;		break;
	case CAMMODE_GAME:
		m_pCamera = new CGameCamera;		break;
	}
	if (FAILED(m_pCamera->InitCamera(vEye, vAt, vUp, fFov, fAspect, fNear, fFar)))
		return E_FAIL;

	return S_OK;
}

void CCameraMgr::Release(void)
{
	if (m_pCamera)
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}
}

CCameraMgr::CCameraMgr()
	:m_pCamera(NULL)
{
}


CCameraMgr::~CCameraMgr()
{

		Release();

}
