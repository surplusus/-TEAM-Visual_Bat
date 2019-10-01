#pragma once
#include "Dynamic.h"
class CObjMgr;
class CChampion :
	public CDynamic
{
public:
	CChampion();
	~CChampion();

protected:
	D3DXVECTOR3		m_vMousePos;
	float			m_fCamDistance;
	TCHAR*			m_strChampionName;
protected:
	CObjMgr*				m_ObjMgr;
	D3DXVECTOR3				m_vecMouseHitPoint;
protected:
	virtual void			KeyCheck();
	virtual bool			MouseCheck();
	virtual void			SetCameraPos();
public:
	virtual void			SetContantTable();
public:
	virtual					HRESULT Initialize()	PURE;
	virtual void			Progress()				PURE;
	virtual void			Render()				PURE;
	virtual void			Release()				PURE;
public:
	void					RegisterObjMgr(CObjMgr* pObjMgr) { m_ObjMgr = pObjMgr; }
};

