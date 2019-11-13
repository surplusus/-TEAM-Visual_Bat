#include "BaseInclude.h"
#include "Minion.h"
#include "MinionMgr.h"
#include "PickingSphereMgr.h"



CMinion::CMinion()
	: m_pMinionMgr(nullptr)
	, m_pHeightMap(nullptr)
	, m_fSize(1.f)
	, m_SphereForPick(1.f, &m_Info.vPos)
	, m_sphereTarget(nullptr)
{
}

CMinion::~CMinion()
{
}

void CMinion::ChangeNextPoint()
{
	static size_t idxNextPoint = 1;
	++idxNextPoint;
	idxNextPoint %= m_vNextPoints.size() - 1;
	m_NextPoint = m_vNextPoints[idxNextPoint];
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
	HRESULT result = D3DXCreateSphere(GET_DEVICE, r, 10, 10, &m_SphereForPick.pMesh, NULL);
	GET_SINGLE(CPickingSphereMgr)->AddSphere(this, &m_SphereForPick);
	return true;
}

bool CMinion::Render_PickingShere()
{
	if (m_SphereForPick.pMesh != nullptr) {
		D3DMATERIAL9 mtrl;
		ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
		if (m_SphereForPick.isPicked) {
			mtrl.Diffuse.r = mtrl.Ambient.r = mtrl.Specular.r = 1.f;
			mtrl.Diffuse.g = mtrl.Ambient.g = mtrl.Specular.g = 1.f;
			mtrl.Diffuse.b = mtrl.Ambient.b = mtrl.Specular.b = 1.f;
			mtrl.Diffuse.a = mtrl.Ambient.a = mtrl.Specular.a = 1.f;
		}
		else
		{
			mtrl.Diffuse.r = mtrl.Ambient.r = mtrl.Specular.r = 1.f;
			mtrl.Diffuse.g = mtrl.Ambient.g = mtrl.Specular.g = 0.f;
			mtrl.Diffuse.b = mtrl.Ambient.b = mtrl.Specular.b = 0.f;
			mtrl.Diffuse.a = mtrl.Ambient.a = mtrl.Specular.a = 1.f;
		}
		//LPDIRECT3DTEXTURE9 texture;
		//ZeroMemory(&texture, sizeof(LPDIRECT3DTEXTURE9);
		//D3DXCreateTextureFromFileA(GET_DEVICE, "./Resource/Test/mint.png", &texture);
		SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		//GET_DEVICE->SetTexture(0, NULL);
		//GET_DEVICE->SetTexture(0, texture);
		GET_DEVICE->SetMaterial(&mtrl);
		//GET_DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		m_SphereForPick.pMesh->DrawSubset(0);
		//GET_DEVICE->SetTexture(0, NULL);
		//texture->Release();
		//GET_DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		//return true;
		//GET_DEVICE->SetMaterial(NULL);
		GET_DEVICE->SetTexture(0, NULL);
		SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	return false;
}

void CMinion::SetDirectionToNextPoint()
{
	D3DXVECTOR3 vUp = { 0, 1.f, 0.f };
	m_Info.vDir = m_Info.vPos - m_NextPoint;
	D3DXVec3Normalize(&m_Info.vDir, &m_Info.vDir);
}

void CMinion::SetUpAniSetNameList()
{
	m_pAnimationCtrl->GetAnimationNames(m_AniSetNameList);
}

bool CMinion::TurnSlowly(const D3DXVECTOR3 * destPos, float fLerpRate)
{
	D3DXVECTOR3 vMousePos = *destPos - m_Info.vPos; vMousePos.y = m_fHeight;
	D3DXVECTOR3 vMouseNor;
	D3DXVec3Normalize(&vMouseNor, &vMousePos);
	if (_isnan(m_Info.vDir.y))	m_Info.vDir.y = vMouseNor.y;
	float fDot = D3DXVec3Dot(&m_Info.vDir, &vMouseNor);
	float fRadian = acosf(fDot);
	float fDirLerped = fRadian / fLerpRate;

	if (fabs(fRadian) <= D3DX_16F_EPSILON) {
		return false;
	}

	D3DXVECTOR3 vLeft;
	D3DXVec3Cross(&vLeft, &m_Info.vDir, &D3DXVECTOR3(0.f, 1.f, 0.f));
	if (D3DXVec3Dot(&vMouseNor, &vLeft) > 0) {
		m_fAngle[ANGLE_Y] -= fDirLerped;
		if (m_fAngle[ANGLE_Y] < D3DX_PI)
			m_fAngle[ANGLE_Y] += 2.f * D3DX_PI;
	}
	else {
		m_fAngle[ANGLE_Y] += fDirLerped;
		if (m_fAngle[ANGLE_Y] > D3DX_PI)
			m_fAngle[ANGLE_Y] -= 2.f * D3DX_PI;
	}

	return true;
}

void CMinion::SetPosition(const D3DXVECTOR3 * pos)
{
	m_Info.vPos.x = pos->x;
	m_Info.vPos.y = pos->y;
	m_Info.vPos.z = pos->z;
}