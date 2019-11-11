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
	SPHERE*				m_sphereTarget;
	// << : Behavior
	UdyrBT::UdyrBTHandler*	m_pBehavior;
	// << : Collision
	ColiderComponent*  m_pCollider;
	list<ColiderComponent*> m_ColliderList;
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
public:
	bool			IsEnemyNearInSphere(float fRadius);
private:
	const UdyrBT::UdyrBTHandler*	GetBehaviorTree();
	void			ChangeAniSetByKey(string key);
	void			SetUpAniSetNameList();
	void			DoOnMouseRButton();
	void			DoOnMouseLButton();
	void			QWERControl();
	// Event Functions
	void			OperateOnFindPickingSphere(PICKSPHEREEVENT* evt);
	void			OperateOnPaticleCollisionEvent(COLLISIONEVENT* evt);
	void			OperateOnPhysicalAttackEvent(PHYSICALATTACKEVENT* evt);
};

