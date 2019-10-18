#include "BaseInclude.h"
#include "Spell_.h"
#include "Image_Loader.h"
#include "C2DMouse.h"



CSpell_::CSpell_(string name, string FileName, D3DXVECTOR3 pos, D3DXVECTOR3 vScale, UI_SPELLTYPE etype)
	: CUI(name, FileName, pos, vScale), m_eType(etype)
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

	cout << endl;
	cout << m_name << endl;
	cout << m_vPosition.x << " " << m_vPosition.y << endl;
	cout << m_Rect.left << " " << m_Rect.top << " " << m_Rect.right << " " << m_Rect.bottom << endl;
}

int CSpell_::Progress()
{
	return false;
}

void CSpell_::Render()
{
	m_ImageLoader->Render();
}

void CSpell_::Render(D3DXVECTOR3 pos)
{
	m_ImageLoader->Render(pos);
	Rectangle(GetDC(g_hWnd), m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
}

void CSpell_::Release()
{
	m_ImageLoader->Release();
}