#include "BaseInclude.h"
#include "SelectScene.h"
#include "C2DMouse.h"
#include "AbilityPage.h"
#include "Image_Loader.h"
#include "Champ.h"
#include "Spell_.h"
#include "TextMgr.h"
#include "SceneMgr.h"
#include "LoadingScene.h"
#include "DropBox.h"
#include "SceneMediator.h"

static CUI* Filnal_Champ = NULL;
static CUI* SpellRender_1 = NULL;
static CUI* SpellRender_2 = NULL;

CSelectScene::CSelectScene()
	:m_p2Dmouse(NULL)
	, m_pChamp(NULL)
	, m_pSpell(NULL)
	, m_pSpellRender_1(NULL)
	, m_pSpellRender_2(NULL)
	, m_bChecked_1(false)
	, m_bChecked_2(false)
	, m_pDropBox_1(NULL)
	, m_pDropBox_2(NULL)
	, isChecked_1(false)
	, isChecked_2(false)
	, m_pTextMgr(NULL)
	, m_ReddyButton(NULL)
	, m_Reddy(false)
	, m_bChampCheck(false)
	, m_ReddyState(NULL)
	, m_TimerImage(NULL)
{



}


CSelectScene::~CSelectScene()
{
}

HRESULT CSelectScene::Initialize()
{
	m_vecBackGround.push_back(new CImage_Loader("Resource/choen/Select/BackGround_.jpg", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1.0F, 1.0F, 0)));
	m_vecBackGround.push_back(new CImage_Loader("Resource/choen/Select/Pick.png", D3DXVECTOR3(0, 250, 0), D3DXVECTOR3(1.0F, 1.0F, 0)));


	m_ReddyButton = new CImage_Loader("Resource/choen/Select/ReddyButton.png", D3DXVECTOR3(610, 470, 0), D3DXVECTOR3(1.0f, 1.0f, 0));
	m_ReddyState = new CImage_Loader("Resource/choen/Select/ReddyButton_.png", D3DXVECTOR3(610, 470, 0), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_ReddyButton->Initialize();
	m_ReddyState->Initialize();

	m_TimerImage = new CImage_Loader("Resource/choen/Select/Time.png", D3DXVECTOR3(191, 38, 0), D3DXVECTOR3(1.0f, 1.0f, 0));
	m_TimerImage->Initialize();

	for (int i = 0; i < m_vecBackGround.size(); i++)
	{
		if (m_vecBackGround[i])
		{
			m_vecBackGround[i]->Initialize();
		}
	}
	ChampInitialize();
	SpellInitialize();
	
	
	map<string, vector<CUI*>*>::iterator iter = m_mapUI_List.begin();
	for (iter; iter != m_mapUI_List.end(); ++iter)
	{
		vector<CUI*>::iterator iter2 = (*m_mapUI_List[iter->first]).begin();
		for (iter2; iter2 != (*m_mapUI_List[iter->first]).end(); ++iter2)
		{
			(*iter2)->Initialize();
		}
	}
	m_pTextMgr = new CTextMgr;
	m_pTextMgr->Initialize();
	return E_NOTIMPL;
}
void CSelectScene::Progress()
{
	if (!m_Reddy)
	{
		for (int i = 0; i < m_vecChamp.size(); i++)
		{
			if (m_vecChamp[i]->Progress()) {
				m_vecChampCircle[i]->Progress();
				((CChamp*)m_vecChampCircle[i])->SetClicked(((CChamp*)m_vecChamp[i])->GetClicked());
			}
		}

		if (GetAsyncKeyState(VK_LBUTTON))
		{
			m_pChamp = GET_SINGLE(C2DMouse)->IsInImage_(m_vecChamp);

			for (int i = 0; i < m_vecChampCircle.size(); i++)
			{
				if (m_pChamp)
				{
					string Sname = m_pChamp->GetName();
					if (Sname == m_vecChampCircle[i]->GetName())
					{
						Filnal_Champ = m_vecChampCircle[i];
						m_ChampName = Sname;
						m_bChampCheck = true;
						break;
					}
				}
			}
		}


		if (Filnal_Champ && SpellRender_1 && SpellRender_2)
		{
			GET_SINGLE(CSceneMgr)->GetSceneMediator()->SetSelectedChampInfo
			(
				new ST_SELECTED_CHAMP_INFO
				(
					Filnal_Champ->GetName(),
					SpellRender_1->GetName(),
					SpellRender_2->GetName()
				)
			);
		}

		Checked();
		m_pDropBox_1->Progress();
		m_pDropBox_2->Progress();

		if (isChecked_1 == true)
			Selected_1();

		if (isChecked_2 == true)
			Selected_2();

		if (GetAsyncKeyState(VK_LBUTTON))
		{
			if (GET_SINGLE(C2DMouse)->IsClicked_Button(m_ReddyButton))
			{
				m_Reddy = true;
			}
		}
		if (m_Reddy)
		{
			m_pTextMgr->SetMaxTime(11.0f);
		}
	}

	if (m_pTextMgr->GetMaxTime() == 0)	GET_SINGLE(CSceneMgr)->SetState(new CLoadingScene);
}

