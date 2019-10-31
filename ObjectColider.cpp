#include "BaseInclude.h"
#include "ObjectColider.h"


CObjectColider::CObjectColider(CObj* pObj)
	:m_pObj(pObj), m_Type(COLISION_TYPE_OBJECT)
{
}


CObjectColider::~CObjectColider()
{
	Release();
}

void CObjectColider::Update(D3DXVECTOR3 vPos)
{

	m_Info.matWorld._41 = vPos.x;
	m_Info.matWorld._42 = vPos.y;
	m_Info.matWorld._43 = vPos.z;
	m_Info.vPos = vPos;
	m_Info.matWorld = m_Info.matWorld*m_matWorld;
}
