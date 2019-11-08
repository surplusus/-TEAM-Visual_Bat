#pragma once
#include "Champion.h"
#include "BehaviorUdyr.h"

class ColiderComponent;
class CParticle;
class CUdyr : public CChampion
{
	friend class UdyrBT::UdyrBTHandler;
	friend class UdyrBT::UdyrAccessor;
	friend class BehaviorTree::Decorator;
public:
	CUdyr();
	virtual ~CUdyr();
private:
	vector<string>		m_AniSetNameList;
	STATUSINFO			m_stStatusInfo;
	// << : Behavior
	UdyrBT::UdyrBTHandler*	m_pBehavior;
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
	// Write on BlackBoard
	void			WriteOnBlackBoard(string sKey, bool bValue);
	void			WriteOnBlackBoard(string sKey, int iValue);
	void			WriteOnBlackBoard(string sKey, float fValue);
	void			WriteOnBlackBoard(string sKey, double llValue);
	void			WriteOnBlackBoard(string sKey, string sValue);
private:
	void			ChangeAniSetByKey(string key);
	void			SetUpAniSetNameList();
	void			OperateOnFindPickingSphere(PICKSPHEREEVENT* evt);
	void			OperateOnPaticleCollisionEvent(COLLISIONEVENT* evt);

};

