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

bool C2DMouse::IsInImage(CUI* pUI)
{
	GetCursorPos(&m_GetCur);
	ScreenToClient(g_hWnd, &m_GetCur);
	if (PtInRect(&pUI->GetRect(), m_GetCur)) 
		return true;
	return false;
	
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
