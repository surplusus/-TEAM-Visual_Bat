#include "BaseInclude.h"
#include "ImageLoader.h"


cImageLoader::cImageLoader()
{
}

cImageLoader::cImageLoader(LPCWSTR nFileName, D3DXVECTOR3 nImagePos)
	: m_pSprite(NULL)
	, m_pTextureUI(NULL)
	, m_FileName(nFileName)
	, m_ImagePos(nImagePos)
{
}


cImageLoader::~cImageLoader()
{
}

cImageLoader * cImageLoader::Initialize()
{
	D3DXCreateSprite(GetDevice(), &m_pSprite);

	D3DXCreateTextureFromFileEx(
		GetDevice(),
		m_FileName,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImageInfo,
		NULL,
		&m_pTextureUI
	);

	return this;
}

void cImageLoader::Progress()
{
}

void cImageLoader::Render()
{
	m_pSprite->Begin(
		D3DXSPRITE_ALPHABLEND
		| D3DXSPRITE_SORT_TEXTURE
	);

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	m_pSprite->SetTransform(&matT);

	RECT rc;
	SetRect(&rc, 0, 0, 
		m_stImageInfo.Width, m_stImageInfo.Height);

	m_pSprite->Draw(
		m_pTextureUI,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&m_ImagePos,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	m_pSprite->End();
}

void cImageLoader::Release()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTextureUI);
}
