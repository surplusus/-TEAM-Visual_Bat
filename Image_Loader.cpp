#include "BaseInclude.h"
#include "Image_Loader.h"


CImage_Loader::CImage_Loader()
{
}


CImage_Loader::~CImage_Loader()
{
}

CImage_Loader::CImage_Loader(string FileName)
	: m_pSprite(NULL), m_pTexture(NULL), m_FileName(FileName)
{
	m_FileName = FileName;
}

CImage_Loader::CImage_Loader(string FileName, D3DXVECTOR3 pos, D3DXVECTOR3 vScale)
	:m_pSprite(NULL), m_pTexture(NULL), m_FileName(FileName),m_vPosition(pos),m_vScale(vScale)
{
//LPCWSTR
	
}

void CImage_Loader::Initialize()
{
	D3DXCreateSprite(GetDevice(), &m_pSprite);

	if (FAILED(D3DXCreateTextureFromFileExA(
		GetDevice(),
		m_FileName.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_ImageInfo,
		NULL,
		&m_pTexture
	))) 
		ERR_MSG(g_hWnd, L"Failed");

	m_Rect.left = m_vPosition.x;
	m_Rect.top = m_vPosition.y;
	m_Rect.right = m_vPosition.x + m_ImageInfo.Width * m_vScale.x;
	m_Rect.bottom = m_vPosition.y + m_ImageInfo.Height * m_vScale.y;
}


void CImage_Loader::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	D3DXMATRIXA16	matT, matR, matS, matWorld;

	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixTranslation(&matT,m_vPosition.x, m_vPosition.y, 0);

	

	matWorld = matS * matT;

	m_pSprite->SetTransform(&matWorld);
	

	RECT rc;
	SetRect(&rc, 0, 0, m_ImageInfo.Width, m_ImageInfo.Height);

	ID3DXSprite* temp;

	m_pSprite->Draw(m_pTexture, nullptr, nullptr,
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();
}

void CImage_Loader::Render(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	D3DXMATRIXA16	matT, matR, matS, matWorld;

	D3DXMatrixScaling(&matS, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, 0);

	

	matWorld = matS * matT;

	m_pSprite->SetTransform(&matWorld);

	RECT rc;
	SetRect(&rc, 0, 0, m_ImageInfo.Width, m_ImageInfo.Height);
	m_pSprite->Draw(m_pTexture, &rc, NULL,
		NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();
}

void CImage_Loader::Release()
{
	delete m_pSprite;
	delete m_pTexture;
}

int CImage_Loader::GetWidth()
{
	return m_ImageInfo.Width * m_vScale.x;
}

int CImage_Loader::GetHeight()
{
	return m_ImageInfo.Height * m_vScale.y;
}
