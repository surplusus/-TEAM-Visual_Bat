#include "BaseInclude.h"
#include "ColiderComponent.h"
#include "BoundingBox.h"

ColiderComponent::ColiderComponent()
	
{
}

ColiderComponent::ColiderComponent(CObj * pObj)
	:m_pObj(pObj),m_pParticle(NULL), m_pSphareMesh(NULL), m_pBoudingBox(NULL)
{
}


ColiderComponent::ColiderComponent(CParticle * pParticle)
	: m_pObj(NULL), m_pParticle(pParticle),m_pSphareMesh(NULL),m_pBoudingBox(NULL)
{

}

ColiderComponent::~ColiderComponent()
{
}


void ColiderComponent::SetUp(D3DXVECTOR3 vPos, float fRadius, D3DXMATRIX matWorld)
{
	
	m_pvPosition = vPos;
	m_fRadius = fRadius;
	m_matWorld = matWorld;
	m_pBoudingBox = new CBoundingBox;
	m_pBoudingBox->InitMesh(GetDevice());
	m_pMesh = m_pBoudingBox->GetMesh();
	
}



void ColiderComponent::Render()
{
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, (m_pvPosition).x, (m_pvPosition).y, (m_pvPosition).z);
	D3DXMATRIX matWorld = m_matWorld*matTrans;
	SetTransform(D3DTS_WORLD, &matWorld);
	D3DXCreateSphere(GetDevice(), m_fRadius, 20, 20, &m_pSphareMesh, NULL);
	//m_pMesh->DrawSubset(0);
	SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pSphareMesh->DrawSubset(0);
	SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

bool ColiderComponent::CheckColision(ColiderComponent* pEnemy)
{
	D3DXVECTOR3 vPos = (m_pvPosition);
	D3DXVECTOR3 vPos2 = ((pEnemy->m_pvPosition));
	D3DXVECTOR3 vRes = vPos-vPos2;
	float fLenght = D3DXVec3Length(&vRes);
	float fRadius = m_fRadius + pEnemy->m_fRadius;
	if (fLenght < fRadius)
		return true;

	return false;
}

void ColiderComponent::InitColider()
{
	LPDIRECT3DVERTEXBUFFER9 pVB;
	if (m_pMesh){
		if (SUCCEEDED(m_pMesh->GetVertexBuffer(&pVB)))
		{

			int FaceNum = m_pMesh->GetNumFaces();
			int VtxNum = m_pMesh->GetNumVertices();
			VTXTEX* pVertex = NULL;
			pVB->Lock(0, sizeof(VTXTEX)*m_pMesh->GetNumVertices(), (void**)&pVertex, 0);
			for (int i = 0; i < VtxNum; i++)
			{
				m_VerTexBuffer.push_back(pVertex[i]);
			}
		}
	}
	pVB->Unlock();      pVB->Release();
}

void ColiderComponent::SetCollison(D3DXVECTOR3 vMin,D3DXVECTOR3 vMax)
{
	/*D3DXComputeBoundingBox(&m_VerTexBuffer[0].vPosition, m_VerTexBuffer.size(), sizeof(m_VerTexBuffer), &vMin, &vMax);
	D3DXVECTOR3 vCenter;
	D3DXComputeBoundingSphere(&m_VerTexBuffer[0].vPosition, m_VerTexBuffer.size(), D3DXGetFVFVertexSize(VTXFVF_VTXTEX), &vCenter, &m_fRadius);
	m_fRadius = m_pBoudingBox->GetRadius();
*/
}

void ColiderComponent::Update(D3DXVECTOR3 vPos)
{
	m_pvPosition = vPos;
}
