#include "BaseInclude.h"
#include "ColiderComponent.h"
#include"BoundingSphere.h"
ColiderComponent::ColiderComponent()
	:m_pBoxMesh(NULL),m_bColision(false), m_fRadius(0), m_SphereMesh(NULL), m_bErase(false)
{

}
ColiderComponent::~ColiderComponent()
{
	Release();
}


void ColiderComponent::SetUp(INFO tInfo, float fRadius, CBound* pMesh)
{
	
	m_Info = tInfo;
	m_fRadius = fRadius;
	m_matWorld = tInfo.matWorld;
	m_pBoxMesh = pMesh;
	m_pBoxMesh->InitMesh(GetDevice());
	m_SphereMesh = new CBoundingSphere(m_fRadius,*m_pBoxMesh->GetCenter());
	m_SphereMesh->InitMesh(GetDevice());


	m_SphereInfo.fRadius = m_SphereMesh->GetRadius();
	m_SphereInfo.pMesh = m_SphereMesh->GetMesh();
	m_SphereInfo.isPicked = m_bColision;
	m_SphereInfo.vpCenter = m_SphereMesh->GetCenter();

	D3DMATRIX matWorld = m_Info.matWorld * m_matWorld;
	m_Info.vPos = { matWorld._41,matWorld._42,matWorld._43 };
	
}



void ColiderComponent::Render()
{
	D3DXMATRIX matWorld = m_Info.matWorld * m_matWorld;
	SetTexture(0, NULL);
	SetTransform(D3DTS_WORLD, &matWorld);
	SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	if(m_pBoxMesh)	m_pBoxMesh->GetMesh()->DrawSubset(0);
	if (m_SphereMesh)m_SphereMesh->GetMesh()->DrawSubset(0);
	SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	SetTexture(0, NULL);
}

bool ColiderComponent::CheckColision(ColiderComponent* pEnemy)
{
	D3DXVECTOR3 vPos = m_Info.vPos;
	D3DXVECTOR3 vPos2 = pEnemy->m_Info.vPos;
	vPos.y = 0;	vPos2.y = 0;
	D3DXVECTOR3 vRes = vPos-(vPos2);
	float fLenght = D3DXVec3Length(&vRes);
 	float fRadius = m_fRadius + pEnemy->m_fRadius;
	if (fLenght < fRadius)
		return true;

	return false;
}



void ColiderComponent::Update(D3DXVECTOR3 vPos)
{
	
	m_Info.matWorld._41 = vPos.x;
	m_Info.matWorld._42 = vPos.y;
	m_Info.matWorld._43 = vPos.z;
	D3DMATRIX matWorld = m_Info.matWorld * m_matWorld;
	m_Info.vPos = {matWorld._41,matWorld._42,matWorld._43};
}

void ColiderComponent::Release()
{
	SAFE_DELETE(m_SphereMesh);	m_SphereMesh = NULL;
	SAFE_DELETE(m_pBoxMesh);	m_pBoxMesh = NULL;
	m_VerTexBuffer.clear();
}
