#pragma once
#include "Texture.h"
class CNormalTexture :
	public CTexture
{
public:
	CNormalTexture();
	~CNormalTexture();
public:
	HRESULT		InsertTexture(LPDIRECT3DDEVICE9 pDevice
		, const TCHAR* pFileName
		, const TCHAR* pStateKey
		, const int& iCnt = 1, TERRIAN_INSERTTYPE = INSERTTYPE_NUMBER);

};

