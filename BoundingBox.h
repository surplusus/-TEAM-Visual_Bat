#pragma once
#include "Bound.h"
class CBoundingBox :
	public CBound
{
public:
	CBoundingBox(D3DXVECTOR3 min = D3DXVECTOR3(-1.f, -1.f, -1.f), D3DXVECTOR3 max = D3DXVECTOR3(1.f, 1.f, 1.f));
	virtual ~CBoundingBox();
public:
	virtual HRESULT	 InitMesh(LPDIRECT3DDEVICE9 pDevice);

};

