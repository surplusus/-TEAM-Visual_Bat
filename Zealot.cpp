#include "BaseInclude.h"
#include "Zealot.h"
#include "Ray.h"

CZealot::CZealot()
{
}

CZealot::~CZealot()
{
	Release();
}

HRESULT CZealot::Initialize()
{
	CloneMesh(GetDevice(), L"Zealot", &m_pAnimationCtrl);
	if (!m_pAnimationCtrl)
		return S_FALSE;
	g_MouseHitPoint = m_Info.vPos;
	UpdateWorldMatrix();
	return S_OK;
}

void CZealot::Progress()
{
	MouseControl();
	QWERControl();
	UpdateWorldMatrix();
	m_pAnimationCtrl->SetAnimationSet("Stand");
	m_pAnimationCtrl->FrameMove(L"Zealot", g_fDeltaTime);
}

void CZealot::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), L"Zealot");
}

void CZealot::Release()
{
}

void CZealot::UpdateWorldMatrix()
{
	D3DXQUATERNION qtRot(m_fAngle[ANGLE_X], m_fAngle[ANGLE_Y], m_fAngle[ANGLE_Z], 1.f);
	D3DXMATRIX matScale, matRot, matTrans;
	D3DXMatrixScaling(&matScale, m_fSize, m_fSize, m_fSize);
	D3DXMatrixRotationQuaternion(&matRot, &qtRot);
	D3DXVec3TransformNormal(&m_Info.vDir, &m_Info.vLook, &matRot);
	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);
	m_Info.matWorld = matScale * matRot * matTrans;
}

void CZealot::MouseControl()
{
	static bool isTurning = false;
	if (MyGetMouseState().rgbButtons[0])
		EnqueueMousePickingFunc();
	if (g_bHitFloor) {
		isTurning = true;
		m_bIsPicked = true;
	}

	if (m_bIsPicked)
	{
		float speed;
		if (isTurning) {
			isTurning = TurnSlowly(&g_MouseHitPoint);
			speed = 0.1f;
		}
		else
			speed = 1.f;
		printf("MouseHitPoint : %.2f,%.2f,%.2f\n",
			g_MouseHitPoint.x, g_MouseHitPoint.y, g_MouseHitPoint.z);
		// Update_vPos_ByDestPoint : mouseHitPos와 거리가 0.1f 보다 작으면 false 리턴
		m_bIsPicked = Update_vPos_ByDestPoint(&g_MouseHitPoint, speed);
	}
}

void CZealot::QWERControl()
{
	if (CheckPushKeyOneTime(VK_Q)) {

	}
	if (CheckPushKeyOneTime(VK_W)) {

	}
	if (CheckPushKeyOneTime(VK_E)) {

	}
	if (CheckPushKeyOneTime(VK_R)) {

	}
}

bool CZealot::TurnSlowly(const D3DXVECTOR3 * destPos)
{
	static float speed = 5.f;
	D3DXVECTOR3 normal(*destPos); normal.y = 0.f;
	D3DXVec3Normalize(&normal, &normal);
	float dot = D3DXVec3Dot(&m_Info.vDir, &normal);
	float radian = acosf(dot);
	if (radian < 0.00001f)
	{
		m_Info.vDir = normal;
		return false;
	}
	else
	{
		D3DXVECTOR3 left;
		D3DXVec3Cross(&left, &m_Info.vDir, &D3DXVECTOR3(0.f, 1.f, 0.f));
		if (D3DXVec3Dot(&normal, &left) > 0)
			m_fAngle[ANGLE_Y] -= radian * speed / 100.f;
		else
			m_fAngle[ANGLE_Y] += radian * speed / 100.f;
	}

	return true;
}
