#pragma once
#include "Minion.h"
class CMeleeMinion : public CMinion
{
	enum { STATETYPE_IDLE = 0, STATETYPE_AGRESSIVE, STATETYPE_ATTACK, STATETYPE_HIT, STATETYPE_END	};
	using StateFunc = function<void()>;
public:
	CMeleeMinion();
	virtual ~CMeleeMinion();
public:
	virtual HRESULT		Initialize() override;
	virtual void		Progress()	 override;
	virtual void		Render()	 override;
	virtual void		Release()	 override;
private:

public:
	void SetPosition(const D3DXVECTOR3* pos);
};

