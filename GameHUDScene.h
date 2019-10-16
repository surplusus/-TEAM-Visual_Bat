#pragma once

#include "Scene.h"

class cGameHUD;

class cGameHUDScene
	: public CScene
{
public:
	cGameHUDScene();
	~cGameHUDScene();

	virtual HRESULT Initialize();
	virtual void Progress();
	virtual void Render();
	virtual void Release();

public:
	virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	cGameHUD * m_pGameHUD;
};

