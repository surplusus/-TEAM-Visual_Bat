#include "BaseInclude.h"
#include "ColiderComponent.h"

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
 	m_pBoxMesh = pMesh;
	m_ParentMatrix = m_Info.matWorld;
	m_pBoxMesh->InitMesh(GetDevice());
	m_SphereMesh = new CBoundingSphere(m_fRadius,*m_pBoxMesh->GetCenter());
	m_SphereMesh->InitMesh(GetDevice());
	m_fAngle[ANGLE_X] = 0;
	m_fAngle[ANGLE_Y] = 0;
	m_fAngle[ANGLE_Z] = 0;
	m_vCenter = *m_SphereMesh->GetCenter()+m_Info.vPos;
	cout << m_vCenter.x << m_vCenter.y << m_vCenter.z;
	m_vCenter.y = 0;
	m_SphereInfo.fRadius = m_SphereMesh->GetRadius();
	m_SphereInfo.pMesh = m_SphereMesh->GetMesh();
	m_SphereInfo.isPicked = m_bColision;
	m_SphereInfo.vpCenter = &m_vCenter;
}



void ColiderComponent::Render()
{
	SetTexture(0, NULL);
	SetTransform(D3DTS_WORLD, &(m_Info.matWorld));
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

	m_Info.vPos = vPos;
	WorldSetting();
}

void ColiderComponent::Release()
{
	SAFE_DELETE(m_SphereMesh);	m_SphereMesh = NULL;
	SAFE_DELETE(m_pBoxMesh);	m_pBoxMesh = NULL;
	m_VerTexBuffer.clear();
}

void ColiderComponent::WorldSetting()
{
	
	D3DXMATRIX matRotX, matRotY, matRotZ, matTrans, matScale;
	D3DXMatrixRotationX(&matRotX, m_fAngle[ANGLE_X]);
	D3DXMatrixRotationY(&matRotY, m_fAngle[ANGLE_Y]);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle[ANGLE_Z]);
	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);
	D3DXMatrixScaling(&matScale, 1.0f, 1.0f, 1.0f);
	m_Info.matWorld = matScale*matRotX*matRotY*matRotZ*matTrans;
	
}
