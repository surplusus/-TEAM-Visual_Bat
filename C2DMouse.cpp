#include "BaseInclude.h"
#include "C2DMouse.h"
#include "UI.h"

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

//string C2DMouse::IsInImage(vector<CUI*> pUI)
//{
//	string s = "";
//	GetCursorPos(&m_GetCur);
//	ScreenToClient(g_hWnd, &m_GetCur);
//	for(int i = 0; i < pUI.size();i++)
//	if (PtInRect(&pUI[i]->GetRect(), m_GetCur)) 
//		return pUI[i]->GetName();
//	return s;
//}

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

//string C2DMouse::IsInImage_(vector<CUI*>* vecUI)
//{
//	for (int i = 0; i < vecUI->size(); i++)
//	{
//		if (PtInRect(&vecUI[i][i]->GetRect() , m_GetCur))
//			return vecUI[i][i]->GetName();
//	}
//	return NULL;
//}
