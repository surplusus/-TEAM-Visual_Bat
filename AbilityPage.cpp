#include "BaseInclude.h"
#include "AbilityPage.h"
#include "Image_Loader.h"


CAbilityPage::CAbilityPage()
{
}


CAbilityPage::~CAbilityPage()
{
}

void CAbilityPage::Initialize()
{
	ImageLoad_To_Detailed();
	ImageLoad_To_Control();
	ImageLoad_To_BrainStorm();
	ImageLoad_To_Masic();
	ImageLoad_To_Resolution();
}
void CAbilityPage::Progress()
{
	
}

void CAbilityPage::Render()
{
	ImageRender_To_Detailed();
	ImageRender_To_Control();
	ImageRender_To_BrainStorm();
	ImageRender_To_Masic();
	ImageRender_To_Resolution();	
}

void CAbilityPage::Release()
{
}

void CAbilityPage::ImageLoad_To_Detailed()
{
	CImage_Loader*	Main = new CImage_Loader;
	("Resource/cheon/Runepage/정밀/Main.png");
	Main->Initialize();
	m_mapDetailedRune["Main"] = Main;

	CImage_Loader*	Press_the_Attack_rune = new CImage_Loader;
	("Resource/cheon/Runepage/정밀/Press_the_Attack_rune.png");
	Press_the_Attack_rune->Initialize();
	m_mapDetailedRune["Press_the_Attack_rune"] = Press_the_Attack_rune;
}
void CAbilityPage::ImageLoad_To_Control()
{
	CImage_Loader*	Main = new CImage_Loader;
	("Resource/cheon/Runepage/지배/Main.png");
	Main->Initialize();
	m_mapContolRune["Main"] = Main;
}

void CAbilityPage::ImageLoad_To_BrainStorm()
{
	CImage_Loader*	Main = new CImage_Loader;
	("Resource/cheon/Runepage/영감/Main.png");
	Main->Initialize();
	m_mapBrainStormRune["Main"] = Main;
}

void CAbilityPage::ImageLoad_To_Masic()
{
	CImage_Loader*	Main = new CImage_Loader;
	("Resource/cheon/Runepage/마법/Main.png");
	Main->Initialize();
	m_mapMasicRune["Main"] = Main;
}

void CAbilityPage::ImageLoad_To_Resolution()
{
	CImage_Loader*	Main = new CImage_Loader;
	("Resource/cheon/Runepage/결의/Main.png");
	Main->Initialize();
	m_mapResolutionRune["Main"] = Main;
}

void CAbilityPage::ImageRender_To_Detailed()
{
	m_mapDetailedRune["Main"]->Render(D3DXVECTOR3(200, 200, 0), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	m_mapDetailedRune["Press_the_Attack_rune"]->Render(D3DXVECTOR3(150, 250, 0));
}

void CAbilityPage::ImageRender_To_Control()
{
	m_mapContolRune["Main"]->Render(D3DXVECTOR3(350, 200, 0), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
}

void CAbilityPage::ImageRender_To_BrainStorm()
{
	m_mapBrainStormRune["Main"]->Render(D3DXVECTOR3(500, 200, 0), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
}

void CAbilityPage::ImageRender_To_Masic()
{
	m_mapMasicRune["Main"]->Render(D3DXVECTOR3(650, 200, 0), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
}

void CAbilityPage::ImageRender_To_Resolution()
{
	m_mapResolutionRune["Main"]->Render(D3DXVECTOR3(800, 200, 0), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
}
