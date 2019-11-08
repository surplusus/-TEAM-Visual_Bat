#pragma once
#include"ColiderComponent.h"
class CTargetColider :
	public ColiderComponent
{
public:
	CTargetColider();
	~CTargetColider();
private:
	const COLISION_TYPE m_Type;
public:
	virtual COLISION_TYPE GetType() override { return m_Type; }
	virtual void Update(D3DXVECTOR3 vPos) override;
	virtual bool CheckColision(ColiderComponent* pEnemy) override;
};

