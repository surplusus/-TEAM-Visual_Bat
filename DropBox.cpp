#include "BaseInclude.h"
#include "DropBox.h"
#include "Spell_.h"
#include "Image_Loader.h"
#include "C2DMouse.h"
#include "UI.h"


CDropBox::CDropBox(D3DXVECTOR3 pos, D3DXVECTOR3 scale) : m_vPosition(pos), m_scale(scale)
, m_pImageLoader(NULL)
, m_pSelect1(NULL)
, m_pSelect2(NULL)
{
}


CDropBox::~CDropBox()
{
}

void CDropBox::Initialize()
{
	/*
	480, 500 / 530, 500/ 575, 500/ 625, 500
	480, 570 / 530, 570/ 575/ 570/ 625, 570
	480, 640
	*/
	D3DXVECTOR3 position = D3DXVECTOR3(464, 330, 0);
	m_pImageLoader = new CImage_Loader("Resource/choen/Spell_Image/dropBox.png" , position, m_scale);
	m_pImageLoader->Initialize();

	m_mapSpellList.insert(make_pair("cleanse",  new CSpell_("Cleanse",  "Resource/choen/Spell_Image/1.Cleanse.png",		D3DXVECTOR3(479.5f, 497.05f, 0),    D3DXVECTOR3(0.555f, 0.578f, 0.f))));
	m_mapSpellList.insert(make_pair("Exhaust",  new CSpell_("Exhaust",  "Resource/choen/Spell_Image/2.Exhaust.png",		D3DXVECTOR3(521.0f, 497.05f, 0),	D3DXVECTOR3(0.555f, 0.578f, 0.f))));
	m_mapSpellList.insert(make_pair("Flash",    new CSpell_("Flash",	"Resource/choen/Spell_Image/3.Flash.png",		D3DXVECTOR3(563.0f, 497.05f, 0),	D3DXVECTOR3(0.555f, 0.578f, 0.f))));
	m_mapSpellList.insert(make_pair("Ghost",    new CSpell_("Ghost",	"Resource/choen/Spell_Image/4.Ghost.png",		D3DXVECTOR3(605.0f, 497.05f, 0),	D3DXVECTOR3(0.555f, 0.578f, 0.f))));
	m_mapSpellList.insert(make_pair("Heal",     new CSpell_("Heal",	    "Resource/choen/Spell_Image/5.Heal.png",		D3DXVECTOR3(479.5f, 538.55f, 0),	D3DXVECTOR3(0.555f, 0.578f, 0.f))));
	m_mapSpellList.insert(make_pair("Smite",    new CSpell_("Smite",	"Resource/choen/Spell_Image/6.Smite.png",		D3DXVECTOR3(521.0f, 538.55f, 0),	D3DXVECTOR3(0.555f, 0.578f, 0.f))));
	m_mapSpellList.insert(make_pair("Teleport", new CSpell_("Teleport", "Resource/choen/Spell_Image/7.Teleport.png",	D3DXVECTOR3(563.0f, 538.55f, 0),    D3DXVECTOR3(0.555f, 0.578f, 0.f))));
	m_mapSpellList.insert(make_pair("Ignite",   new CSpell_("Ignite",   "Resource/choen/Spell_Image/8.Ignite.png",		D3DXVECTOR3(605.0f, 538.55f, 0),    D3DXVECTOR3(0.555f, 0.578f, 0.f))));
	m_mapSpellList.insert(make_pair("Barrier",  new CSpell_("Barrier",  "Resource/choen/Spell_Image/9.Barrier.png",		D3DXVECTOR3(479.5f, 582.05f, 0),	D3DXVECTOR3(0.555f, 0.578f, 0.f))));

	for (auto it = m_mapSpellList.begin(); it != m_mapSpellList.end(); it++)
	{
		it->second->Initialize();
	}
}

void CDropBox::Progress()
{

}

void CDropBox::Render()
{
	m_pImageLoader->Render();
	for (auto it = m_mapSpellList.begin(); it != m_mapSpellList.end(); it++)
		it->second->Render();
}

void CDropBox::Release()
{
}
