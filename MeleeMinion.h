#pragma once
#include "Minion.h"
#include "BehaviorMeleeMinion.h"
class CMeleeMinion : public CMinion
{
#pragma region 무더기 친구들
	friend class MeleeMinionBT::MinionBTHandler;
	friend class MeleeMinionBT::MinionAccessor;
	friend struct MeleeMinionBT::MinionDeath;
	friend struct MeleeMinionBT::MinionBeaten;
	friend struct MeleeMinionBT::MinionAttack;
	friend struct MeleeMinionBT::MinionAggressive;
	friend struct MeleeMinionBT::MinionNextPos;
	friend struct MeleeMinionBT::MinionRun;
	friend struct MeleeMinionBT::MinionTurn;
	friend struct MeleeMinionBT::MinionIdle;
	friend struct MeleeMinionBT::WhenEnemyNear;
	friend class CMinionMgr;
#pragma endregion
public:
	CMeleeMinion();
	virtual ~CMeleeMinion();
public:
	virtual HRESULT		Initialize() override;
	virtual void		Progress()	 override;
	virtual void		Render()	 override;
	virtual void		Release()	 override;
private:
	// << : Behavior
	MeleeMinionBT::MinionBTHandler*	m_pBehavior;
	// << : Collision
	ColiderComponent*  m_pCollider;
	list<ColiderComponent*> m_ColliderList;
	int m_iDelaySec = 590;
	int m_iCntSec = 0;
	bool m_bStartRender = false;
public:
	void SetPosition(const D3DXVECTOR3* pos);
private:
	void OperateOnPaticleCollisionEvent(COLLISIONEVENT* evt);
	void OperateOnPhysicalAttackEvent(PHYSICALATTACKEVENT* evt);
	void SearchNearBy();
};

