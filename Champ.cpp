#include "BaseInclude.h"
#include "Champ.h"
#include "Image_Loader.h"
#include"C2DMouse.h"

CChamp::CChamp(string name, string FileName, D3DXVECTOR3 pos, D3DXVECTOR3 vScale,UI_CHAMPTYPE eType)
: CUI(name, FileName, pos, vScale),bClicked(false), m_eType(eType)
{
}



CChamp::~CChamp()
{
}

void CChamp::Initialize()
{
	m_ImageLoader = new CImage_Loader(m_FileName,m_vPosition,m_vScale);
	m_ImageLoader->Initialize();

	m_Rect = GetRect();
	cout << m_Rect.left << " " << m_Rect.top << " " << m_Rect.right << " " << m_Rect.bottom << endl;
}

int CChamp::Progress()
{
	if (m_eType == UI_CHAMPTYPE_STATIC) 
	{
		if (CheckMouse())
		{
			return bClicked;
		}
	}
	if (bClicked == true)
	{
		return true;
	}
	return false;

}

void CChamp::Render()
{
	switch (m_eType)
	{
	case UI_CHAMPTYPE_STATIC:
		m_ImageLoader->Render();
		break;
	case UI_CHAMPTYPE_DYNAMIC:
		if (bClicked == true)
			m_ImageLoader->Render();
		break;
	default:
		break;
	}
}
void CChamp::Render(D3DXVECTOR3 pos)
{

}
void CChamp::Release()
{
	m_ImageLoader->Release();
}

bool CChamp::CheckMouse()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (GET_SINGLE(C2DMouse)->IsInImage(this))
		{
			bClicked = true;
			return bClicked;
		}
		else
		{
			bClicked = false;
			return bClicked;
		}
	}
	return false;
}