#include "BaseInclude.h"
#include "SelectScene.h"
#include "C2DMouse.h"
#include "AbilityPage.h"
#include "Image_Loader.h"
#include "Champ.h"
#include "Spell_.h"
#include "Text.h"
#include "SceneMgr.h"
#include "LoadingScene.h"
#include "DropBox.h"

static CUI* temp = NULL;
static CUI* SpellRender_1 = NULL;
static CUI* SpellRender_2 = NULL;
string g_ChampName;
string g_Spell_1;
string g_Spell_2;
CSelectScene::CSelectScene()
	:m_p2Dmouse(NULL)
	, m_pChamp(NULL)
	, m_pSpell(NULL)
	, m_pSpellRender_1(NULL)
	, m_pSpellRender_2(NULL)
	, m_pDorpBox_1(NULL)
	, m_pDorpBox_2(NULL)
	, m_bChecked_1(false)
	, m_bChecked_2(false)
{
	
	
	
}


CSelectScene::~CSelectScene()
{
}

HRESULT CSelectScene::Initialize()
{	
	m_vecBackGround.push_back( new CImage_Loader("Resource/choen/Select/BackGround_.jpg", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1.0f, 1.0f, 0)));
	m_vecBackGround.push_back(new CImage_Loader("Resource/choen/Select/Pick.png", D3DXVECTOR3(0, 250, 0), D3DXVECTOR3(1.0f, 1.0f, 0)));

	
	for (int i = 0; i < m_vecBackGround.size(); i++)
	{
		if (m_vecBackGround[i])
		{
			m_vecBackGround[i]->Initialize();
		}
	}

	GET_SINGLE(CText)->Initialize();
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
	if (m_pDorpBox_1) m_pDorpBox_1->Progress();
	if (m_pDorpBox_2) m_pDorpBox_2->Progress();
		
	//if(GetAsyncKeyState(VK_LBUTTON))	Checked();

	IsSelected();

	
	//Scene ÀüÈ¯
	/*if (GET_SINGLE(CText)->GetTimer() == "0")
	{
		GET_SINGLE(CSceneMgr)->SetState(new CLoadingScene);
	}*/
	if(GetAsyncKeyState(VK_ESCAPE))GET_SINGLE(CSceneMgr)->SetState(new CLoadingScene);

}

void CSelectScene::Render()
{
	for (int i = 0; i < m_vecBackGround.size(); i++)
	{
		if (m_vecBackGround[i]) m_vecBackGround[i]->Render();
	}

	MyDrawFPSByTimeMgr();
	GET_SINGLE(CText)->Render_time();
	ChampRender();
	SpellRender();

	if (m_bChecked_1) m_pDorpBox_1->Render();
	if (m_bChecked_2) m_pDorpBox_2->Render();
}

void CSelectScene::Release()
{

}

void CSelectScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}


void CSelectScene::ChampInitialize()
{
	m_vecChamp.push_back(new CChamp("Amumu", "Resource/choen/ChampImage/Amumu/Amumu_Square_0.png", D3DXVECTOR3(220, 150, 0), D3DXVECTOR3(1.0f, 1.0f, 1.0f)));
	m_vecChamp.push_back(new CChamp("Ezreal", "Resource/choen/ChampImage/Ezreal/Ezreal_Square_0.png", D3DXVECTOR3(290, 150, 0), D3DXVECTOR3(1.0f, 1.0f, 1.0f)));

	m_mapUI_List.insert(make_pair("Champ", &m_vecChamp));

	D3DXVECTOR3 pick = D3DXVECTOR3(60, 258, 0);
	m_vecChampCircle.push_back(new CChamp("Amumu", "Resource/choen/ChampImage/Amumu/Amumu_Square_0.png",	pick, D3DXVECTOR3(1.0f, 1.0f, 1.0f), UI_CHAMPTYPE_DYNAMIC));
	m_vecChampCircle.push_back(new CChamp("Ezreal", "Resource/choen/ChampImage/Ezreal/Ezreal_Square_0.png", pick, D3DXVECTOR3(1.0f, 1.0f, 1.0f), UI_CHAMPTYPE_DYNAMIC));

	for (int i = 0; i < m_vecChampCircle.size(); i++)
		m_vecChampCircle[i]->Initialize();

	
}

void CSelectScene::SpellInitialize()
{
	m_pDorpBox_1 = new CDropBox(D3DXVECTOR3(430, 170, 0), D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	m_pDorpBox_1->Initialize();

	m_pDorpBox_2 = new CDropBox(D3DXVECTOR3(500, 170, 0), D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	m_pDorpBox_2->Initialize();

	SpellRender_1 = m_pDorpBox_1->GetVecSpells()[rand() % m_pDorpBox_1->GetVecSpells().size()];
	SpellRender_2 = m_pDorpBox_2->GetVecSpells()[rand() % m_pDorpBox_2->GetVecSpells().size()];
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
	if (SpellRender_1)
	{
		SpellRender_1->Render(D3DXVECTOR3(460, 500, 0));
		SpellRender_1->Render(D3DXVECTOR3(20, 300, 0));
		Rectangle(GetDC(g_hWnd), SpellRender_1->GetRect().left, SpellRender_1->GetRect().top, SpellRender_1->GetRect().right, SpellRender_1->GetRect().bottom);
	}

	if (SpellRender_2)
	{
		SpellRender_2->Render(D3DXVECTOR3(503, 500, 0));
		SpellRender_2->Render(D3DXVECTOR3(20, 350, 0));
		Rectangle(GetDC(g_hWnd), SpellRender_2->GetRect().left, SpellRender_2->GetRect().top, SpellRender_2->GetRect().right, SpellRender_2->GetRect().bottom);
	}
}

bool CSelectScene::Checked()
{
	if (SpellRender_1)
	{
		if (m_pDorpBox_1)
		{
			for (int i = 0; i < m_pDorpBox_1->GetVecSpells().size(); i++)
			{
				if (GET_SINGLE(C2DMouse)->IsInImage(SpellRender_1))
				{
					m_bChecked_1 = true;
					return true;
				}
				else
				{
					m_bChecked_1 = false;
				}
			}
		}
	}

	if (SpellRender_2)
	{
		if (m_pDorpBox_2)
		{
			for (int i = 0; i < m_pDorpBox_2->GetVecSpells().size(); i++)
			{
				if (GET_SINGLE(C2DMouse)->IsInImage(SpellRender_2))
				{
					m_bChecked_2 = true;
					return true;
				}
				else
				{
					m_bChecked_2 = false;
				}
			}
		}
	}
	return false;
}

void CSelectScene::IsSelected()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (m_pSpellRender_1)
		{
			if (m_pDorpBox_1)
			{
				for (int i = 0; i < m_pDorpBox_1->GetVecSpells().size(); i++)
				{
					if (GET_SINGLE(C2DMouse)->IsInImage_(m_pDorpBox_1->GetVecSpells()[i]))
					{
						SpellRender_1 = GET_SINGLE(C2DMouse)->IsInImage_(m_pDorpBox_1->GetVecSpells()[i]);
					}
				}
			}
		}
	}

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (m_pSpellRender_2)
		{
			if (m_pDorpBox_2)
			{
				for (int i = 0; i < m_pDorpBox_2->GetVecSpells().size(); i++)
				{
					if (GET_SINGLE(C2DMouse)->IsInImage_(m_pDorpBox_2->GetVecSpells()[i]))
					{
						SpellRender_2 = GET_SINGLE(C2DMouse)->IsInImage_(m_pDorpBox_2->GetVecSpells()[i]);
					}
				}
			}
		}
	}
}

