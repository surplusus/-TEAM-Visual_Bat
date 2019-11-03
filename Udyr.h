#pragma once
#include "Champion.h"
#include "BehaviorUdyr.h"

class CUdyr : public CChampion
{
	friend class UdyrBT::UdyrBTHandler;
	friend class BehaviorTree::Task;
	using FUNCSTATE = function<bool(void)>;
	enum {STATETYPE_IDLE, STATETYPE_ATTACK, STATETYPE_RUN, STATETYPE_AGRESSIVE
		, STATETYPE_TURNING
		, STATETYPE_END
	};
public:
	CUdyr();
	virtual ~CUdyr();
private:
	int 				m_iStateFlag;
	void				ControlFlag();
	vector<bool>		m_vStateFlag;
	vector<FUNCSTATE>	m_vStateFunc;
	queue<FUNCSTATE>	m_queStateFunc;
	CObj*				m_pTargetObj;
	vector<string>		m_AniSetNameList;
	// << : Behavior
	UdyrBT::UdyrBTHandler*	m_pBehavior;
	void			UpdateBlackBoard();
	// >> : Behavior
public:
	virtual HRESULT Initialize() override;
	virtual void	Progress()   override;
	virtual void	Render()     override;
	virtual void	Release()    override;

	virtual void	ChangeAniSetByState() override {}
private:
	void			ChangeAniSetByKey(string key);
	void			SetUpAniSetNameList();
	void			OnFindPickingSphere(PICKSPHEREEVENT* evt);
	void			MouseControl();
	void			QWERControl();
private:	// StateFunc
	bool			Func1_IDLE();
	bool			Func2_ATTACK();
	bool			Func3_RUN();
	bool			Func4_AGRESSIVE();

	void			ProgressStateFunc();
};

