#pragma once
#include "Bound.h"
class CBoundingSphere :
	public CBound
{
public:
	CBoundingSphere(float r = 1.f, D3DXVECTOR3 p = D3DXVECTOR3(0.f,0.f,0.f));
	virtual ~CBoundingSphere();
public:
	virtual HRESULT	 InitMesh(LPDIRECT3DDEVICE9 pDevice);
};

