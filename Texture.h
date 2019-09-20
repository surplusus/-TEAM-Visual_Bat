#pragma once
class CTexture
{
public:
	CTexture();
	virtual ~CTexture();
protected:
	map<const TCHAR*, vector<TEXINFO*>> m_MapTexture;
public:


	//키값으로 텍스트의 정보를가져온다.
	const TEXINFO* GetTexture(const TCHAR* pStateKey, const int& iCnt = 0);
	//디바이스 ,텍스쳐 경로,키값
	virtual HRESULT InsertTexture(LPDIRECT3DDEVICE9 pDevice, 
		const TCHAR* pFileName
		, const TCHAR*pStateKey
		, const int&iCnt = 1,TERRIAN_INSERTTYPE = INSERTTYPE_NUMBER) PURE;
public:
	virtual void Release();


};

