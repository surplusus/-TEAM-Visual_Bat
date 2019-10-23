#pragma once
#include "Scene.h"

class cGameHUD;

class cHUDScene
	: public CScene
{
public:
	cHUDScene();
	~cHUDScene();

public:
	virtual HRESULT Initialize();
	virtual void Progress();
	virtual void Render();
	virtual void Release();

	virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

