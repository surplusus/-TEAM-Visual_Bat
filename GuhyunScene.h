#pragma once
#include "Scene.h"

struct stEventInfo {
	bool m_bComplate;
	string m_sObjName;
	string m_sObjType;
};

class GuhyunScene :
	public CScene
{
public:
	GuhyunScene();
	virtual ~GuhyunScene();
public:
	class CObjMgr* m_pObjMgr;
	virtual HRESULT Initialize() override;
	virtual void Progress()		 override;
	virtual void Render()		 override;
	virtual void Release()		 override;
private:
	float		m_fSceneTime = 0.f;
	vector<stEventInfo> m_vFuncRegister;
	class CHeightMap*  m_pHeightMap = nullptr;
private:
	HRESULT Setup();
	void SoundUpdate();
	void RegisterMapLoaded(REGISTEREVENT* evt);
public:
	void ProcessRegisterMapLoaded(stEventInfo evtInfo);
	virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override {}
private:
	bool EnqueueLoadMapFunc();
	// Thread MapLoad
	//static bool m_bMapLoad;
	static bool LoadMapByThread();
	class MinionMgr*  m_minion;
};

