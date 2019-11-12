#pragma once
#include "Turret.h"
class CChaosTurret :
	public CTurret
{
public:
	CChaosTurret();
	~CChaosTurret();
	CChaosTurret(D3DXVECTOR3 pos, TCHAR* TurretName, float Rotation_Radian);
	
public:
	virtual HRESULT Initialize() override;
	virtual void Progress() override;
	virtual void Render() override;
	virtual void Release() override;

protected:
	virtual void ChangeAniSetByState() override {};

	TCHAR*							m_name;
	float							m_RotRadian;
	
};