void CSelectScene::Render()
{
	for (int i = 0; i < m_vecBackGround.size(); i++)
	{
		if (m_vecBackGround[i]) m_vecBackGround[i]->Render();
	}
	if(m_Reddy)	m_TimerImage->Render();

	MyDrawFPSByTimeMgr();
	
	m_pTextMgr->Render_time(m_Reddy);
	ChampRender();
	SpellRender();

	if (SpellRender_1) SpellRender_1->Render();
	if (SpellRender_2) SpellRender_2->Render();

	if (m_ReddyButton) m_ReddyButton->Render();

	if(m_Reddy)	m_ReddyState->Render();
}

void CSelectScene::Release()
{
	if (m_Reddy)
	{
		m_mapSpellList.clear();
		m_mapSpellList_2.clear();
		m_mapUI_List.clear();
		delete  m_pDropBox_1;
		delete  m_pDropBox_2;
	}
	delete m_pTextMgr;
}

void CSelectScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}


void CSelectScene::ChampInitialize()
{
	m_vecChamp.push_back(new CChamp("Udyr", "Resource/choen/ChampImage/Udyr/Udyr_Square.png", D3DXVECTOR3(220, 150, 0), D3DXVECTOR3(1.0F, 1.0F, 1.0F)));
	m_vecChamp.push_back(new CChamp("Ezreal", "Resource/choen/ChampImage/Ezreal/Ezreal_Square_0.png", D3DXVECTOR3(290, 150, 0), D3DXVECTOR3(1.0F, 1.0F, 1.0F)));

	m_mapUI_List.insert(make_pair("Champ", &m_vecChamp));

	D3DXVECTOR3 pick = D3DXVECTOR3(60, 258, 0);
	m_vecChampCircle.push_back(new CChamp("Udyr", "Resource/choen/ChampImage/Udyr/Udyr_Square.png", pick, D3DXVECTOR3(1.0F, 1.0F, 1.0F), UI_CHAMPTYPE_DYNAMIC));
	m_vecChampCircle.push_back(new CChamp("Ezreal", "Resource/choen/ChampImage/Ezreal/Ezreal_Square_0.png", pick, D3DXVECTOR3(1.0F, 1.0F, 1.0F), UI_CHAMPTYPE_DYNAMIC));

	for (int i = 0; i < m_vecChampCircle.size(); i++)
		m_vecChampCircle[i]->Initialize();

	m_VecSelectImage.push_back(new CChamp("Udyr", "Resource/choen/ChampImage/Udyr/Udyr_Select.png", D3DXVECTOR3(220, 150, 0), D3DXVECTOR3(1.0f, 1.0f, 1.0f)));
	m_VecSelectImage.push_back(new CChamp("Ezreal", "Resource/choen/ChampImage/Ezreal/Ezreal_Select.png", D3DXVECTOR3(290, 150, 0), D3DXVECTOR3(1.0f, 1.0f, 1.0f)));

	for (int i = 0; i < m_VecSelectImage.size(); i++)
		m_VecSelectImage[i]->Initialize();
}

