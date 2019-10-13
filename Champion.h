#pragma once
#include "Dynamic.h"


class CObjMgr;
class CRay;
class CChampion :
	public CDynamic
{
public:
	CChampion();
	~CChampion();

protected:
	float					m_fCamDistance;
	TCHAR*					m_strChampionName;
protected:
	CObjMgr*				m_ObjMgr;
	D3DXVECTOR3				m_vecMouseHitPoint;
protected:
	virtual void			KeyCheck();
	virtual bool			MouseCheck();
	virtual void			SetCameraPos();
	virtual void			SetAngleFromPostion();
public:
	virtual void			SetContantTable();
public:
	virtual					HRESULT Initialize()	PURE;
	virtual void			Progress()				PURE;
	virtual void			Render()				PURE;
	virtual void			Release()				PURE;
	
public:
	void					RegisterObjMgr(CObjMgr* pObjMgr) { m_ObjMgr = pObjMgr; }


//쓰레드를 쓰기위한 변수와 함수
private:
	static bool MapChecktThreadLoop(int number, const VTXTEX* vtx);
	static bool					bPick;
protected:
	static D3DXVECTOR3		g_MouseHitPoint;
	static std::atomic<bool>g_bMouseHitPoint;

		//test
public:
	void RenderDirection();
};

