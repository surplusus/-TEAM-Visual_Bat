#include "BaseInclude.h"
#include "SelectedChamp.h"
#include "Image_Loader.h"


SelectedChamp::SelectedChamp()
	:m_Loader(NULL)
{
}


SelectedChamp::~SelectedChamp()
{
}

void SelectedChamp::Initialize()
{
	m_Loader = new CImage_Loader()
}

void SelectedChamp::Progress()
{
}

void SelectedChamp::Render()
{
}

void SelectedChamp::Release()
{
}
