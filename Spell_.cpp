#include "BaseInclude.h"
#include "Spell_.h"
#include "Image_Loader.h"
#include "C2DMouse.h"
#include "DropBox.h"


CSpell_::CSpell_(string name, string FileName, D3DXVECTOR3 pos, D3DXVECTOR3 vScale, UI_SPELLTYPE etype)
	: CUI(name, FileName, pos, vScale), m_eType(etype),  m_bClicked(false), m_dropbox(NULL)
{
}

CSpell_::~CSpell_()
{
}

void CSpell_::Initialize()
{
	m_ImageLoader = new CImage_Loader(m_FileName,m_vPosition,m_vScale);
	m_ImageLoader->Initialize();
	m_dropbox = new CDropBox(m_vPosition, m_vScale);
	m_dropbox->Initialize();
}

int CSpell_::Progress()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (GET_SINGLE(C2DMouse)->IsInImage(this))
		{
			m_bClicked = true;
		}
		else
		{
			m_bClicked = false;
		}
	}
	return false;

	m_dropbox->Progress();
}

void CSpell_::Render()
{
	m_ImageLoader->Render();
	if (m_bClicked) m_dropbox->Render();
}

void CSpell_::Render(D3DXVECTOR3 pos)
{
	m_ImageLoader->Render(pos);
}

void CSpell_::Release()
{
	m_ImageLoader->Release();
}