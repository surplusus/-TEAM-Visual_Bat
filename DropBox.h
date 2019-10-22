#pragma once
class CImage_Loader;
class CUI;
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
	map<string, CImage_Loader*>					m_mapSpellList;
	
	CImage_Loader*						m_pImageLoader;
	D3DXVECTOR3							m_vPosition;
	D3DXVECTOR3							m_scale;
	vector<CImage_Loader*>						m_vecSpells;
	

private:
	UI_SPELLTYPE						m_eType;

	bool Checked();
public:
	vector<CImage_Loader*>	GetVecSpells() { return m_vecSpells; }
};

