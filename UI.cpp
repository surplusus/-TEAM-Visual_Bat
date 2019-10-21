#include "BaseInclude.h"
#include "UI.h"
#include "Image_Loader.h"
CUI::CUI()
	:m_name("")
	, m_vPosition(0,0,0)
	, m_FileName("")
	, m_vScale(0,0,0) 
	, m_ImageLoader(NULL)
{
	m_Rect = { 0,0,0,0 };
}


CUI::~CUI()
{
}

RECT CUI::GetRect()
{
	float Width = m_ImageLoader->GetImageInfo().Width;
	float Height = m_ImageLoader->GetImageInfo().Height;
	SetCenterPos();
	RECT rc =
	{
		m_vCenter.x - (Width) / 2,
		m_vCenter.y - (Height) / 2,
		m_vCenter.x + (Width)  / 2,
		m_vCenter.y + (Height) / 2
	};
	return rc;
}

string CUI::GetName()
{
	return m_name;
}

void CUI::SetCenterPos()
{
	float Width = m_ImageLoader->GetImageInfo().Width;
	float Height = m_ImageLoader->GetImageInfo().Height;
	m_vCenter.x = m_vPosition.x + (Width) / 2;	
	m_vCenter.y = m_vPosition.y + (Height) / 2;	
	m_vCenter.z = 0;
	static bool ckeck = true;
	
	if (ckeck) {
	ckeck = false;
	}
}
