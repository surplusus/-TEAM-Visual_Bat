#pragma once
#include "ColiderComponent.h"
class CObj;
class CObjectColider :
	public ColiderComponent
{
public:
	CObjectColider(CObj* pObj);
	~CObjectColider();
private:
	CObj* m_pObj;
	const COLISION_TYPE m_Type;
public:
	virtual COLISION_TYPE GetType() override { return m_Type; }
	virtual void Update(D3DXVECTOR3 vPos) override;
};
