#pragma once
#include "Dynamic.h"
class CObjMgr;
class CHeightMap;
class CChampion :
	public CDynamic
{
public:
	CChampion();
	~CChampion();
protected:
	CObjMgr*				m_ObjMgr;
	CHeightMap*				m_pHeightMap;
	float					m_fSize;
	D3DXVECTOR3				m_MouseHitPoint;
	D3DXVECTOR3				m_CurMousePoint;//현재 마우스가 어디있는지;
	bool					m_bPicked;
	SPHERE					m_SphereForPick;
	LPD3DXMESH				m_pMeshSphere;
	CHAMPION_STATETYPE		m_CurStateType;

protected:
	bool				TurnSlowly(const D3DXVECTOR3* destPos,float fLerpRate = 7.0f);
	void				UpdateWorldMatrix();
	void				SetDirectionToMouseHitPoint();
	bool				SetUpPickingShere(const float r = 1.f, D3DXVECTOR3* v = nullptr);
	bool				Render_PickingShere();
	bool				SearchPickingPointInHeightMap(int number, const VTXTEX* vtx);
	bool				SearchCurMousePointInHeightMap(int number,const VTXTEX* vtx);
	const VTXTEX*		GetVertexInHeightMap();
	DWORD&				GetVertexNumInHeightMap();
public:
	virtual	HRESULT		Initialize()	PURE;
	virtual void		Progress()		PURE;
	virtual void		Render()		PURE;
	virtual void		Release()		PURE;
public:		// 챔피언이면 만들어야 되는 함수들
	virtual void		ChangeAniSetByState()	PURE;
	void				SetHeightMap(CHeightMap* pHeightMap);
	STATUSINFO	*		GetStatusInfo() { return &m_StatusInfo; }
	CHAMPION_STATETYPE	GetStateType() { return m_CurStateType; }
protected:
	STATUSINFO m_StatusInfo;
	

};

