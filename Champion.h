#pragma once
#include "Dynamic.h"
class CObjMgr;
class CChampion :
	public CDynamic
{
public:
	CChampion();
	~CChampion() {}
protected:
	TCHAR*					m_strChampionName;
	CObjMgr*				m_ObjMgr;
	D3DXVECTOR3				m_vecMouseHitPoint;
	LPD3DXMESH				m_pMesh;
protected:
	// Init

	// Update
	bool				CheckMousePickingOnFloor();		// 마우스 피킹포인트를 찾았으면 true;

	
public:
	virtual	HRESULT		Initialize()	PURE;
	virtual void		Progress()		PURE;
	virtual void		Render()		PURE;
	virtual void		Release()		PURE;
};

