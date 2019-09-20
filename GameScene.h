#pragma once
#include"Scene.h"
class CCube;
class CGrid;
class CCamera;
class CXFileUtil;
class CObjMgr;
class GameScene: public CScene
{
public:
	GameScene();
	~GameScene();
public:
	CObjMgr* m_pObjMgr;
	virtual HRESULT Initalize() ;
	virtual void Progress()  ;
	virtual void Render()    ;
	virtual void Release()   ;

private:
	HRESULT Setup();
	void Update();

public:
	virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	CCube* m_pCube;
	CGrid* m_pGrid;
	vector<CXFileUtil*> m_XImg;

};

