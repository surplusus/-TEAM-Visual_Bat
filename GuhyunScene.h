#pragma once
#include "Scene.h"

class GuhyunScene :
	public CScene
{
public:
	GuhyunScene();
	virtual ~GuhyunScene();
public:
	class CObjMgr* m_pObjMgr;
	virtual HRESULT Initialize();
	virtual void Progress();
	virtual void Render();
	virtual void Release();
private:
	float		m_fSceneTime = 0.f;
private:
	HRESULT Setup();
	void SoundUpdate();
public:
	virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	bool EnqueueLoadMapFunc();
	// Thread MapLoad
	//static bool m_bMapLoad;
	static bool LoadMapByThread();
	class MinionMgr*  m_minion;
};

