#pragma once
#include"Scene.h"
class CCube;
class CGrid;
class CCamera;
class CXFileUtil;
class GameScene: public CScene
{
public:
	GameScene();
	~GameScene();
public:
	
	virtual void Initalize() ;
	virtual void Progress()  ;
	virtual void Render()    ;
	virtual void Release()   ;

private:
	void Setup();
	void Update();

public:
	virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	CCube* m_pCube;
	CGrid* m_pGrid;
	CCamera* m_pCamera;
	vector<CXFileUtil*> m_XImg;

};

