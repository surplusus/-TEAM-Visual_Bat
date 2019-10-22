#pragma once
#include "Scene.h"

struct stEventInfo {
	bool m_bComplate;
	string m_sObjName;
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
	static atomic<vector<string> >	g_sThreadResult;
	float					m_fSceneTime = 0.f;
	vector<stEventInfo>		m_vFuncRegister;
	class CHeightMap*		m_pHeightMap = nullptr;
	bool					m_bLoading = true;
	class CLoadingScene*	m_pLoadingScene = nullptr;
	vector<bool>			m_vThreadCompleted;
private:
	HRESULT Setup();
	void SoundUpdate();
	void RegisterMapLoaded(REGISTEREVENT* evt);
	void RegisterMapLoaded(string sLoadResult);
public:
	void ProcessRegisterMapLoaded(stEventInfo evtInfo);
	virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override {}
private:
	// Thread MapLoad
	//static bool m_bMapLoad;
	static string AddStaticMeshByThread(string path, string fileName, string objName);
	static string AddDynamicMeshByThread(string path, string fileName, string objName);
	bool LoadResourceByThread();
	class MinionMgr*  m_minion;
};

