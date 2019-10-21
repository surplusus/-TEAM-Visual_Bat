#pragma once
#include "UI.h"
#include "DropBox.h"

class CImage_Loader;
class CSpell_ :
	public CUI
{
public:
	CSpell_(string name, string FileName, D3DXVECTOR3 pos,D3DXVECTOR3 vScale, UI_SPELLTYPE etype);
	~CSpell_();
public:
	void Initialize() override;
	int Progress() override;
	void Render() override;
	void Render(D3DXVECTOR3 pos) override;
	void Release() override;

private:
	UI_SPELLTYPE				m_eType;
public:
	UI_SPELLTYPE GetType() { return m_eType; }

private:
	bool						m_bClicked;

	CDropBox*					m_dropbox;

};

