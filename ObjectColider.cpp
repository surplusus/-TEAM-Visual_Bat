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
	

	D3DXMATRIX		matView, matProj;
	GetTransform(D3DTS_VIEW, &matView);
	GetTransform(D3DTS_PROJECTION, &matProj);


	D3DMATRIX matWorld = m_Info.matWorld * m_matWorld;


	m_Info.vPos = { matWorld._41,matWorld._42,matWorld._43 };
	m_SphereInfo.vpCenter = &m_Info.vPos;

}

bool CObjectColider::CheckColision(ColiderComponent* pEnemy)
{
	return ColiderComponent::CheckColision(pEnemy);
}

