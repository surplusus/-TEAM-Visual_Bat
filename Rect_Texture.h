#pragma once
#include "VIBuffer.h"
class CRect_Texture :
	public CVIBuffer
{
public:
	CRect_Texture();
	~CRect_Texture();
public:

	virtual HRESULT CreateVertexIndexBuffer(LPDIRECT3DDEVICE9 pDevice
		, const int& iVtxCntX = 0
		, const int& iVtxCntZ = 0
		, const float& fGap = 1);
	virtual void Buffer_Render(LPDIRECT3DDEVICE9 pDevice);
	virtual void Release(void);
};

