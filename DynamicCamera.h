#pragma once
#include "Camera.h"
class CDynamicCamera :
	public CCamera
{
public:
	virtual void Progress(void);
	void Rotation_Mouse(void);
	void Move_KeyBoard(void);
public:
	CDynamicCamera(void);
	~CDynamicCamera(void);
};

