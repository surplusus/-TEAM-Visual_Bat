#include "BaseInclude.h"
#include "SelectedChampion.h"
#include "SceneMgr.h"
#include "Image_Loader.h"
#include "UI.h"
#include "Champ.h"
#include "Spell_.h"
#include "SelectedSpells.h"


CSelectedChampion::CSelectedChampion(string ChampName)
	: m_pLoadingBoarder_blue(NULL), m_pLoadingBoarder_red(NULL), m_pEnemy(NULL), m_ChampName(ChampName)
{
}

CSelectedChampion::~CSelectedChampion()
{
}

void CSelectedChampion::Initialize()
{
	m_pLoadingBoarder_blue = new CImage_Loader("Resource/choen/Loading/ChallengerBoarder.png", D3DXVECTOR3(400, 0, 0), D3DXVECTOR3(0.7f, 0.7f, 0));
	m_pLoadingBoarder_red = new CImage_Loader("Resource/choen/Loading/ChallengerBoarder.png", D3DXVECTOR3(400, 410, 0), D3DXVECTOR3(0.7f, 0.7f, 0));
	m_pLoadingBoarder_blue->Initialize();
	m_pLoadingBoarder_red->Initialize();

	m_mapChampList.insert(make_pair(("Friendly_Amumu"), new CChamp("Amumu", "Resource/choen/ChampImage/Amumu/AmumuLoadScreen.dds", D3DXVECTOR3(410, 5, 0), D3DXVECTOR3(0.55f, 0.5f, 1.0f))));
	m_mapChampList.insert(make_pair(("Friendly_Ezreal"), new CChamp("Ezreal", "Resource/choen/ChampImage/Ezreal/EzrealLoadScreen.dds", D3DXVECTOR3(410, 5, 0), D3DXVECTOR3(0.55f, 0.5f, 1.0f))));

	m_mapChampList.insert(make_pair(("Enemy_Amumu"), new CChamp("Amumu", "Resource/choen/ChampImage/Ezreal/EzrealLoadScreen.dds", D3DXVECTOR3(410, 415, 0), D3DXVECTOR3(0.55f, 0.5f, 1.0f))));
	m_mapChampList.insert(make_pair(("Enemy_Ezreal"), new CChamp("Ezreal", "Resource/choen/ChampImage/Amumu/AmumuLoadScreen.dds", D3DXVECTOR3(410, 415, 0), D3DXVECTOR3(0.55f, 0.5f, 1.0f))));


	for (auto it = m_mapChampList.begin(); it != m_mapChampList.end(); it++)
	{
		it->second->Initialize();
	}
	m_pSpell_1 = new CSelectedSpells(GET_SINGLE(CSceneMgr)->GetSceneMediator()->SetSelectedSpell_1Name(), 
		D3DXVECTOR3(m_pLoadingBoarder_blue->GetPosition().x + m_pLoadingBoarder_blue->GetWidth() / 3 + 8 , m_pLoadingBoarder_blue->GetPosition().y + m_pLoadingBoarder_blue->GetHeight() * 0.8f + 26, 0));
	m_pSpell_1->Initialize();
	
	m_pSpell_2 = new CSelectedSpells(GET_SINGLE(CSceneMgr)->GetSceneMediator()->SetSelectedSpell_2Name(), 
		D3DXVECTOR3(m_pSpell_1->GetPosition().x + 31, m_pSpell_1->GetPosition().y, 0)
	);
	m_pSpell_2->Initialize();

	vector<CUI*> vecChamp;
	vecChamp.push_back(m_mapChampList["Enemy_Amumu"]);
	vecChamp.push_back(m_mapChampList["Enemy_Ezreal"]);
	m_pEnemy = vecChamp[rand() % vecChamp.size()];
}

void CSelectedChampion::Render()
{
	for (auto it = m_mapChampList.begin(); it != m_mapChampList.end(); it++)
	{
		if (m_ChampName == it->second->GetName())
		{
			it->second->Render();
		}

	}
	m_pLoadingBoarder_blue->Render();


	if(m_pEnemy)	m_pEnemy->Render();
	m_pLoadingBoarder_red->Render();

	m_pSpell_1->Render();
	m_pSpell_2->Render();
}

void CSelectedChampion::Release()
{
	m_pLoadingBoarder_blue->Release();
	m_pLoadingBoarder_red ->Release();
	delete m_pEnemy;
	m_pEnemy = NULL;
}