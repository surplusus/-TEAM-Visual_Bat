#pragma once
#include "Dynamic.h"
#include "BehaviorMinion.h"

class CHeightMap;
class CMinionMgr;
class ColiderComponent;
class CMinion : public CDynamic
{
#pragma region 무더기 친구들
	friend class MinionBT::MinionBTHandler;
	friend class MinionBT::MinionAccessor;
	friend struct MinionBT::MinionDeath;
	friend struct MinionBT::MinionBeaten;
	friend struct MinionBT::MinionAggressive;
	friend struct MinionBT::MinionAttack;
	friend struct MinionBT::MinionRun;
	friend struct MinionBT::MinionTurn;
#pragma endregion
public:
	CMinion();
	virtual ~CMinion();

	virtual HRESULT		Initialize() PURE;
	virtual void		Progress() PURE;
	virtual void		Render() PURE;
	virtual void		Release() PURE;

	vector<string>		m_AniSetNameList;
protected:
	CMinionMgr*			m_pMinionMgr;
	CHeightMap*			m_pHeightMap;
	float				m_fSize;
	SPHERE				m_SphereForPick;
	//LPD3DXMESH			m_pMeshSphere;
	D3DXVECTOR3			m_NextPoint;
	vector<D3DXVECTOR3>	m_vNextPoints;
	STATUSINFO			m_stStatusInfo;
	SPHERE*				m_sphereTarget;	// Enemy
	// << : Behavior
	MinionBT::MinionBTHandler*	m_pBehavior;
	// >> : Behavior
	// << : Collision
	ColiderComponent*  m_pCollider;
	list<ColiderComponent*> m_ColliderList;
	// >> : Collision
protected:
	void				ChangeNextPoint();
	void				UpdateWorldMatrix();
	bool				SetUpPickingShere(const float r = 1.f, D3DXVECTOR3* v = nullptr);
	bool				Render_PickingShere();
	void				SetDirectionToNextPoint();
	void				SetUpAniSetNameList();
	bool				TurnSlowly(const D3DXVECTOR3* destPos, float fLerpRate = 7.0f);
public:
	void				SetPosition(const D3DXVECTOR3* pos);
	void				SetMinionMgr(CMinionMgr* pMinionMgr) { m_pMinionMgr = pMinionMgr; }
	void				SetHeightMap(CHeightMap** pHeightMap) { m_pHeightMap = *pHeightMap; }
private:
	void			OperateOnPaticleCollisionEvent(COLLISIONEVENT* evt);
	void			OperateOnPhysicalAttackEvent(PHYSICALATTACKEVENT* evt);
};

