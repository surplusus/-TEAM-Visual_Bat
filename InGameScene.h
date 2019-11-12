#pragma once
#include "Scene.h"
class CObjMgr;
class CHeightMap;
class CMinionMgr;
class CMinion;
class CCursor;
class CInGameScene : public CScene
{
public:
	CInGameScene();
	virtual ~CInGameScene();
public:
	virtual HRESULT Initialize() override;
	virtual void Progress()		 override;
	virtual void Render()		 override;
	virtual void Release()		 override;
	virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override {}
private:
	CObjMgr*			m_pObjMgr;
	float				m_fSceneTime = 0.f;
	CHeightMap*			m_pHeightMap = nullptr;
	CMinionMgr*			m_pMinionMgr = nullptr;
	CMinion*			m_pMinion = nullptr;
	CCursor*			m_pCursor = nullptr;
private:
	HRESULT Setup_Light();
	HRESULT Setup_Camera();
	void SoundUpdate();
	void LetObjectKnowHeightMap();
	bool InitAsset();
	bool InitAddObject();

public:
	void GetMinionMgr(void** pMinionMgr);
	void GetCursor(void** pCursor);
};

