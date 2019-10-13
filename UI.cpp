#include "BaseInclude.h"
#include "UI.h"
#include "Image_Loader.h"

CUI::CUI()
	:m_name("")
	, m_vPosition(0,0,0)
	, m_FileName("")
	, m_vScale(0,0,0) 
{
	m_Rect = { 0,0,0,0 };

}


CUI::~CUI()
{
}