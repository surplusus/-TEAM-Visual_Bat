#pragma once
#include "Scene.h"
class CTestScene :
	public CScene
{
public:
	CTestScene();
	virtual ~CTestScene();
public:
	class CObjMgr*		m_pObjMgr;
	virtual HRESULT	Initialize() override;
	virtual void Progress()		 override;
	virtual void Render()		 override;
	virtual void Release()		 override;
	virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override {}

private:
	float						m_fSceneTime = 0.f;
	class CHieghtMap*			m_pHeightMap = NULL;

private:
	HRESULT	Setup();
	void SoundUpdate();

	class MinionMgr*			m_minion;
};

