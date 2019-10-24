#include "BaseInclude.h"
#include "Spell_.h"
#include "Image_Loader.h"
#include "C2DMouse.h"



CSpell_::CSpell_(string name, string FileName, D3DXVECTOR3 pos, D3DXVECTOR3 vScale, UI_SPELLTYPE etype)
	: CUI(name, FileName, pos, vScale), m_eType(etype),  m_bClicked(false)
{
}

CSpell_::~CSpell_()
{
}

void CSpell_::Initialize()
{
	m_ImageLoader = new CImage_Loader(m_FileName,m_vPosition,m_vScale);
	m_ImageLoader->Initialize();
	m_Rect = GetRect();
}

int CSpell_::Progress()
{
	return 0;
}

void CSpell_::Render()
{
	m_ImageLoader->Render();
}

void CSpell_::Render(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	m_ImageLoader->Render(pos, scale);
}

void CSpell_::Release()
{
	m_ImageLoader->Release();
}