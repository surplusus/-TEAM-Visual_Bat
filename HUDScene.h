#pragma once
#include "Scene.h"

class cGameHUD;
class CTextMgr;

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

private:
	CObjMgr * m_pObjMgr;
	CHeightMap * m_pHeightMap;

public:
	HRESULT Setup();
	void Update();
	
	void LetObjectKnowHeightMap();
};

