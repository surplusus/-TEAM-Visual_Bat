#pragma once
class CCamera
{
public:
	CCamera();
	~CCamera();
protected:
	D3DXMATRIX	m_matView, m_matProj;
protected:
	D3DXVECTOR3 m_vEye, m_vAt, m_vUp;
protected:
	float m_fCamSpeed;
public:
	const D3DXMATRIX* GetViewMatrix() {
		return &m_matView;
	}
	const D3DXMATRIX* GetProjectionMatrix()
	{
		return &m_matProj;
	}

public:
	void SetCamPosition(const D3DXVECTOR3* pEye, const D3DXVECTOR3* pAt);
	void SetCamSpeed(float speed);
public:
	virtual HRESULT InitCamera(const D3DXVECTOR3& vEye
		, const D3DXVECTOR3& vAt
		, const D3DXVECTOR3& vUp
		, const float& fFov
		, const float& fAspect
		, const float&fNear
		, const float &fFar);
	virtual void Progress();
	D3DXVECTOR4 GetPos() {
		return D3DXVECTOR4(m_vEye.x, m_vEye.y, m_vEye.z, 1.0f);
	}
};

