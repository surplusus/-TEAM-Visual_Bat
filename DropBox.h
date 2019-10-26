#pragma once
class CImage_Loader;
class CUI;
class CTextMgr;
class CDropBox
{
public:
	CDropBox(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	~CDropBox();
public:
	void Initialize();
	void Progress();
	void Render();
	void Release();
private:
	map<string, CUI*>					m_mapSpellList;
	CImage_Loader*						m_pImageLoader;
	D3DXVECTOR3							m_vPosition;
	D3DXVECTOR3							m_scale;
	vector<CUI*>						m_vecSpells;
	

private:
	UI_SPELLTYPE						m_eType;

	bool Checked();
public:
	vector<CUI*>	GetVecSpells() { return m_vecSpells; }
	map<string, CUI*>& GetMap() { return m_mapSpellList; }

private:
	CTextMgr*						  m_pTextMgr;
};

