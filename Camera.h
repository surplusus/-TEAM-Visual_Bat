#pragma once
class CCamera
{
public:
	CCamera();
	virtual ~CCamera();
	CCamera(D3DXVECTOR3 vEye, D3DXVECTOR3 vLookAt, D3DXVECTOR3 vUp) 
		:m_vEye(vEye),m_vLookAt(vLookAt),m_vUp(vUp)
	{}
protected:
	D3DXVECTOR3 m_vEye;
	D3DXVECTOR3	m_vLookAt;
	D3DXVECTOR3 m_vUp;

public:
	virtual void Update() = 0;
	virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
};

