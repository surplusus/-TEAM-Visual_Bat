#pragma once
#include "Champion.h"
#include "BehaviorUdyr.h"

class ColiderComponent;
class CParticle;
class CUdyr : public CChampion
{
	friend class UdyrBT::UdyrBTHandler;
	friend class BehaviorTree::Task;
public:
	CUdyr();
	virtual ~CUdyr();
private:
	vector<string>		m_AniSetNameList;
	STATUSINFO			m_stStatusInfo;
	// << : Behavior
	UdyrBT::UdyrBTHandler*	m_pBehavior;
	void			UpdateBlackBoard();
	// >> : Behavior
	// << : Collision
	ColiderComponent*  m_pCollider;
	list<ColiderComponent*> m_ColiderList;
	// >> : Collision
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
	void			PaticleCollisionEvent(COLLISIONEVENT* evt);
	void			ChangeAniByState();
};

