#pragma once
#include "Tower.h"
class ColiderComponent;
class CTurret :
	public CTower
{
public:
	CTurret() {}
	CTurret(D3DXVECTOR3 pos, TCHAR* TurretName, float Rotation_Radian);
	virtual ~CTurret();
public:
	virtual HRESULT	Initialize() override;
	virtual void Progress() override;
	virtual void Render() override;
	virtual void Release() override;
protected:
	bool Animation_Break();

public:
	list<ColiderComponent*>				m_ColiderList;

protected:
	LPDIRECT3DTEXTURE9					m_pTexture;

	virtual void		ChangeAniSetByState() {};
	void AddAttackLaizer();
	TCHAR*							m_name;
	float							m_RotRadian;

public:
	void SetPosition(D3DXVECTOR3 position) { m_Info.vPos = position; }
	TCHAR* GetName()	{ return m_name; }
};

