#include "BaseInclude.h"
#include "ColiderComponent.h"
#include"BoundingSphere.h"
ColiderComponent::ColiderComponent()
	:m_pBoxMesh(NULL),m_bColision(false), m_fRadius(0), m_SphereMesh(NULL)
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

	D3DMATRIX matWorld = m_Info.matWorld * m_matWorld;
	m_Info.vPos = { matWorld._41,matWorld._42,matWorld._43 };
	
}



void ColiderComponent::Render()
{
	D3DXMATRIX matWorld = m_Info.matWorld * m_matWorld;
	SetTexture(0, NULL);
	SetTransform(D3DTS_WORLD, &matWorld);
	SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pBoxMesh->GetMesh()->DrawSubset(0);
	m_SphereMesh->GetMesh()->DrawSubset(0);
	SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	SetTexture(0, NULL);
}

bool ColiderComponent::CheckColision(ColiderComponent* pEnemy)
{
	D3DXVECTOR3 vPos = m_Info.vPos;
	D3DXVECTOR3 vPos2 = pEnemy->m_Info.vPos;
	D3DXVECTOR3 vRes = vPos-(vPos2);
	float fLenght = D3DXVec3Length(&vRes);
 	float fRadius = m_fRadius + pEnemy->m_fRadius;
	if ( (g_fDeltaTime / 2)) {
		cout << "실제 거리:" << fLenght << endl;
		cout << "충돌 거리 : " << fRadius << endl;
	}
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
	m_VerTexBuffer.clear();
}
