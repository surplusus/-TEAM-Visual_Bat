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

inline const D3DXVECTOR3 * CBound::GetMin() {
	return &m_vMin;
}

inline const D3DXVECTOR3 * CBound::GetMax()
{
	return &m_vMax;
}

const D3DXVECTOR3 * CBound::GetCenter()
{
	return &m_vCenter;
}

const float CBound::GetRadius()
{
	return m_fRadius;
}

void CBound::Release()
{
	m_pMesh->Release();
}
