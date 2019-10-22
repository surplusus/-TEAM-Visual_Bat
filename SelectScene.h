#pragma once
#pragma once
#include "Scene.h"

class CUI;
class CAbilityPage;
class C2DMouse;
class CImage_Loader;
class CDropBox;

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

	vector<map<string, CUI*>>			m_vmapSpellList_1;
	vector<map<string, CUI*>>			m_vmapSpellList_2;

	void ChampInitialize();
	void SpellInitialize();
	void ChampRender();
	void SpellRender();

	CDropBox*							m_pDropBox_1;
	CDropBox*							m_pDropBox_2;
	bool m_bChecked_1;
	bool m_bChecked_2;
	bool Checked();
	void Selected();
};

