#pragma once
#include "Camera.h"
class CStaticCamera :
	public CCamera
{
public:
	CStaticCamera();
	~CStaticCamera();
private:
	float			m_fDistance;
	const INFO*		m_pObjectInfo;
	float			m_fAngle[ANGLE_END];

	D3DXVECTOR3		m_vDirection;
public:
	void Rotation_Mouse(void);
public:
	virtual void Progress(void);

};

