#pragma once
#include "UI.h"
class CImage_Loader;
class CSelectedChampion :
	public CUI
{
public:
	CSelectedChampion();
	~CSelectedChampion();
	CSelectedChampion(D3DXVECTOR3 color);
private:
	D3DXVECTOR3					m_vColor;
public:
	void Initialize();
	int Progress();
	void Render();
	void Release();
	void Render(D3DXVECTOR3 pos);
private:
	CImage_Loader*				m_pLoadingBoarder_blue;
	CImage_Loader*				m_pLoadingBoarder_red;
};