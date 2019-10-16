#include "BaseInclude.h"
#include "Spell_.h"
#include "Image_Loader.h"
#include "C2DMouse.h"



CSpell_::CSpell_(string name, string FileName, D3DXVECTOR3 pos, D3DXVECTOR3 vScale, UI_SPELLTYPE etype)
	: CUI(name, FileName, pos, vScale),  bClicked(false), m_eType(etype)
{
}

CSpell_::~CSpell_()
{
}

void CSpell_::Initialize()
{
	m_ImageLoader = new CImage_Loader(m_FileName,m_vPosition,m_vScale);
	m_ImageLoader->Initialize();
	m_Rect.left = m_vPosition.x;
	m_Rect.top = m_vPosition.y;
	m_Rect.right = m_vPosition.x + m_ImageLoader->GetImageInfo().Width * m_vScale.x;
	m_Rect.bottom = m_vPosition.y + m_ImageLoader->GetImageInfo().Height * m_vScale.y;
}

int CSpell_::Progress()
{
	if (Checked() == true)
		return true;
	return false;
}

void CSpell_::Render()
{
	m_ImageLoader->Render();
}

void CSpell_::Render(D3DXVECTOR3 pos)
{
	m_ImageLoader->Render(pos);
}

void CSpell_::Release()
{
	m_ImageLoader->Release();
}

bool CSpell_::Checked()
{
	//if (GetAsyncKeyState(VK_LBUTTON))
	//{
	//	if (GET_SINGLE(C2DMouse)->IsInImage(this))
	//	{
	//		bClicked = true;
	//		return bClicked;
	//	}
	//}
	//return bClicked;
	return false;
}