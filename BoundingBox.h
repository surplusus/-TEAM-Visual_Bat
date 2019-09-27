#pragma once
#include "Bound.h"
class CBoundingBox :
	public CBound
{
public:
	CBoundingBox();
	~CBoundingBox();
public:
	virtual HRESULT	 InitMesh(LPDIRECT3DDEVICE9 pDevice);

};

