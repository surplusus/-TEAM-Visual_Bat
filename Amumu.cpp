#include "BaseInclude.h"
#include "Amumu.h"
#include "ObjMgr.h"

CAmumu::CAmumu()
{
}

CAmumu::~CAmumu()
{
}

HRESULT	CAmumu::Initialize()
{
	m_SortID = SORTID_LAST;
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, 1.0f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_Info.vLook = D3DXVECTOR3(-10.f, 1.5f, -10.f);

	m_pOriVtx = new VTXTEX[4];
	m_pConVtx = new VTXTEX[4];


	D3DXMatrixIdentity(&m_Info.matWorld);
	CloneMesh(GetDevice(), L"Amumu", &m_pAnimationCtrl);

	m_vMin = *(GetMin(BOUNDTYPE_CUBE));
	m_vMax = *(GetMax(BOUNDTYPE_CUBE));
	return S_OK;
}

void CAmumu::Progress()
{

	MouseControl();
	WASDControl();

	UpdateWorldMatrix();
}

void CAmumu::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	if (!m_pAnimationCtrl)
	{
		cout << "null amumu animationCtrl" << endl;
		return;
	}
	m_pAnimationCtrl->SetAnimationSet(1);
	m_pAnimationCtrl->FrameMove(L"Amumu", GetTime());
	Mesh_Render(GetDevice(), L"Amumu");
}

void CAmumu::Release()
{
}

void CAmumu::UpdateWorldMatrix()
{
	D3DXMATRIX matRotX, matRotY, matRotZ, matTrans, matScale;
	D3DXMatrixRotationX(&matRotX, m_fAngle[ANGLE_X]);
	D3DXMatrixRotationY(&matRotY, m_fAngle[ANGLE_Y]);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle[ANGLE_Z]);
	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	m_Info.matWorld = matScale * matRotX*matRotY*matRotZ*matTrans;
	//CPipeLine::MyVec3TransformNormal(&m_Info.vDir, &m_Info.vLook, &m_Info.matWorld);

}

void CAmumu::MouseControl()
{
	if (!m_bIsPicked)
		return;

	D3DXVECTOR3 vNewDir = m_vecMouseHitPoint - m_Info.vPos; // 마우스 방향백터

	D3DXVECTOR3 vNewDirNormal;
	D3DXVec3Normalize(&vNewDirNormal, &vNewDir);  vNewDir.y = m_Info.vPos.y;
	float dot = D3DXVec3Dot(&m_Info.vDir, &vNewDirNormal);
	float radian = acosf(dot);

	if (fabs(radian) <= D3DX_16F_EPSILON) {
		m_fAngle[ANGLE_Y] += radian;
	}

	static float slowness = 9.f;
	D3DXVECTOR3 vLeft;
	D3DXVec3Cross(&vLeft, &m_Info.vDir, &D3DXVECTOR3(0.f, 1.f, 0.f));
	if (D3DXVec3Dot(&vNewDirNormal, &vLeft) > 0)
	{
		m_fAngle[ANGLE_Y] -= radian / slowness;
	}
	else
	{
		m_fAngle[ANGLE_Y] += radian / slowness;
	}

	if (fabs(vNewDir.x) <= 0.5f &&
		fabs(vNewDir.z) <= 0.5f) {
		if (slowness > 100.f) {
			m_Info.vPos = m_vecMouseHitPoint;
			slowness = 9.f;
			m_bIsPicked = false;
			return;
		}

		slowness *= 1.2f;
	}

	m_Info.vPos += vNewDirNormal / slowness;

}

void CAmumu::WASDControl()
{
	double speed = 4.0 * g_fDeltaTime;

	if (CheckPushKey(DIK_A)) {
		m_fAngle[ANGLE_Y] -= speed;
	}
	if (CheckPushKey(DIK_D)) {
		m_fAngle[ANGLE_Y] += speed;
	}
	if (CheckPushKey(DIK_W)) {
		m_Info.vPos += (m_Info.vDir * speed * 5);
	}
	if (CheckPushKey(DIK_S)) {
		m_Info.vPos -= (m_Info.vDir * speed * 5);
	}
}

void CAmumu::SetPickingPoint(D3DXVECTOR3 * pickpoint)
{
}
