#pragma once
#include "Texture.h"
class CCubeTexture :
	public CTexture
{
public:
	CCubeTexture();
	~CCubeTexture();
public:
	HRESULT		InsertTexture(LPDIRECT3DDEVICE9 pDevice
		, const TCHAR* pFileName
		, const TCHAR* pStateKey
		, const int& iCnt = 1, TERRIAN_INSERTTYPE = INSERTTYPE_NUMBER);
};

