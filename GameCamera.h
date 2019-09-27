#pragma once
#include "Camera.h"
class CGameCamera :
	public CCamera
{
public:
	CGameCamera();
	~CGameCamera();

public:
	virtual void	Progress(void);
	void			Joom_Mouse(void);
	void			Move_KeyBoard(void);
};