void CSelectScene::SpellInitialize()
{
	{
		m_mapSpellList.insert(make_pair("cleanse", new CSpell_("Cleanse", "Resource/choen/Spell_Image/1.Cleanse.png",
			D3DXVECTOR3(463, 500, 0),
			D3DXVECTOR3(1.2f, 1.2f, 0.f), cleanse)));

		m_mapSpellList.insert(make_pair("Exhaust", new CSpell_("Exhaust", "Resource/choen/Spell_Image/2.Exhaust.png",
			D3DXVECTOR3(463, 500, 0),
			D3DXVECTOR3(1.2f, 1.2f, 0.f), Exhaust)));

		m_mapSpellList.insert(make_pair("Flash", new CSpell_("Flash", "Resource/choen/Spell_Image/3.Flash.png",
			D3DXVECTOR3(463, 500, 0),
			D3DXVECTOR3(1.2f, 1.2f, 0.f), Flash)));

		m_mapSpellList.insert(make_pair("Ghost", new CSpell_("Ghost", "Resource/choen/Spell_Image/4.Ghost.png",
			D3DXVECTOR3(463, 500, 0),
			D3DXVECTOR3(1.2f, 1.2f, 0.f), Ghost)));

		m_mapSpellList.insert(make_pair("Heal", new CSpell_("Heal", "Resource/choen/Spell_Image/5.Heal.png",
			D3DXVECTOR3(463, 500, 0),
			D3DXVECTOR3(1.2f, 1.2f, 0.f), Heal)));

		m_mapSpellList.insert(make_pair("Smite", new CSpell_("Smite", "Resource/choen/Spell_Image/6.Smite.png",
			D3DXVECTOR3(463, 500, 0),
			D3DXVECTOR3(1.2f, 1.2f, 0.f), Smite)));

		m_mapSpellList.insert(make_pair("Teleport", new CSpell_("Teleport", "Resource/choen/Spell_Image/7.Teleport.png",
			D3DXVECTOR3(463, 500, 0),
			D3DXVECTOR3(1.2f, 1.2f, 0.f), Teleport)));

		m_mapSpellList.insert(make_pair("Ignite", new CSpell_("Ignite", "Resource/choen/Spell_Image/8.Ignite.png",
			D3DXVECTOR3(463, 500, 0),
			D3DXVECTOR3(1.2f, 1.2f, 0.f), Ignite)));

		m_mapSpellList.insert(make_pair("Barrier", new CSpell_("Barrier", "Resource/choen/Spell_Image/9.Barrier.png",
			D3DXVECTOR3(463, 500, 0),
			D3DXVECTOR3(1.2f, 1.2f, 0.f), Barrier)));

		m_mapSpellList_2.insert(make_pair("cleanse", new CSpell_("Cleanse", "Resource/choen/Spell_Image/1.Cleanse.png",
			D3DXVECTOR3(513, 500, 0),
			D3DXVECTOR3(1.2f, 1.2f, 0.f), cleanse)));

		m_mapSpellList_2.insert(make_pair("Exhaust", new CSpell_("Exhaust", "Resource/choen/Spell_Image/2.Exhaust.png",
			D3DXVECTOR3(513, 500, 0),
			D3DXVECTOR3(1.2f, 1.2f, 0.f), Exhaust)));

		m_mapSpellList_2.insert(make_pair("Flash", new CSpell_("Flash", "Resource/choen/Spell_Image/3.Flash.png",
			D3DXVECTOR3(513, 500, 0),
			D3DXVECTOR3(1.2f, 1.2f, 0.f), Flash)));

		m_mapSpellList_2.insert(make_pair("Ghost", new CSpell_("Ghost", "Resource/choen/Spell_Image/4.Ghost.png",
			D3DXVECTOR3(513, 500, 0),
			D3DXVECTOR3(1.2f, 1.2f, 0.f), Ghost)));

		m_mapSpellList_2.insert(make_pair("Heal", new CSpell_("Heal", "Resource/choen/Spell_Image/5.Heal.png",
			D3DXVECTOR3(513, 500, 0),
			D3DXVECTOR3(1.2f, 1.2f, 0.f), Heal)));

		m_mapSpellList_2.insert(make_pair("Smite", new CSpell_("Smite", "Resource/choen/Spell_Image/6.Smite.png",
			D3DXVECTOR3(513, 500, 0),
			D3DXVECTOR3(1.2f, 1.2f, 0.f), Smite)));

		m_mapSpellList_2.insert(make_pair("Teleport", new CSpell_("Teleport", "Resource/choen/Spell_Image/7.Teleport.png",
			D3DXVECTOR3(513, 500, 0),
			D3DXVECTOR3(1.2f, 1.2f, 0.f), Teleport)));

		m_mapSpellList_2.insert(make_pair("Ignite", new CSpell_("Ignite", "Resource/choen/Spell_Image/8.Ignite.png",
			D3DXVECTOR3(513, 500, 0),
			D3DXVECTOR3(1.2f, 1.2f, 0.f), Ignite)));

		m_mapSpellList_2.insert(make_pair("Barrier", new CSpell_("Barrier", "Resource/choen/Spell_Image/9.Barrier.png",
			D3DXVECTOR3(513, 500, 0),
			D3DXVECTOR3(1.2f, 1.2f, 0.f), Barrier)));
	}
	
	for (auto it = m_mapSpellList.begin(); it != m_mapSpellList.end(); it++)		
		it->second->Initialize();

	for (auto it = m_mapSpellList_2.begin(); it != m_mapSpellList_2.end(); it++)		
		it->second->Initialize();

	SpellRender_1 = m_mapSpellList["Flash"];
	SpellRender_2 = m_mapSpellList_2["Ignite"];

	m_pDropBox_1 = new CDropBox(SpellRender_1->GetPosition(), D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	m_pDropBox_2 = new CDropBox(SpellRender_2->GetPosition(), D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	
	m_pDropBox_1->Initialize();
	m_pDropBox_2->Initialize();	

	
}
void CSelectScene::ChampRender()
{
	for (int i = 0; i < m_vecChamp.size(); i++)
	{
		m_vecChamp[i]->Render();
	}
	
	if (Filnal_Champ) Filnal_Champ->Render();
	if (m_bChampCheck)
	{
		for (int i = 0; i < m_VecSelectImage.size(); i++)
		{
			if (Filnal_Champ->GetName() == m_VecSelectImage[i]->GetName())
			{
				m_VecSelectImage[i]->Render();
			}
		}
	}

	if (m_Reddy)
	{
		for (int i = 0; i < m_VecSelectImage.size(); i++)
		{
			m_VecSelectImage[i]->Render();
		}
	}
}

void CSelectScene::SpellRender()
{
	if (SpellRender_1)
	{
		SpellRender_1->Render();
		SpellRender_1->Render(D3DXVECTOR3(127, 257, 0), D3DXVECTOR3(0.8f, 0.8f, 0.8f));
	}

	if (SpellRender_2)
	{
		SpellRender_2->Render();
		SpellRender_2->Render(D3DXVECTOR3(127, 290, 0), D3DXVECTOR3(0.8f, 0.8f, 0.8f));
	}

	if (m_bChecked_1)
	{
		m_pDropBox_1->Render();
		isChecked_1 = true;
		isChecked_2 = false;
	}

	if (m_bChecked_2)
	{
		m_pDropBox_2->Render();
		isChecked_2 = true;
		isChecked_1 = false;
	}
}

bool CSelectScene::Checked()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (SpellRender_1 && SpellRender_2)
		{
			bool inImage_1 = GET_SINGLE(C2DMouse)->IsInImage(SpellRender_1);
			bool inImage_2 = GET_SINGLE(C2DMouse)->IsInImage(SpellRender_2);

			if (inImage_1)
			{
				m_bChecked_1 = !m_bChecked_1;
				m_bChecked_2 = false;
				return true;
			}
			else if (inImage_2)
			{
				m_bChecked_2 = !m_bChecked_2;
				m_bChecked_1 = false;
				return true;
			}
			else
			{
				m_bChecked_1 = false;
				m_bChecked_2 = false;
				return false;
			}
		}
	}
	return false;
}

void CSelectScene::Selected_1()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		string name;
		for (auto it = m_pDropBox_1->GetMap().begin(); it != m_pDropBox_1->GetMap().end(); it++)
		{
			name = GET_SINGLE(C2DMouse)->IsInImage_Spell(it->second);
			if (name != string(""))
				break;
		}

		for (auto jt = m_mapSpellList.begin(); jt != m_mapSpellList.end(); jt++)
		{
			if (name == jt->second->GetName())
			{
				SpellRender_1 = jt->second;
				m_Spell_1Name = SpellRender_1->GetName();
			}
		}
	}
}

void CSelectScene::Selected_2()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		string name;
		for (auto it = m_pDropBox_2->GetMap().begin(); it != m_pDropBox_2->GetMap().end(); it++)
		{
			name = GET_SINGLE(C2DMouse)->IsInImage_Spell(it->second);
			if (name != string(""))
				break;
		}

		for (auto jt = m_mapSpellList_2.begin(); jt != m_mapSpellList_2.end(); jt++)
		{
			if (name == jt->second->GetName())
			{
				SpellRender_2 = jt->second;
				m_Spell_2Name = SpellRender_2->GetName();
			}
		}
	}
}
