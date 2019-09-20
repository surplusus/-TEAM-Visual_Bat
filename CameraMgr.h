#pragma once
#include"Camera.h"
class CCameraMgr
{
	DECLARE_SINGLETON(CCameraMgr)
private:
	CCamera* m_pCamera;
public:
	const D3DXMATRIX* GetViewMatrix(void) {
		return m_pCamera->GetViewMatrix();
	}
	const D3DXMATRIX* GetProjectionMatrix(void) {
		return m_pCamera->GetProjectionMatrix();
	}
public:
	HRESULT SetCamera(CAMMODE Mode
		, const D3DXVECTOR3& vEye
		, const D3DXVECTOR3& vAt
		, const D3DXVECTOR3& vUp
		, const float& fFov
		, const float& fAspect
		, const float& fNear
		, const float& fFar);
	void Progress(void) {
		m_pCamera->Progress();
	}

	void Release(void);
private:
	CCameraMgr(void);
public:
	~CCameraMgr(void);
};

