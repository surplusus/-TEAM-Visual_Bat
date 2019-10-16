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
	map<string, CUI*>					m_mapSpellList;
	CImage_Loader*						m_pImageLoader;
	D3DXVECTOR3							m_vPosition;
	D3DXVECTOR3							m_scale;
	CUI*								m_pSelect1;
	CUI*								m_pSelect2;

private:
	UI_SPELLTYPE						m_eType;

	bool Checked();
};

