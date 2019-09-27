#include "BaseInclude.h"
#include "Bound.h"


CBound::CBound()
	:m_pMesh(NULL)
{
}


CBound::~CBound()
{
	Release();
}

void CBound::Bound_Render()
{
	m_pMesh->DrawSubset(0);
}

void CBound::Release()
{
	m_pMesh->Release();
}
