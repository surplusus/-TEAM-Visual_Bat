#pragma once
#include "UI.h"

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
	void Release() override;
private:
	UI_CHAMPTYPE m_eType;
private:
	bool bClicked;
	
private:
	bool CheckMouse();

public:
	bool GetClicked() { return bClicked; }
	void SetClicked(bool click) { bClicked = click; }
};