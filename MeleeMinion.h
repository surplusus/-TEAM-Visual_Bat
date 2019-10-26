#pragma once
#include "Minion.h"
class CMeleeMinion : public CMinion
{
public:
	CMeleeMinion();
	virtual ~CMeleeMinion();
private:
	virtual HRESULT		Initialize() override;
	virtual void		Progress()	 override;
	virtual void		Render()	 override;
	virtual void		Release()	 override;
};

