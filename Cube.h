#pragma once
#include "Obj.h"
class CCube :
	public CObj
{
public:
	CCube();
	CCube(D3DXVECTOR3 vPos, D3DXVECTOR3 vDir, D3DXVECTOR3 vRot);
	virtual ~CCube();
private:
	vector<ST_PC_VERTEX> m_vecVertex;
public:

	virtual void SetUp()  ;
	virtual void Update() ;
	virtual void Render() ;

};

