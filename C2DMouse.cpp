#include "BaseInclude.h"
#include "C2DMouse.h"
#include "UI.h"
#include "Spell_.h"

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
	else return false;
}

CUI * C2DMouse::IsInImage_(CUI * vecUI)
{
	GetCursorPos(&m_GetCur);
	ScreenToClient(g_hWnd, &m_GetCur);
	if (PtInRect(&vecUI->GetRect(), m_GetCur))
		return vecUI;
	else return NULL;
}

UI_SPELLTYPE C2DMouse::Is_PointInSpellImage(CUI * UI)
{
	if (!UI) return SPELLTYPE_End;

	GetCursorPos(&m_GetCur);
	ScreenToClient(g_hWnd, &m_GetCur);
	if (PtInRect(&UI->GetRect(), m_GetCur))
	{
		cout << UI->GetRect().left << " " << UI->GetRect().top << " " << UI->GetRect().right << " " << UI->GetRect().bottom << endl;
		return ((CSpell_*)UI)->GetType();
	}
}
