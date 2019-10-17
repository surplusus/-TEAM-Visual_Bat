#pragma once
#include "Scene.h"

class CImage_Loader;

class CLoadingScene :
	public CScene
{
public:
	CLoadingScene();
	~CLoadingScene();
public:
	HRESULT Initialize();
	void Progress() ;
	void Render() ;
	void Release() ;
	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {}

private:
	CImage_Loader*				m_pBackGround;
};

