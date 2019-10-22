#pragma once
#include"Scene.h"

//class CCamera;
//class CXFileUtil;
class CObjMgr;
class CGameScene: public CScene
{
public:
	CGameScene();
	~CGameScene();
public:
	CObjMgr* m_pObjMgr;
	virtual HRESULT Initialize() ;
	virtual void Progress()  ;
	virtual void Render()    ;
	virtual void Release()   ;

private:
	HRESULT Setup();
	void Update();
public:
	virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	
};

