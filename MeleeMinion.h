#pragma once
#include "Minion.h"
class CMeleeMinion : public Minion
{
public:
	CMeleeMinion();
	virtual ~CMeleeMinion();
public:
	virtual HRESULT		Initialize();
	virtual void		Progress();
	virtual void		Render();
	virtual void		Release();
};

