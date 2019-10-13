#pragma once
#include "UI.h"
#include "Cheon.h"

class CImage_Loader;
class CSpell_ :
	public CUI
{
public:
	CSpell_(string name, string FileName, D3DXVECTOR3 pos,D3DXVECTOR3 vScale);
	~CSpell_();
public:
	void Initialize() override;
	int Progress() override;
	void Render() override;
	void Render(D3DXVECTOR3 pos) override;
	

private:
	UI_SPELLTYPE		m_spelltype;
	bool				bClicked;

public:
	bool Checked();
	
};

