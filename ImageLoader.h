#pragma once
class cImageLoader
{
public:
	cImageLoader();
	explicit cImageLoader(LPCWSTR nFileName, D3DXVECTOR3 nImagePos);

	~cImageLoader();

public:
	cImageLoader * Initialize();
	void Progress();
	void Render();
	void Release();

private:
	LPD3DXSPRITE m_pSprite;
	D3DXIMAGE_INFO m_stImageInfo;
	LPDIRECT3DTEXTURE9 m_pTextureUI;
	LPCWSTR m_FileName;
	D3DXVECTOR3 m_ImagePos;

public:
	D3DXIMAGE_INFO * GetImageInfo() { return &m_stImageInfo; }
	D3DXVECTOR3 * GetImagePos() { return &m_ImagePos; }
};

