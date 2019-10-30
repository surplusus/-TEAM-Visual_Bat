#pragma once
#include "Champion.h"
class CUdyr : public CChampion
{
	using FUNCSTATE = function<bool(void)>;
	enum {STATETYPE_IDLE, STATETYPE_ATTACK, STATETYPE_RUN, STATETYPE_AGRESSIVE
		, STATETYPE_TURNING
		, STATETYPE_END
	};
public:
	CUdyr();
	virtual ~CUdyr();
private:
	bool				m_bRunning;
	bool				m_bTurning;
	bool				m_bDirty;

	int 				m_iStateFlag;
	void				ControlFlag();
	vector<FUNCSTATE>	m_vStateFunc;
	queue<FUNCSTATE>	m_queStateFunc;
public:
	virtual HRESULT Initialize() override;
	virtual void	Progress()   override;
	virtual void	Render()     override;
	virtual void	Release()    override;

	virtual void	ChangeAniSetByState() override {}
private:
	void			MouseControl();
	void			QWERControl();
private:	// StateFunc
	bool			Func1_IDLE();
	bool			Func2_ATTACK();
	bool			Func3_RUN();
	bool			Func4_AGRESSIVE();

	void			ProgressStateFunc();
};

