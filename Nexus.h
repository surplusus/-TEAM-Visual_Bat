#pragma once
#include "Tower.h"

class CHeightMap;
class CGauge;
class ColiderComponent;
class CNexus :
	public CTower
{
public:
	CNexus() {}
	~CNexus();
	explicit CNexus(D3DXVECTOR3 pos);
public:
private:
	CHeightMap*			m_pHeightMap = nullptr;

	list<ColiderComponent*> m_ColiderList;
public:
	virtual HRESULT Initialize() override;
	virtual void	Progress()   override;
	virtual void	Render()     override;
	virtual void	Release()    override;

private:
	virtual void ChangeAniSetByState() {  };
	void PaticleCollisionEvent(COLLISIONEVENT* Evt);
	void OnFindPickingSphere(PICKSPHEREEVENT * evt);


	bool AnimationSet();

	
};

