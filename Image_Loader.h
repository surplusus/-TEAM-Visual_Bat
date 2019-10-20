#pragma once
class CImage_Loader
{
public:
	CImage_Loader();
	~CImage_Loader();
	CImage_Loader(string FileName);
	CImage_Loader(string FileName,D3DXVECTOR3 pos,D3DXVECTOR3 vScale);

public:
	virtual void Initialize();
	virtual void Render();
protected:
	LPD3DXSPRITE					m_pSprite;
	PDIRECT3DTEXTURE9				m_pTexture;
	D3DXIMAGE_INFO					m_ImageInfo;
	RECT							m_Rect;
	string							m_FileName;
	D3DXVECTOR3						m_vScale;
	D3DXVECTOR3						m_vPosition;
public:
	string	GetFileName() { return m_FileName; }
	D3DXIMAGE_INFO	GetImageInfo() { return m_ImageInfo; }
	void Render(D3DXVECTOR3 pos);

	void Release();
	D3DXVECTOR3 GetPosition() { return m_vPosition; }
};

