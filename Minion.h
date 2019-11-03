#pragma once
#include "Dynamic.h"
class CHeightMap;
class CMinionMgr;
class CMinion : public CDynamic
{
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

