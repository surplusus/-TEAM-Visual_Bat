#include "BaseInclude.h"
#include "Udyr.h"
#include "SoundManager.h"
#include "PickingSphereMgr.h"

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
	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0.f);

	SetUpPickingShere(1.f);
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
	Render_PickingShere();
}

void CUdyr::Release()
{
	SAFE_RELEASE(m_pMeshSphere);
	SAFE_RELEASE(m_pAnimationCtrl);
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
	{	// 방향전환
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
	{	// Sphere 픽킹
		if (MyGetMouseState().rgbButtons[1]) {
			SPHERE* spherePicked = nullptr;
			bool bPickSphere = GET_SINGLE(CPickingSphereMgr)->GetSpherePicked(this, &spherePicked);
			if (bPickSphere)
				spherePicked->isPicked = !spherePicked->isPicked;
		}
	}
}

void CUdyr::QWERControl()
{
	static int iAniIndex = 0;
	if (CheckPushKeyOneTime(VK_0)) {	// 애니메이션 정보 콘솔 출력
		m_pAnimationCtrl->DisplayAniSetNameOnConsole();
	}
	//if (CheckPushKeyOneTime(VK_Q)) {
	//	m_pAnimationCtrl->BlendAnimationSet(iAniIndex++);
	//	GET_SINGLE(SoundManager)->PlayEffectSound("Udyr1");
	//}
	//if (CheckPushKeyOneTime(VK_W)) {
	//	m_pAnimationCtrl->BlendAnimationSet(iAniIndex++);
	//	GET_SINGLE(SoundManager)->PlayEffectSound("Udyr2");
	//}
	//if (CheckPushKeyOneTime(VK_E)) {
	//	m_pAnimationCtrl->BlendAnimationSet(iAniIndex++);
	//	GET_SINGLE(SoundManager)->PlayEffectSound("Udyr3");
	//}
	//if (CheckPushKeyOneTime(VK_R)) {
	//	m_pAnimationCtrl->BlendAnimationSet(iAniIndex++);
	//	GET_SINGLE(SoundManager)->PlayEffectSound("Udyr4");
	//}
	// sound check
	if (CheckPushKeyOneTime(VK_1))
		GET_SINGLE(SoundManager)->PlayUdyrSound(T_SOUND::Udyr_Attack_Left);
	if (CheckPushKeyOneTime(VK_2))
		GET_SINGLE(SoundManager)->PlayUdyrSound(T_SOUND::Udyr_Idle);
	if (CheckPushKeyOneTime(VK_3))
		GET_SINGLE(SoundManager)->PlayUdyrSound(T_SOUND::Udyr_Search);
	if (CheckPushKeyOneTime(VK_4))
		GET_SINGLE(SoundManager)->PlayUdyrSound(T_SOUND::Udyr_Run);
	if (CheckPushKeyOneTime(VK_5))
		GET_SINGLE(SoundManager)->PlayUdyrSound(T_SOUND::Udyr_Taunt);
	if (CheckPushKeyOneTime(VK_6))
		GET_SINGLE(SoundManager)->PlayUdyrSound(T_SOUND::Udyr_Dance);
	if (CheckPushKeyOneTime(VK_7))
		GET_SINGLE(SoundManager)->PlayUdyrSound(T_SOUND::Udyr_Death);

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
