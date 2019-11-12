#pragma once
#include "Scene.h"

class GuhyunScene :	public CScene
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
	virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override {}
private:
	float					m_fSceneTime = 0.f;
	class CHeightMap*		m_pHeightMap = nullptr;
	class CMinionMgr*		m_pMinionMgr = nullptr;
	class CMinion*			m_pMinion = nullptr;
	class CCursor*			m_pCursor = nullptr;
private:
	HRESULT Setup();
	void SetUp_Light();
	void SoundUpdate();
	void LetObjectKnowHeightMap();
public:
	void GetMinionMgr(void** pMinionMgr);
	void GetCursor(void** pCursor);
};

