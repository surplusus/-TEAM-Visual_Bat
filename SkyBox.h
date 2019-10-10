#pragma once
#include "Obj.h"
class CSkyBox :
	public CObj
{
public:
	CSkyBox();
	virtual ~CSkyBox();
public:
	void PreRender(void);
	void EndRender(void);

public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
};

