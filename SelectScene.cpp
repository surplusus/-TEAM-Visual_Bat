#include "BaseInclude.h"
#include "SelectScene.h"
#include "C2DMouse.h"
#include "AbilityPage.h"
#include "Image_Loader.h"
#include "Champ.h"
#include "Spell_.h"
#include "DropBox.h"
#include "Text.h"
#include "SceneMgr.h"
#include "LoadingScene.h"

static CUI* temp = NULL;
string g_ChampName;
string g_Spell_1;
string g_Spell_2;
CSelectScene::CSelectScene()
	:m_p2Dmouse(NULL)
	, m_testsuzi(NULL)
	, m_pChamp(NULL)
	, m_pSpell(NULL)
	, m_pSpellRender_1(NULL)
	, m_pSpellRender_2(NULL)
	, m_pDorpBox(NULL)
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
		if (m_vecChamp[i]->Progress()) {
			m_vecChampCircle[i]->Progress();
			((CChamp*)m_vecChampCircle[i])->SetClicked(((CChamp*)m_vecChamp[i])->GetClicked());
		}
	}
	if (m_pDorpBox) m_pDorpBox->Progress();
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (m_pDorpBox)
		{
			for (int i = 0; i < m_pDorpBox->GetVecSpells().size(); i++)
			{
				if (GET_SINGLE(C2DMouse)->IsInImage_(m_pDorpBox->GetVecSpells()[i]))
					g_Spell_1 = GET_SINGLE(C2DMouse)->IsInImage_Spell(m_pDorpBox->GetVecSpells()[i]);
			}
		}
	}


	if (GetAsyncKeyState(VK_ESCAPE))
	{
		GET_SINGLE(CSceneMgr)->SetState(new CLoadingScene);
	}
}

void CSelectScene::Render()
{
	//if (m_testsuzi) m_testsuzi->Render();

	MyDrawFPSByTimeMgr();

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
	m_vecChamp.push_back(new CChamp("Amumu", "Resource/choen/ChampImage/Amumu/Amumu_Square_0.dds", D3DXVECTOR3(250, 150, 0), D3DXVECTOR3(0.5f, 0.5f, 0.5f)));
	m_vecChamp.push_back(new CChamp("Ezreal", "Resource/choen/ChampImage/Ezreal/Ezreal_Square_0.dds", D3DXVECTOR3(350, 150, 0), D3DXVECTOR3(0.5f, 0.5f, 0.5f)));

	m_mapUI_List.insert(make_pair("Champ", &m_vecChamp));

	m_vecChampCircle.push_back(new CChamp("Amumu", "Resource/choen/ChampImage/Amumu/Amumu_Circle_0.dds", D3DXVECTOR3(80, 300, 0), D3DXVECTOR3(0.5f, 0.5f, 0.5f), UI_CHAMPTYPE_DYNAMIC));
	m_vecChampCircle.push_back(new CChamp("Ezreal", "Resource/choen/ChampImage/Ezreal/Ezreal_Circle.dds", D3DXVECTOR3(80, 300, 0), D3DXVECTOR3(0.5f, 0.5f, 0.5f), UI_CHAMPTYPE_DYNAMIC));

	for (int i = 0; i < m_vecChampCircle.size(); i++)
		m_vecChampCircle[i]->Initialize();

	
}

void CSelectScene::SpellInitialize()
{
	m_pDorpBox = new CDropBox(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	if(m_pDorpBox)	m_pDorpBox->Initialize();

	if (m_pDorpBox)
	{
		m_pSpellRender_1 = m_pDorpBox->GetVecSpells()[rand() % m_pDorpBox->GetVecSpells().size()];
	}
}

void CSelectScene::ChampRender()
{
	for (int i = 0; i < m_vecChamp.size(); i++)
	{
		m_vecChamp[i]->Render();
	}
	for (int i = 0; i < m_vecChampCircle.size(); i++)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			m_pChamp = GET_SINGLE(C2DMouse)->IsInImage_(m_vecChamp[i]);
		}
		if (m_pChamp)
		{
			if (m_pChamp->GetName() == m_vecChampCircle[i]->GetName())
			{
				temp = m_vecChampCircle[i];
				g_ChampName = m_vecChampCircle[i]->GetName();
				break;
			}
		}
	}
	if(temp) temp->Render();
}

void CSelectScene::SpellRender()
{
	if(m_pDorpBox)	m_pDorpBox->Render();
	/*if (GetAsyncKeyState(VK_LBUTTON))
	{
		for (int i = 0; i < m_pDorpBox->GetVecSpells().size(); i++)
		{
			if (GET_SINGLE(C2DMouse)->IsInImage(m_pSpellRender_1))
				if (m_pDorpBox)
					m_pDorpBox->Render();
		}
	}*/

	if (m_pDorpBox)
	{
		for (int i = 0; i < m_pDorpBox->GetVecSpells().size(); i++)
			if (m_pDorpBox->GetVecSpells()[i]->GetName() == g_Spell_1)
				m_pSpellRender_1 = m_pDorpBox->GetVecSpells()[i];
	}
	if (m_pSpellRender_1)
	{
		m_pSpellRender_1->Render(D3DXVECTOR3(20, 300, 0));
		m_pSpellRender_1->Render(D3DXVECTOR3(500, 700, 0));
	}
}