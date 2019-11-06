#pragma once
#include "Dynamic.h"
#include "BehaviorMinion.h"

class CHeightMap;
class CMinionMgr;
class ColiderComponent;
class CMinion : public CDynamic
{
private:
	friend class MinionBT::MinionBTHandler;
	friend class BehaviorTree::Task;
public:
	CMinion();
	virtual ~CMinion();

	virtual HRESULT		Initialize() PURE;
	virtual void		Progress() PURE;
	virtual void		Render() PURE;
	virtual void		Release() PURE;
protected:
	CMinionMgr*			m_pMinionMgr;
	CHeightMap*			m_pHeightMap;
	float				m_fSize;
	SPHERE				m_SphereForPick;
	LPD3DXMESH			m_pMeshSphere;
	D3DXVECTOR3			m_vNextPoint;
	STATUSINFO			m_stStatusInfo;
	// << : Behavior
	MinionBT::MinionBTHandler*	m_pBehavior;
	void			UpdateBlackBoard();
	// >> : Behavior
	// << : Collision
	ColiderComponent*  m_pCollider;
	list<ColiderComponent*> m_ColiderList;
	// >> : Collision
protected:
	void				UpdateWorldMatrix();
	bool				SetUpPickingShere(const float r = 1.f, D3DXVECTOR3* v = nullptr);
	bool				Render_PickingShere();
	void				SetDirectionToNextPoint();
public:
	void				SetPosition(const D3DXVECTOR3* pos);
	void				SetMinionMgr(CMinionMgr* pMinionMgr) { m_pMinionMgr = pMinionMgr; }
	void				SetHeightMap(CHeightMap** pHeightMap) { m_pHeightMap = *pHeightMap; }
};

