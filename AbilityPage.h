#pragma once
class CImage_Loader;

class CAbilityPage
{
public:
	CAbilityPage();
	~CAbilityPage();
private:
	D3DXIMAGE_INFO				m_stImageInfo;
	LPD3DXSPRITE				m_pSprite;
	LPDIRECT3DTEXTURE9			m_pTexture;

public:
	void Initialize();
	void Progress();
	void Render();
	void Release();
private:
	map<string, CImage_Loader*>				m_mapDetailedRune;
	map<string, CImage_Loader*>				m_mapContolRune;
	map<string, CImage_Loader*>				m_mapBrainStormRune;
	map<string, CImage_Loader*>				m_mapMasicRune;
	map<string, CImage_Loader*>				m_mapResolutionRune;
public:
	void ImageLoad_To_Detailed();
	void ImageLoad_To_Control();
	void ImageLoad_To_BrainStorm();
	void ImageLoad_To_Masic();
	void ImageLoad_To_Resolution();

	void ImageRender_To_Detailed();
	void ImageRender_To_Control();
	void ImageRender_To_BrainStorm();
	void ImageRender_To_Masic();
	void ImageRender_To_Resolution();
};