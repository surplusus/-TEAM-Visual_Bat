#pragma once
#include"Scene.h"

class CParticle;
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
private:
	HRESULT InitAsset();
public:
	virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	CParticle* TestParticle;
};

