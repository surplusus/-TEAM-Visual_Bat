#include "BaseInclude.h"
#include "SelectScene.h"
#include "C2DMouse.h"
#include "AbilityPage.h"
#include "Image_Loader.h"
#include "Champ.h"
#include "Spell_.h"


CSelectScene::CSelectScene()
	:m_p2Dmouse(NULL)
	, m_testsuzi(NULL)
	, m_pChamp(NULL)
	, m_pSpell(NULL)
	, m_pSpellRender_1(NULL)
	, m_pSpellRender_2(NULL)
{
	
	
}


CSelectScene::~CSelectScene()
{
}

HRESULT CSelectScene::Initialize()
{	
	m_testsuzi = new CImage_Loader("Resource/choen/suzi.jpeg", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1.7f, 1.7f, 0));
	if (m_testsuzi)	m_testsuzi->Initialize();

	ChampInitialize();
	SpellInitialize();
	map<string, vector<CUI*>*>::iterator iter = m_mapUI_List.begin();
	for(iter; iter != m_mapUI_List.end(); ++iter)
	{
		vector<CUI*>::iterator iter2 = (*m_mapUI_List[iter->first]).begin();
		for (iter2; iter2!=(*m_mapUI_List[iter->first]).end();++iter2)
		{
			(*iter2)->Initialize();
		}
	}
	return E_NOTIMPL;
}
void CSelectScene::Progress()
{
	for (int i = 0; i < m_vecChamp.size(); i++)
	{
		if (m_vecChamp[i]->Progress())
		{
			m_vecChampCircle[i]->Progress();
		}
	}
}

void CSelectScene::Render()
{
	if (m_testsuzi) m_testsuzi->Render();
	map<string, vector<CUI*>*>::iterator iter = m_mapUI_List.begin();
	for (iter; iter != m_mapUI_List.end(); ++iter)
	{
		vector<CUI*>::iterator iter2 = (*m_mapUI_List[iter->first]).begin();
		for (iter2; iter2 != (*m_mapUI_List[iter->first]).end(); ++iter2)
		{
			(*iter2)->Render();
		}
	}
	ChampRender();
	SpellRender();
}

void CSelectScene::Release()
{
}

void CSelectScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}


void CSelectScene::ChampInitialize()
{
	m_vecChamp.push_back(new CChamp("Garen", "Resource/choen/ChampImage/Garen/Garen_Square.dds",   D3DXVECTOR3(250, 150, 0),D3DXVECTOR3(0.5f, 0.5f, 0.5f)));
	m_vecChamp.push_back(new CChamp("Aatrox", "Resource/choen/ChampImage/Atrox/Aatrox_Square.dds", D3DXVECTOR3(350, 150, 0),D3DXVECTOR3(0.5f, 0.5f, 0.5f)));
	m_mapUI_List.insert(make_pair("Champ", &m_vecChamp));

	m_vecChampCircle.push_back(new CChamp("Garen", "Resource/choen/ChampImage/Garen/Garen_Circle.dds",   D3DXVECTOR3(80, 300, 0), D3DXVECTOR3(0.5f, 0.5f, 0.5f),UI_CHAMPTYPE_DYNAMIC));
	m_vecChampCircle.push_back(new CChamp("Aatrox", "Resource/choen/ChampImage/Atrox/Aatrox_Circle.dds", D3DXVECTOR3(80, 300, 0), D3DXVECTOR3(0.5f, 0.5f, 0.5f),UI_CHAMPTYPE_DYNAMIC));

	for (int i = 0; i < m_vecChampCircle.size(); i++)
	{
		m_vecChampCircle[i]->Initialize();
	}
}

void CSelectScene::SpellInitialize()
{
	/*
	480, 500 / 530, 500/ 575, 500/ 625, 500
	480, 570 / 530, 570/ 575/ 570/ 625, 570
	480, 640
	*/	
	m_vecSpell.push_back(new CSpell_("Cleanse", "Resource/choen/Spell_Image/Cleanse.png", D3DXVECTOR3(480, 500, 0), D3DXVECTOR3(0.5f, 0.5f, 0.5f)));
	m_vecSpell.push_back(new CSpell_("Exhaust", "Resource/choen/Spell_Image/Exhaust.png", D3DXVECTOR3(530, 500, 0), D3DXVECTOR3(0.5f, 0.5f, 0.5f)));
	m_vecSpell.push_back(new CSpell_("Flash", "Resource/choen/Spell_Image/Flash.png",   D3DXVECTOR3(580, 500, 0), D3DXVECTOR3(0.5f, 0.5f, 0.5f)));
	m_vecSpell.push_back(new CSpell_("Ghost", "Resource/choen/Spell_Image/Ghost.png",   D3DXVECTOR3(630, 500, 0), D3DXVECTOR3(0.5f, 0.5f, 0.5f)));
	m_vecSpell.push_back(new CSpell_("Heal", "Resource/choen/Spell_Image/Heal.png",    D3DXVECTOR3(480, 570, 0), D3DXVECTOR3(0.5f, 0.5f, 0.5f)));
	m_vecSpell.push_back(new CSpell_("Smite", "Resource/choen/Spell_Image/Smite.png",   D3DXVECTOR3(530, 570, 0), D3DXVECTOR3(0.5f, 0.5f, 0.5f)));
	m_vecSpell.push_back(new CSpell_("Teleport", "Resource/choen/Spell_Image/Teleport.png",D3DXVECTOR3(580, 570, 0), D3DXVECTOR3(0.5f, 0.5f, 0.5f)));
	m_vecSpell.push_back(new CSpell_("Ignite", "Resource/choen/Spell_Image/Ignite.png",  D3DXVECTOR3(630, 570, 0), D3DXVECTOR3(0.5f, 0.5f, 0.5f)));
	m_vecSpell.push_back(new CSpell_("Barrier", "Resource/choen/Spell_Image/Barrier.png", D3DXVECTOR3(480, 640, 0), D3DXVECTOR3(0.5f, 0.5f, 0.5f)));
	m_mapUI_List.insert(make_pair("Spell", &m_vecSpell));

	m_pSpellRender_1 = m_vecSpell[rand() % 9];
	m_pSpellRender_2 = m_vecSpell[rand() % 9];

	m_pSpellRender_1->Initialize();
	m_pSpellRender_2->Initialize();
}

void CSelectScene::ChampRender()
{
	for (int i = 0; i < m_vecChampCircle.size(); i++)
	{
		m_vecChampCircle[i]->Render();
	}
}

void CSelectScene::SpellRender()
{
	m_pSpellRender_1->Render(D3DXVECTOR3(20, 20, 0));
	m_pSpellRender_1->Render(D3DXVECTOR3(540, 740, 0));
	m_pSpellRender_2->Render(D3DXVECTOR3(20, 60, 0));
	m_pSpellRender_2->Render(D3DXVECTOR3(575, 740, 0));

	for (int i = 0; i < m_vecSpell.size(); i++)
	{
		m_vecSpell[i]->Render();
	}

}
