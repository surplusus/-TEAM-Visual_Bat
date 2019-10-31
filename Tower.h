#pragma once
#include "Dynamic.h"
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
class CTower
	: public CDynamic
{
public:
	CTower(string name, ST_ABILITY Ability);
	CTower() {}
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
	void		UpdateWorldMatrix();
	const VTXTEX*		GetVertexInHeightMap();
	DWORD&				GetVertexNumInHeightMap();
public:
	virtual	HRESULT		Initialize()	 = 0;
	virtual void		Progress()		 = 0;
	virtual void		Render()		 = 0;
	virtual void		Release()		 = 0;
	void				SetHeightMap(CHeightMap* pHeightMap);
};

