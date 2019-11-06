#pragma once
#include "VIBuffer.h"
class CRectColor :
	public CVIBuffer
{
public:
	CRectColor();
	~CRectColor();
public:
	virtual HRESULT CreateVertexIndexBuffer(LPDIRECT3DDEVICE9 pDevice
		, const int& iVtxCntX = 0
		, const int& iVtxCntZ = 0
		, const float& fGap = 1);
	virtual void Buffer_Render(LPDIRECT3DDEVICE9 pDevice);
};
