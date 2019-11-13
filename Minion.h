#pragma once
#include "Dynamic.h"

class CHeightMap;
class CMinionMgr;
class ColiderComponent;
class CMinion : public CDynamic
{
public:
	CMinion();
	virtual ~CMinion();

	virtual HRESULT		Initialize() PURE;
	virtual void		Progress() PURE;
	virtual void		Render() PURE;
	virtual void		Release() PURE;

	vector<string>		m_AniSetNameList;
	const TCHAR*		m_MeshName;
protected:
	CMinionMgr*			m_pMinionMgr;
	CHeightMap*			m_pHeightMap;
	float				m_fSize;
	SPHERE				m_SphereForPick;
	//LPD3DXMESH			m_pMeshSphere;
	D3DXVECTOR3			m_NextPoint;
	vector<D3DXVECTOR3>	m_vNextPoints;
	STATUSINFO			m_StatusInfo;
	SPHERE*				m_sphereTarget;	// Enemy

protected:
	void			ChangeNextPoint();
	void			UpdateWorldMatrix();
	bool			SetUpPickingShere(const float r = 1.f, D3DXVECTOR3* v = nullptr);
	bool			Render_PickingShere();
	void			SetDirectionToNextPoint();
	bool			TurnSlowly(const D3DXVECTOR3* destPos, float fLerpRate = 7.0f);
public:
	void			SetUpAniSetNameList();
	CAnimationCtrl* GetAnimationCtrl() { return m_pAnimationCtrl; }
	void			SetPosition(const D3DXVECTOR3* pos);
	void			SetMinionMgr(CMinionMgr* pMinionMgr) { m_pMinionMgr = pMinionMgr; }
	void			SetHeightMap(CHeightMap** pHeightMap) { m_pHeightMap = *pHeightMap; }
	void			SetMeshName(const TCHAR* str) { m_MeshName = str; }
	void			SetPos(const D3DXVECTOR3* vecPos) { m_Info.vPos = *vecPos; }
};

