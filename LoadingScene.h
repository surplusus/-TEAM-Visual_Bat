#pragma once
#include "Scene.h"

class CImage_Loader;
class CSelectedPlayer;
class CSelectedSpells;
class CUI;
class CTextMgr;
class CLoadingFunctor;
class CMakingTowerFunctor;
class CProgressBarFunctor;
class CLoadingScene :	public CScene
{
private:
	friend class CProgressBarFunctor;
public:
	CLoadingScene();
	~CLoadingScene();
	CLoadingScene(CUI * Champ) {}
public:
	HRESULT Initialize();
	void Progress() ;
	void Render() ;
	void Release() ;
	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {}
private:
	CTextMgr*					m_pTextMgr;
	CImage_Loader*				m_pBackGround;
	CSelectedPlayer*			m_pChampSelect;
	CSelectedSpells*			m_pSpell_1;
	CSelectedSpells*			m_pSpell_2;
public:
	// << :: Functor
	CLoadingFunctor*			m_pLoadingFunctor;
	CMakingTowerFunctor*		m_pMakingTowerFunctor;
	CProgressBarFunctor*		m_pProgressBarFunctor;
	atomic<bool>				m_bOnSwitch;
	shared_future<bool>			m_future;
private:
	bool						m_bLoadingComplete;
	bool OperateLoadingFunctorThruThread();
	bool Progress_LoadingFunctors();
};

