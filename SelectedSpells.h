#pragma once
class CUI;
class CSelectedSpells
{
public:
	CSelectedSpells(string SpellName, D3DXVECTOR3 pos);
	~CSelectedSpells();

public:
	void Initialize() ;
	void Render();
	void Release();

private:
	map<string, CUI*>			m_mapSpellList;
	string						m_sSpellName;
	D3DXVECTOR3					m_vPosition;

public:
	D3DXVECTOR3		GetPosition() { return m_vPosition; }
};

