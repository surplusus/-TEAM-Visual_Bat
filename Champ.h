#pragma once
#include "UI.h"
#include "Cheon.h"

class CImage_Loader;
class CChamp :
	public CUI
{
public:
	CChamp(string name, string FileName, D3DXVECTOR3 pos, D3DXVECTOR3 vScale, UI_CHAMPTYPE eType = UI_CHAMPTYPE_STATIC);
	~CChamp();
public:
	void Initialize() override;
	int Progress() override;
	void Render() override;
	void Render(D3DXVECTOR3 pos) override;
private:
	UI_CHAMPTYPE m_eType;
private:
	bool bClicked;

private:
	CImage_Loader*				m_ImageLoader;
	
private:
	bool CheckMouse();
};

