#include "BaseInclude.h"
#include "SelectedSpells.h"
#include "UI.h"
#include "Spell_.h"
#include "Image_Loader.h"

CSelectedSpells::CSelectedSpells(string SpellName, D3DXVECTOR3 pos)
	:m_sSpellName(SpellName), m_vPosition(pos)
{
}


CSelectedSpells::~CSelectedSpells()
{
}

void CSelectedSpells::Initialize()
{
	{
		m_mapSpellList.insert(make_pair("cleanse", new CSpell_("Cleanse", "Resource/choen/Spell_Image/1.Cleanse.png",
			m_vPosition,
			D3DXVECTOR3(0.8f, 0.8f, 0.f), cleanse)));

		m_mapSpellList.insert(make_pair("Exhaust", new CSpell_("Exhaust", "Resource/choen/Spell_Image/2.Exhaust.png",
			m_vPosition,
			D3DXVECTOR3(0.8f, 0.8f, 0.f), Exhaust)));

		m_mapSpellList.insert(make_pair("Flash", new CSpell_("Flash", "Resource/choen/Spell_Image/3.Flash.png",
			m_vPosition,
			D3DXVECTOR3(0.8f, 0.8f, 0.f), Flash)));

		m_mapSpellList.insert(make_pair("Ghost", new CSpell_("Ghost", "Resource/choen/Spell_Image/4.Ghost.png",
			m_vPosition,
			D3DXVECTOR3(0.8f, 0.8f, 0.f), Ghost)));

		m_mapSpellList.insert(make_pair("Heal", new CSpell_("Heal", "Resource/choen/Spell_Image/5.Heal.png",
			m_vPosition,
			D3DXVECTOR3(0.8f, 0.8f, 0.f), Heal)));

		m_mapSpellList.insert(make_pair("Smite", new CSpell_("Smite", "Resource/choen/Spell_Image/6.Smite.png",
			m_vPosition,
			D3DXVECTOR3(0.8f, 0.8f, 0.f), Smite)));

		m_mapSpellList.insert(make_pair("Teleport", new CSpell_("Teleport", "Resource/choen/Spell_Image/7.Teleport.png",
			m_vPosition,
			D3DXVECTOR3(0.8f, 0.8f, 0.f), Teleport)));

		m_mapSpellList.insert(make_pair("Ignite", new CSpell_("Ignite", "Resource/choen/Spell_Image/8.Ignite.png",
			m_vPosition,
			D3DXVECTOR3(0.8f, 0.8f, 0.f), Ignite)));

		m_mapSpellList.insert(make_pair("Barrier", new CSpell_("Barrier", "Resource/choen/Spell_Image/9.Barrier.png",
			m_vPosition,
			D3DXVECTOR3(0.8f, 0.8f, 0.f), Barrier)));

	}
	for (auto it = m_mapSpellList.begin(); it != m_mapSpellList.end(); it++)
		it->second->Initialize();
}

void CSelectedSpells::Render()
{
	for (auto it = m_mapSpellList.begin(); it != m_mapSpellList.end(); it++)
	{
		if (m_sSpellName == it->second->GetName())
		{
			it->second->Render();
		}
	}
}

void CSelectedSpells::Release()
{
}
