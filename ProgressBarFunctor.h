#pragma once
class CLoadingScene;
class CProgressBarFunctor
{
public:
	CProgressBarFunctor(CLoadingScene*	pLoadingScene);
	CProgressBarFunctor(CProgressBarFunctor&& functor);
	CProgressBarFunctor(const CProgressBarFunctor& func);
	~CProgressBarFunctor();
	bool operator()();
public:
	CLoadingScene*				m_pLoadingScene;
	LPD3DXSPRITE				m_pLoadingSprite;
	LPDIRECT3DTEXTURE9			m_pLoadingTexture;
	D3DXIMAGE_INFO				m_ImageInfo;
	int							m_iProgressBar;
	int							m_iTimeProgressed;
	void SetUp_ProgressBar();
	void Render_ProgressBar();
};

