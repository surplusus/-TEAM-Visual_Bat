#pragma once
#include "Minion.h"
class CMeleeMinion : public CMinion
{
	enum { STATETYPE_IDLE = 0, STATETYPE_AGRESSIVE, STATETYPE_ATTACK, STATETYPE_HIT, STATETYPE_END	};
	using StateFunc = function<void()>;
public:
	CMeleeMinion();
	virtual ~CMeleeMinion();
private:
	virtual HRESULT		Initialize() override;
	virtual void		Progress()	 override;
	virtual void		Render()	 override;
	virtual void		Release()	 override;
private:
	vector<bool>		m_vbOnState;
	vector<StateFunc>	m_vStateFunc;
	queue<StateFunc>	m_queStateFunc;
	void				EnqueueStateFunc(StateFunc func);
	void				ProgressStateFuncInQueue();
};

