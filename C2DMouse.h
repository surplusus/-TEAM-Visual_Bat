#pragma once
class CUI;
class C2DMouse
{
	DECLARE_SINGLETON(C2DMouse);
private:
	C2DMouse();
public:
	~C2DMouse();
private:
	POINT			m_GetCur;
public:
	POINT GetMousePoint();
public:
	//string IsInImage(vector<CUI*> vecUI);
	bool IsInImage(CUI* vecUI);
	CUI* IsInImage_(CUI* vecUI);

	UI_SPELLTYPE Is_PointInSpellImage(CUI * UI);
};
