#include "BaseInclude.h"
#include "Udyr.h"
#include "SoundManager.h"

CUdyr::CUdyr()
	: m_bRunning(false)
	, m_bTurning(false)
	, m_bDirty(false)
{
}

CUdyr::~CUdyr()
{
	Release();
}

HRESULT CUdyr::Initialize()
{
	CloneMesh(GetDevice(), L"Udyr", &m_pAnimationCtrl);
	if (!m_pAnimationCtrl)
		return S_FALSE;
	UpdateWorldMatrix();
	m_pAnimationCtrl->SetAnimationSet("Default_Action");
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, -1.0f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, -1.f);
	m_Info.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	return S_OK;
}

void CUdyr::Progress()
{
	MouseControl();
	QWERControl();
	CChampion::UpdateWorldMatrix();
	ChangeAniSetByState();
	m_pAnimationCtrl->FrameMove(L"Udyr", g_fDeltaTime);
}

void CUdyr::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), L"Udyr");
}

void CUdyr::Release()
{
}

void CUdyr::ChangeAniSetByState()
{
	if (m_bDirty)
	{
		if (m_bRunning) {
			m_pAnimationCtrl->BlendAnimationSet("Run");
			m_bDirty = false;
			return;
		}

		m_pAnimationCtrl->BlendAnimationSet("Idle");
		m_bDirty = false;
	}
}

void CUdyr::MouseControl()
{
	if (MyGetMouseState().rgbButtons[0]) {
		m_bPicked = SearchPickingPointInHeightMap(GetVertexNumInHeightMap(), GetVertexInHeightMap());
	}

	if (m_bPicked) {
		m_bPicked = false;
		m_bRunning = true;
		m_bDirty = true;
	}

	if (m_bRunning)
	{
		float speed = 2.5f;
		m_bTurning = TurnSlowly(&m_MouseHitPoint);
		m_bRunning = Update_vPos_ByDestPoint(&m_MouseHitPoint, speed);
		if (!m_bRunning)
			m_bDirty = true;
	}
}

void CUdyr::QWERControl()
{
	static int iAniIndex = 0;
	if (CheckPushKeyOneTime(VK_1)) {	// 애니메이션 정보 콘솔 출력
		m_pAnimationCtrl->DisplayAniSetNameOnConsole();
	}
	if (CheckPushKeyOneTime(VK_Q)) {
		m_pAnimationCtrl->BlendAnimationSet(iAniIndex++);
		GET_SINGLE(SoundManager)->PlayEffectSound("Udyr1");
	}
	if (CheckPushKeyOneTime(VK_W)) {
		m_pAnimationCtrl->BlendAnimationSet(iAniIndex++);
		GET_SINGLE(SoundManager)->PlayEffectSound("Udyr2");
	}
	if (CheckPushKeyOneTime(VK_E)) {
		m_pAnimationCtrl->BlendAnimationSet(iAniIndex++);
		GET_SINGLE(SoundManager)->PlayEffectSound("Udyr3");
	}
	if (CheckPushKeyOneTime(VK_R)) {
		m_pAnimationCtrl->BlendAnimationSet(iAniIndex++);
		GET_SINGLE(SoundManager)->PlayEffectSound("Udyr4");
	}
}

bool CUdyr::TurnSlowly(const D3DXVECTOR3 * destPos)
{
	D3DXVECTOR3 vMousePos = *destPos - m_Info.vPos; vMousePos.y = m_fHeight;
	D3DXVECTOR3 vMouseNor;
	D3DXVec3Normalize(&vMouseNor, &vMousePos);
	float fDot = D3DXVec3Dot(&m_Info.vDir, &vMouseNor);
	float fRadian = acosf(fDot);
	float fDirLerped = fRadian / 7.f;

	if (fabs(fRadian) <= D3DX_16F_EPSILON) {
		return false;
	}

	D3DXVECTOR3 vLeft;
	D3DXVec3Cross(&vLeft, &m_Info.vDir, &D3DXVECTOR3(0.f, 1.f, 0.f));
	if (D3DXVec3Dot(&vMouseNor, &vLeft) > 0) {
		m_fAngle[ANGLE_Y] -= fDirLerped;
		if (m_fAngle[ANGLE_Y] <= D3DX_PI)
			m_fAngle[ANGLE_Y] += 2.f * D3DX_PI;
	}
	else {
		m_fAngle[ANGLE_Y] += fDirLerped;
		if (m_fAngle[ANGLE_Y] >= D3DX_PI)
			m_fAngle[ANGLE_Y] -= 2.f * D3DX_PI;
	}

	return false;
}
