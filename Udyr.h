#pragma once
#include "Champion.h"
class CUdyr : public CChampion
{
	using FUNCSTATE = function<bool(void)>;
	enum {};
public:
	CUdyr();
	virtual ~CUdyr();
private:
	bool				m_bRunning;
	bool				m_bTurning;
	bool				m_bDirty;

	vector<bool>		m_vStateFlag;
	vector<FUNCSTATE>	m_vStateFunc;
public:
	virtual HRESULT Initialize() override;
	virtual void	Progress()   override;
	virtual void	Render()     override;
	virtual void	Release()    override;

	virtual void	ChangeAniSetByState() override;
private:
	void			MouseControl();
	void			QWERControl();
private:	// StateFunc
	bool			Func_IDLE();
	bool			Func_ATTACK();
	bool			Func_RUN();
	bool			Func_AGRESSIVE();
};

