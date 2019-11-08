#pragma once
#include "Tower.h"

class ColiderComponent;
class CInhibitor :
	public CTower
{
public:
	CInhibitor() {}
	explicit CInhibitor(D3DXVECTOR3 pos);
	virtual ~CInhibitor();
public:
	virtual HRESULT	Initialize() override;
	virtual void Progress() override;
	virtual void Render() override;
	virtual void Release() override;
private:

	list<ColiderComponent*> m_ColiderList;
private:

	bool Animation_Set();
	virtual void		ChangeAniSetByState() {};
public:
	void SetPosition(D3DXVECTOR3 position) { m_Info.vPos = position; }
	void PaticleCollisionEvent(COLLISIONEVENT* Evt);
	void OnFindPickingSphere(PICKSPHEREEVENT * evt);

};

