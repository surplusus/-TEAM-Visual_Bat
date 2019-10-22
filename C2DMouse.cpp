#include "BaseInclude.h"
#include "C2DMouse.h"
#include "UI.h"
#include "Spell_.h"
#include "Image_Loader.h"

C2DMouse::C2DMouse()
{
}


C2DMouse::~C2DMouse()
{
}


POINT C2DMouse::GetMousePoint()
{
	return m_GetCur;
}

bool C2DMouse::IsInImage(CUI * vecUI)
{
	GetCursorPos(&m_GetCur);
	ScreenToClient(g_hWnd, &m_GetCur);
	if (PtInRect(&vecUI->GetRect(), m_GetCur))
		return true;
	else 
	{
		cout << "you not enough in Rect" << endl;
		return false;
	}
}

CUI * C2DMouse::IsInImage_(vector<CUI *> vecUI)
{
	GetCursorPos(&m_GetCur);
	ScreenToClient(g_hWnd, &m_GetCur);
	cout << "ÂïÈù À§Ä¡ : " << m_GetCur.x << " " << m_GetCur.y << endl;
	for (int i = 0; i < vecUI.size(); i++)
	{
		RECT rt = vecUI[i]->GetRect();
		if (PtInRect(&rt, m_GetCur))
		{
			return vecUI[i];
			break;
		}
		else
		{
			cout << "you not enough in Rect" << endl;
			continue;
		}
	}
	return NULL;
}

UI_SPELLTYPE C2DMouse::Is_PointInSpellImage(CUI * UI)
{
	if (!UI) return SPELLTYPE_End;

	GetCursorPos(&m_GetCur);
	ScreenToClient(g_hWnd, &m_GetCur);

	RECT rt = ((CSpell_*)UI)->GetRect();

	if (PtInRect(&rt, m_GetCur))
	{
		return ((CSpell_*)UI)->GetType();
	}

	return SPELLTYPE_End;
}

string C2DMouse::IsInImage_Spell(CUI * UI)
{
	if (!UI) return NULL;

	GetCursorPos(&m_GetCur);
	ScreenToClient(g_hWnd, &m_GetCur);
	
	RECT rc = ((CSpell_*)UI)->GetRect();
	if (PtInRect(&rc, m_GetCur))
	{
		return UI->GetName();
	}
}
