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
class CTower
	: public CDynamic
{
public:
	CTower(string name, ST_ABILITY Ability);
	CTower() {}
	virtual ~CTower();
protected:
	CObjMgr*				m_ObjMgr;
	float					m_fSize = 1.f;
protected:
	// Update
	void		UpdateWorldMatrix();
// Thread or 지금은 작은 맵이라 그냥 개별 챔피언이 부름
	static bool	MapCheckThreadLoop(int number, const VTXTEX* vtx);
protected:
	ST_ABILITY			m_stAbil;
public:
	virtual	HRESULT		Initialize()	= 0;
	virtual void		Progress()		= 0;
	virtual void		Render()		= 0;
	virtual void		Release()		= 0;
};

