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
	m_Info.vPos = vPos;
	WorldSetting();
}

bool CObjectColider::CheckColision(ColiderComponent* pEnemy)
{
	return ColiderComponent::CheckColision(pEnemy);
}

