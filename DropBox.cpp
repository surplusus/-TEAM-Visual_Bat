#include "BaseInclude.h"
#include "DropBox.h"
#include "Spell_.h"
#include "Image_Loader.h"
#include "C2DMouse.h"
#include "UI.h"
#include "Spell_.h"
#include "TextMgr.h"


CDropBox::CDropBox(D3DXVECTOR3 pos, D3DXVECTOR3 scale) : m_vPosition(pos), m_scale(scale)
, m_pImageLoader(NULL)
{
	GET_SINGLE(CTextMgr)->SetPosition(m_vPosition);
}


CDropBox::~CDropBox()
{
}

// D3DXVECTOR3(WINSIZEX/2 - 30.5f, WINSIZEY/2 + 99.5f, 0)
void CDropBox::Initialize()
{
	D3DXVECTOR3 position = D3DXVECTOR3(m_vPosition.x - 50 , m_vPosition.y - 320, 0);
	m_pImageLoader = new CImage_Loader("Resource/choen/Spell_Image/dropBox.png" , position, m_scale);
	m_pImageLoader->Initialize();

	m_mapSpellList.insert(make_pair("cleanse", new CSpell_("Cleanse", "Resource/choen/Spell_Image/1.Cleanse.png",
		D3DXVECTOR3(m_pImageLoader->GetPosition().x + 17, m_pImageLoader->GetPosition().y + 169, 0),
		D3DXVECTOR3(1.0f, 1.0f, 0.f), cleanse)));

	m_mapSpellList.insert(make_pair("Exhaust", new CSpell_("Exhaust", "Resource/choen/Spell_Image/2.Exhaust.png",
		D3DXVECTOR3(m_mapSpellList["cleanse"]->GetPosition().x + 42.0f, m_mapSpellList["cleanse"]->GetPosition().y, 0),
		D3DXVECTOR3(1.0f, 1.0f, 0.f), Exhaust)));

	m_mapSpellList.insert(make_pair("Flash", new CSpell_("Flash", "Resource/choen/Spell_Image/3.Flash.png",
		D3DXVECTOR3(m_mapSpellList["Exhaust"]->GetPosition().x + 42.0f, m_mapSpellList["Exhaust"]->GetPosition().y, 0),
		D3DXVECTOR3(1.0f, 1.0f, 0.f), Flash)));

	m_mapSpellList.insert(make_pair("Ghost", new CSpell_("Ghost", "Resource/choen/Spell_Image/4.Ghost.png",
		D3DXVECTOR3(m_mapSpellList["Flash"]->GetPosition().x + 42.0f, m_mapSpellList["Flash"]->GetPosition().y, 0),
		D3DXVECTOR3(1.0f, 1.0f, 0.f), Ghost)));

	m_mapSpellList.insert(make_pair("Heal", new CSpell_("Heal", "Resource/choen/Spell_Image/5.Heal.png",
		D3DXVECTOR3(m_mapSpellList["cleanse"]->GetPosition().x, m_mapSpellList["cleanse"]->GetPosition().y + 42.0f, 0),
		D3DXVECTOR3(1.0f, 1.0f, 0.f), Heal)));

	m_mapSpellList.insert(make_pair("Smite", new CSpell_("Smite", "Resource/choen/Spell_Image/6.Smite.png",
		D3DXVECTOR3(m_mapSpellList["cleanse"]->GetPosition().x + 42.0f, m_mapSpellList["cleanse"]->GetPosition().y + 42.0f, 0),
		D3DXVECTOR3(1.0f, 1.0f, 0.f), Smite)));

	m_mapSpellList.insert(make_pair("Teleport", new CSpell_("Teleport", "Resource/choen/Spell_Image/7.Teleport.png",
		D3DXVECTOR3(m_mapSpellList["Smite"]->GetPosition().x + 42.0f, m_mapSpellList["cleanse"]->GetPosition().y + 42.0f, 0),
		D3DXVECTOR3(1.0f, 1.0f, 0.f), Teleport)));

	m_mapSpellList.insert(make_pair("Ignite", new CSpell_("Ignite", "Resource/choen/Spell_Image/8.Ignite.png",
		D3DXVECTOR3(m_mapSpellList["Teleport"]->GetPosition().x + 42.0f, m_mapSpellList["cleanse"]->GetPosition().y + 42.0f, 0),
		D3DXVECTOR3(1.0f, 1.0f, 0.f), Ignite)));

	m_mapSpellList.insert(make_pair("Barrier", new CSpell_("Barrier", "Resource/choen/Spell_Image/9.Barrier.png",
		D3DXVECTOR3(m_mapSpellList["cleanse"]->GetPosition().x, m_mapSpellList["Ignite"]->GetPosition().y + 44.0f, 0),
		D3DXVECTOR3(1.0f, 1.0f, 0.f), Barrier)));



	for (auto it = m_mapSpellList.begin(); it != m_mapSpellList.end(); it++)
	{
		it->second->Initialize();
		m_vecSpells.push_back(it->second);
	}
	GET_SINGLE(CTextMgr)->Initialize();
}

void CDropBox::Progress()
{
	if (Checked() == true)
	{
		for (auto it = m_mapSpellList.begin(); it != m_mapSpellList.end(); it++)
		{
			if (GET_SINGLE(C2DMouse)->Is_PointInSpellImage(it->second))		
				m_eType = GET_SINGLE(C2DMouse)->Is_PointInSpellImage(it->second);
		}
	}
}

void CDropBox::Render()
{
	m_pImageLoader->Render();
	for (auto it = m_mapSpellList.begin(); it != m_mapSpellList.end(); it++)
		it->second->Render();



	/*RECT rt = {1050, 250, 0, 0 };
	RECT rc = {1050, 220, 0, 0 };*/
	RECT rt = { m_vPosition.x + 550, m_vPosition.y - 250, 0, 0 };
	RECT rc = { m_vPosition.x + 550, m_vPosition.y - 280, 0, 0 };
	GET_SINGLE(CTextMgr)->Render(m_eType);
}

void CDropBox::Release()
{
	m_pImageLoader->Release();
}

bool CDropBox::Checked()
{
	for (auto it = m_mapSpellList.begin(); it != m_mapSpellList.end(); it++)
	{
		if (GET_SINGLE(C2DMouse)->Is_PointInSpellImage(it->second))
		{
			return true;
		}
	}
	return false;
}