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
	atomic<bool>				m_bOnSwitch;
	void SetUp_ProgressBar();
	void Render_ProgressBar();
public:
	void SetTextureByPara(LPD3DXSPRITE pSprite, LPDIRECT3DTEXTURE9 pTexture);
	void SetSwitch(bool bOnOff) { m_bOnSwitch = bOnOff; }
};

