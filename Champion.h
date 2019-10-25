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
	CObjMgr*				m_ObjMgr;
	float					m_fSize;
	D3DXVECTOR3				m_MouseHitPoint;
	bool					m_bPicked;
	SPHERE					m_SphereForPick;
	LPD3DXMESH				m_MeshSphere;
protected:
	// Update
	void		UpdateWorldMatrix();
	void		SetDirectionToMouseHitPoint();
	bool		SetUpPickingShere(const float r, const D3DXVECTOR3 v);
	bool		Render_PickingShere();
	//bool		EnqueueMousePickingFunc();		// 마우스 피킹포인트를 찾았으면 true /  g_MouseHitPoint 과 g_bHitFloor 로 결과를 받는다
	// Algorithm

//private:
	// Thread or 지금은 작은 맵이라 그냥 개별 챔피언이 부름
	bool	MapCheckThreadLoop(int number, const VTXTEX* vtx);
public:
	virtual	HRESULT		Initialize()	PURE;
	virtual void		Progress()		PURE;
	virtual void		Render()		PURE;
	virtual void		Release()		PURE;
};

