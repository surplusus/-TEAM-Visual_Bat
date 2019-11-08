#include "BaseInclude.h"
#include "TargetColider.h"


CTargetColider::CTargetColider()
	:m_Type(COLISION_TYPE_TARGETCHASE)
{
}


CTargetColider::~CTargetColider()
{
}

void CTargetColider::Update(D3DXVECTOR3 vPos)
{
	m_Info.vPos = vPos;
	WorldSetting();
}

bool CTargetColider::CheckColision(ColiderComponent * pEnemy)
{

	return ColiderComponent::CheckColision(pEnemy);
}
