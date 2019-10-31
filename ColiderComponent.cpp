#include "BaseInclude.h"
#include "ColiderComponent.h"
#include "BoundingBox.h"

ColiderComponent::ColiderComponent()
	:m_pSphareMesh(NULL), m_pBoudingBox(NULL), m_pMesh(NULL),m_bColision(false), m_fRadius(0)

{
}
ColiderComponent::~ColiderComponent()
{
	Release();
}


void ColiderComponent::SetUp(INFO tInfo, float fRadius, D3DXMATRIX matWorld)
{
	
	m_Info = tInfo;
	m_fRadius = fRadius;
	m_matWorld = tInfo.matWorld;
	m_pBoudingBox = new CBoundingBox;
	m_pBoudingBox->InitMesh(GetDevice());
	m_pMesh = m_pBoudingBox->GetMesh();
	D3DXCreateSphere(GetDevice(), m_fRadius, 20, 20, &m_pSphareMesh, NULL);

	
}



void ColiderComponent::Render()
{
	SetTexture(0, NULL);
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pSphareMesh->DrawSubset(0);
	SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	SetTexture(0, NULL);
}

bool ColiderComponent::CheckColision(ColiderComponent* pEnemy)
{
	D3DXVECTOR3 vPos = (m_Info.vPos);
	D3DXVECTOR3 vPos2 = ((pEnemy->m_Info.vPos));
	D3DXVECTOR3 vRes = vPos-(vPos2);
	float fLenght = D3DXVec3Length(&vRes);
 	float fRadius = m_fRadius + pEnemy->m_fRadius;
	if ( (g_fDeltaTime / 2) ==1) {
		cout << "角力 芭府:" << fLenght << endl;
		cout << "面倒 芭府 : " << fRadius << endl;
	}
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

			int VtxNum = m_pMesh->GetNumVertices();
			VTXTEX* pVertex = NULL;
			pVB->Lock(0, VtxNum, (void**)&pVertex, 0);
			for (int i = 0; i < VtxNum; i++)
			{
				m_VerTexBuffer.push_back(pVertex[i]);
			}
		}
	}
	pVB->Unlock();      pVB->Release();
}

void ColiderComponent::SetCollison(D3DXVECTOR3 vMin, D3DXVECTOR3 vMax)
{
	//BYTE *pv = 0;
	//if (m_pBoudingBox != NULL) {
	//	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)pv);
	//	D3DXComputeBoundingBox((D3DXVECTOR3*)pv, m_pMesh->GetNumVertices(), D3DXGetFVFVertexSize(m_pMesh->GetFVF()), &vMin, &vMax);
	//	m_pBoudingBox->GetMesh()->UnlockVertexBuffer();
	//	
	//}
	if (m_pSphareMesh != NULL) {

	D3DXVECTOR3 vCenter = { m_matWorld._41 ,m_matWorld._42,m_matWorld._43};
	float fRadius = m_fRadius;	
	BYTE *v = 0;	
	m_pSphareMesh->LockVertexBuffer(0, (void**)&v);
	D3DXComputeBoundingSphere((D3DXVECTOR3*)v, m_pSphareMesh->GetNumVertices(), D3DXGetFVFVertexSize(m_pSphareMesh->GetFVF()), &vCenter, &m_fRadius);
	m_pSphareMesh->UnlockVertexBuffer();
	
	m_fRadius = fRadius * 0.2f;
	}
}
void ColiderComponent::Update(D3DXVECTOR3 vPos)
{

	m_Info.matWorld._41 = vPos.x;
	m_Info.matWorld._42 = vPos.y;
	m_Info.matWorld._43 = vPos.z;
	m_Info.vPos = vPos;
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, vPos.x, vPos.y, vPos.z);
	m_Info.matWorld = matTrans*m_matWorld;
}

void ColiderComponent::Release()
{
	if (m_pBoudingBox)	{
		SAFE_DELETE(m_pBoudingBox);	m_pBoudingBox = NULL;
	}
	m_pMesh->Release();			m_pMesh = NULL;
	m_pSphareMesh->Release();	m_pSphareMesh = NULL;
	
	m_VerTexBuffer.clear();
}
