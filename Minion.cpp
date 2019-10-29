#include "BaseInclude.h"
#include "Minion.h"
#include "MinionMgr.h"
#include "PickingSphereMgr.h"

CMinion::CMinion()
	: m_pMinionMgr(nullptr)
	, m_pHeightMap(nullptr)
	, m_fSize(1.f)
	, m_SphereForPick(1.f, &m_Info.vPos)
	, m_pMeshSphere(nullptr)
{
}

CMinion::~CMinion()
{
}

void CMinion::UpdateWorldMatrix()
{
	D3DXMATRIX matScale, matRot, matTrans;
	D3DXMatrixScaling(&matScale, m_fSize, m_fSize, m_fSize);
	D3DXQUATERNION quat; D3DXQuaternionIdentity(&quat);
	D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(0.f, 1.f, 0.f), m_fAngle[ANGLE_Y]);
	D3DXMatrixRotationQuaternion(&matRot, &quat);
	D3DXVec3TransformNormal(&m_Info.vDir, &D3DXVECTOR3(0.f, 0.f, -1.f), &matRot);
	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);
	m_Info.matWorld = matScale * matRot * matTrans;
}

bool CMinion::SetUpPickingShere(const float r, D3DXVECTOR3* v)
{
	m_SphereForPick.fRadius = r;
	if (v == nullptr) {
		m_SphereForPick.vpCenter = &m_Info.vPos;
	}
	GET_SINGLE(CPickingSphereMgr)->AddSphere(this, &m_SphereForPick);
	HRESULT result = D3DXCreateSphere(GET_DEVICE, r, 10, 10, &m_pMeshSphere, NULL);
	return true;
}

bool CMinion::Render_PickingShere()
{
	if (m_pMeshSphere != nullptr) {
		D3DMATERIAL9 mtrl;
		ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
		/*if (m_SphereForPick.isPicked) */{
			mtrl.Diffuse.r = mtrl.Ambient.r = mtrl.Specular.r = 1.f;
			mtrl.Diffuse.g = mtrl.Ambient.g = mtrl.Specular.g = 0.f;
			mtrl.Diffuse.b = mtrl.Ambient.b = mtrl.Specular.b = 0.f;
			mtrl.Diffuse.a = mtrl.Ambient.a = mtrl.Specular.a = 1.f;
		}
		/*else
		{
			mtrl.Diffuse.r = mtrl.Ambient.r = 1.f;
			mtrl.Diffuse.g = mtrl.Ambient.g = 1.f;
			mtrl.Diffuse.b = mtrl.Ambient.b = 1.f;
			mtrl.Diffuse.a = mtrl.Ambient.a = 1.f;
		}*/
		GET_DEVICE->SetTexture(0,NULL);
		GET_DEVICE->SetMaterial(&mtrl);
		//GET_DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		m_pMeshSphere->DrawSubset(0);
		//GET_DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		return true;
	}
	return false;
}

void CMinion::SetDirectionToNextPoint()
{
	D3DXVECTOR3 vUp = { 0, 1.f, 0.f };
	m_Info.vDir = m_Info.vPos - m_vNextPoint;
	D3DXVec3Normalize(&m_Info.vDir, &m_Info.vDir);
}