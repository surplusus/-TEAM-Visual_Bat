#pragma once
#pragma once
#include "Scene.h"

class CUI;
class CAbilityPage;
class C2DMouse;
class CImage_Loader;
class CDropBox;
class CTextMgr;

class CSelectScene :
	public CScene
{
public:
	CSelectScene();
	~CSelectScene();

public:
	HRESULT Initialize() override;
	void Progress() override;
	void Render() override;
	void Release() override;
private:
	C2DMouse*					m_p2Dmouse;
	bool m_bView;

private:
	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:// Champion map


private:
	CAbilityPage*						m_page;

	// >> temp
private:
	vector<CImage_Loader*>						m_vecBackGround;

	// >> new class
	CUI*								m_pChamp;
	CUI*								m_pSpell;

	CUI*								m_pSpellRender_1;
	CUI*								m_pSpellRender_2;

	vector<CUI*>						m_vecChamp;
	vector<CUI*>						m_vecChampCircle;

	map<string, vector<CUI*>*>			m_mapUI_List;

	vector<CUI*>						m_vecSpell;

	map<string, CUI*>					m_mapSpellList;
	map<string, CUI*>					m_mapSpellList_2;

	vector<CUI*>						m_VecSelectImage;

	void ChampInitialize();
	void SpellInitialize();
	void ChampRender();
	void SpellRender();

	CDropBox*							m_pDropBox_1;
	CDropBox*							m_pDropBox_2;

private:
	bool m_bChecked_1;
	bool m_bChecked_2;
	bool Checked();
	void Selected_1();
	void Selected_2();
	bool isChecked_1;
	bool isChecked_2;

private:
	string m_ChampName;
	string m_Spell_1Name;
	string m_Spell_2Name;
public:
	string GetChampName() { return m_ChampName; }
	string GetSpell_1Name() { return m_Spell_1Name; }
	string GetSpell_2Name() { return m_Spell_2Name; }

private:
	CTextMgr*				m_pTextMgr;

	CImage_Loader*			m_ReddyButton;
	bool					m_Reddy;
	bool					m_bChampCheck;
	CImage_Loader*			m_ReddyState;
	CImage_Loader*			m_TimerImage;
};

