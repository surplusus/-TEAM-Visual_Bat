#pragma once
#include "Champion.h"
struct ST_ABILITY
{
	int st_HitPoint;
	int st_Attack;
	int st_AttackSpeed;
	int st_Barrier;
	int st_HealthRegeneration;
	int st_MagicResist;
	int st_Gold;
	int st_GlobalGold;
};

class CObjMgr;
class CHeightMap;
//>>champion -> dyanmic으로 나중에 코드 정리후 상속관계변경 필요
class CGauge;
class CTower
	: public CChampion
{
public:
	CTower();
	virtual ~CTower();
protected:
	CObjMgr*				m_ObjMgr;
	CHeightMap*				m_pHeightMap;
	float					m_fSize;
	D3DXVECTOR3				m_MouseHitPoint;
	bool					m_bPicked;
	SPHERE					m_SphereForPick;
	LPD3DXMESH				m_pMeshSphere;
protected:
	void				UpdateWorldMatrix();
	const VTXTEX*		GetVertexInHeightMap();
	DWORD&				GetVertexNumInHeightMap();
public:
	virtual	HRESULT		Initialize()	 = 0;
	virtual void		Progress()		 = 0;
	virtual void		Render()		 = 0;
	virtual void		Release()		 = 0;
	void				SetHeightMap(CHeightMap* pHeightMap);

protected:
	CGauge*					m_pGauge;
};

