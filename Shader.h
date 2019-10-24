#pragma once
class CShader
{
public:
	CShader();
	~CShader();
protected:
	LPD3DXEFFECT gTextureMappingShader = NULL;
	LPDIRECT3DTEXTURE9 gpEarthDM = NULL;
	LPDIRECT3DTEXTURE9 gpEarthDM2 = NULL;
	LPD3DXMESH gModel;

public:
	virtual HRESULT LoadAsset(const TCHAR* pFileName);
	void Release();
	LPD3DXEFFECT LoadShader(const TCHAR * pFileName);	
	LPD3DXMESH LoadModel(const TCHAR * pFileName);
};

