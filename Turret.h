#pragma once
#include "Tower.h"
class ColiderComponent;
class CTurret :
	public CTower
{
public:
	CTurret();
	virtual ~CTurret();
public:
	virtual HRESULT	Initialize() override;
	virtual void Progress() override;
	virtual void Render() override;
	virtual void Release() override;
private:
	bool Animation_Break();

public:
	bool Attacked_Target();
	list<ColiderComponent*> m_ColiderList;

private:
	LPDIRECT3DTEXTURE9				m_pTexture;

private:
	virtual void		ChangeAniSetByState() {};
	void AddAttackLaizer();

};

