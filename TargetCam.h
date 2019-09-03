#pragma once
#include "Camera.h"
class CTargetCam :
	public CCamera
{
public:
	CTargetCam();
	~CTargetCam();
private:
	POINT m_ptPrevMouse;
	bool m_isLButtonDown;
	float m_fCameraDistance;
	D3DXVECTOR3 m_vCamRotAngle;
	D3DXVECTOR3* m_pvTarget;

	bool m_isDirty;
public:
	void Setup(D3DXVECTOR3 * pvTarget);
	virtual void Update();
	virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

};

