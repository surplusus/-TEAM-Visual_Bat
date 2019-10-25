#pragma once

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


class CTower
{
public:
	CTower();
	~CTower();
public:
	virtual void Initialize() = 0;
	virtual void Progress() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

private:
	ST_ABILITY				m_stAbility;
};

