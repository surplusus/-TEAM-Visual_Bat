#pragma once
#include "Scene.h"

class CImage_Loader;
class CSelectedChampion;
class CUI;
class CLoadingScene :
	public CScene
{
public:
	CLoadingScene();
	~CLoadingScene();
	CLoadingScene(CUI * Champ) {}
public:
	HRESULT Initialize();
	void Progress() ;
	void Render() ;
	void Release() ;
	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {}
private:
	LPD3DXSPRITE				m_pLoadingSprite;
	LPDIRECT3DTEXTURE9			m_pLoadingTexture;
	D3DXIMAGE_INFO				m_ImageInfo;
	void Render_Loading();
private:
	CImage_Loader*				m_pBackGround;
	CSelectedChampion*			m_pChampSelect;
	
	vector<D3DXVECTOR2>			m_vLinePoint;
	float						m_fLineLength;
	// << :: mediate
	map<string, string>			m_StringInfo;
public:
	map<string, string>* GetStringInfo() { return &m_StringInfo; }
	// >> :: mediate
};

