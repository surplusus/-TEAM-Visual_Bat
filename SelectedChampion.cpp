#include "BaseInclude.h"
#include "SelectedChampion.h"
#include "Image_Loader.h"
#include "UI.h"
#include "Champ.h"
#include "Spell_.h"

CSelectedChampion::CSelectedChampion()
{
}


CSelectedChampion::~CSelectedChampion()
{
}

CSelectedChampion::CSelectedChampion(D3DXVECTOR3 color)
	: m_vColor(color), m_pLoadingBoarder_blue(NULL), m_pLoadingBoarder_red(NULL), m_pEnemy(NULL)
{
}

void CSelectedChampion::Initialize()
{
	ChampInitialize();
	SpellInitialize();
}

int CSelectedChampion::Progress()
{
	return 0;
}

void CSelectedChampion::Render()
{
	for (auto it = m_mapChampList.begin(); it != m_mapChampList.end(); it++)
	{
		if (g_ChampName == it->second->GetName())
		{
			it->second->Render();
		}

	}
	m_pLoadingBoarder_blue->Render();


	if(m_pEnemy)	m_pEnemy->Render();
	m_pLoadingBoarder_red->Render();
}

void CSelectedChampion::Release()
{
	m_pLoadingBoarder_blue->Release();
	m_pLoadingBoarder_red ->Release();
}

void CSelectedChampion::Render(D3DXVECTOR3 pos)
{
}

void CSelectedChampion::ChampInitialize()
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

	vector<CUI*> vecChamp;
	vecChamp.push_back(m_mapChampList["Enemy_Amumu"]);
	vecChamp.push_back(m_mapChampList["Enemy_Ezreal"]);
	m_pEnemy = vecChamp[rand() % vecChamp.size()];
}

void CSelectedChampion::SpellInitialize()
{
	/*m_mapSpellList_1.insert(make_pair("cleanse", new CSpell_("cleanse ", "Resource/choen/Spell_Image/1.Cleanse.png", D3DXVECTOR3(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), cleanse)));
	m_mapSpellList_1.insert(make_pair("cleanse", new CSpell_("Exhaust ", "Resource/choen/Spell_Image/2.Exhaust.png", D3DXVECTOR3(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Exhaust)));
	m_mapSpellList_1.insert(make_pair("cleanse", new CSpell_("Flash	", "Resource/choen/Spell_Image/3.Flash.png", D3DXVECTOR3(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Flash)));
	m_mapSpellList_1.insert(make_pair("cleanse", new CSpell_("Ghost	", "Resource/choen/Spell_Image/4.Ghost.png", D3DXVECTOR3(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Ghost)));
	m_mapSpellList_1.insert(make_pair("cleanse", new CSpell_("Heal	", "Resource/choen/Spell_Image/5.Heal.png", D3DXVECTOR3(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Heal)));
	m_mapSpellList_1.insert(make_pair("cleanse", new CSpell_("Smite	", "Resource/choen/Spell_Image/6.Smite.png", D3DXVECTOR3(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Smite)));
	m_mapSpellList_1.insert(make_pair("cleanse", new CSpell_("Teleport", "Resource/choen/Spell_Image/7.Teleport.png", D3DXVECTOR3(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Teleport)));
	m_mapSpellList_1.insert(make_pair("cleanse", new CSpell_("Ignite	", "Resource/choen/Spell_Image/8.Ignite.png", D3DXVECTOR3(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Ignite)));
	m_mapSpellList_1.insert(make_pair("cleanse", new CSpell_("Barrier	", "Resource/choen/Spell_Image/9.Barrier.png", D3DXVECTOR3(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Barrier)));

	m_mapSpellList_2.insert(make_pair("cleanse", new CSpell_("cleanse ", "Resource/choen/Spell_Image/1.Cleanse.png", D3DXVECTOR3(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), cleanse)));
	m_mapSpellList_2.insert(make_pair("cleanse", new CSpell_("Exhaust ", "Resource/choen/Spell_Image/2.Exhaust.png", D3DXVECTOR3(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Exhaust)));
	m_mapSpellList_2.insert(make_pair("cleanse", new CSpell_("Flash	", "Resource/choen/Spell_Image/3.Flash.png", D3DXVECTOR3(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Flash)));
	m_mapSpellList_2.insert(make_pair("cleanse", new CSpell_("Ghost	", "Resource/choen/Spell_Image/4.Ghost.png", D3DXVECTOR3(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Ghost)));
	m_mapSpellList_2.insert(make_pair("cleanse", new CSpell_("Heal	", "Resource/choen/Spell_Image/5.Heal.png", D3DXVECTOR3(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Heal)));
	m_mapSpellList_2.insert(make_pair("cleanse", new CSpell_("Smite	", "Resource/choen/Spell_Image/6.Smite.png", D3DXVECTOR3(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Smite)));
	m_mapSpellList_2.insert(make_pair("cleanse", new CSpell_("Teleport", "Resource/choen/Spell_Image/7.Teleport.png", D3DXVECTOR3(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Teleport)));
	m_mapSpellList_2.insert(make_pair("cleanse", new CSpell_("Ignite	", "Resource/choen/Spell_Image/8.Ignite.png", D3DXVECTOR3(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Ignite)));
	m_mapSpellList_2.insert(make_pair("cleanse", new CSpell_("Barrier	", "Resource/choen/Spell_Image/9.Barrier.png", D3DXVECTOR3(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), Barrier)));

	for (auto it = m_mapSpellList_1.begin(); it != m_mapSpellList_1.end(); it++)
	{
		it->second->Initialize();
	}

	for (auto it = m_mapSpellList_2.begin(); it != m_mapSpellList_2.end(); it++)
	{
		it->second->Initialize();
	}*/
}