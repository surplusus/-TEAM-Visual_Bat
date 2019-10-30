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

void CUdyr::ControlFlag()
{
	int num, idx;
	// 비트 값 확인
	bool r1 = ((num & (1 << idx)) != 0);
	// 비트 값만 채워넣기
	int r2 = (num | (1 << idx));
	// 비트 값만 삭제하기
	int r3 = (num & ~(1 << idx));
	// 비트 값만 켜고 나머지 전부 삭제하기
	int f4 = (1 << idx);
	 
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
	{	// Push_back StateFunc
		m_vStateFunc.push_back([this]() {return this->Func1_IDLE(); });
		m_vStateFunc.push_back([this]() {return this->Func2_ATTACK(); });
		m_vStateFunc.push_back([this]() {return this->Func3_RUN(); });
		m_vStateFunc.push_back([this]() {return this->Func4_AGRESSIVE(); });

		m_bStateFlag = new bool[STATETYPE_END + 1];
		fill(m_bStateFlag[0], m_bStateFlag[STATETYPE_END], false);
	}
	return S_OK;
}

void CUdyr::Progress()
{
	MouseControl();
	QWERControl();
	ProgressStateFunc();
	//ChangeAniSetByState();
	CChampion::UpdateWorldMatrix();
	m_pAnimationCtrl->FrameMove(L"Udyr", g_fDeltaTime);
}

void CUdyr::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), L"Udyr");
	//Render_PickingShere();
}

void CUdyr::Release()
{
	SAFE_RELEASE(m_pMeshSphere);
	SAFE_RELEASE(m_pAnimationCtrl);
}

void CUdyr::MouseControl()
{
	{	// 방향전환
		bool bPicked = false;
		if (CheckMouseButtonDownOneTime(MOUSEBUTTON0)) {
			bPicked = SearchPickingPointInHeightMap(GetVertexNumInHeightMap(), GetVertexInHeightMap());
		}

		if (bPicked) {
			
			m_vStateFlag[STATETYPE_IDLE] = false;
			m_vStateFlag[STATETYPE_RUN] = true;
			m_vStateFlag[STATETYPE_TURNING] = true;
			//m_queStateFunc.push(m_vStateFunc[STATETYPE_RUN]);
		}

		//if (m_bPicked) {
		//	m_bPicked = false;
		//	m_bRunning = true;
		//	m_bDirty = true;
		//}

		//if (m_vStateFlag[STATETYPE_RUN])
		//{
		//	float speed = 2.5f;
		//	m_vStateFlag[STATETYPE_TURNING] = TurnSlowly(&m_MouseHitPoint);
		//	m_vStateFlag[STATETYPE_RUN] = Update_vPos_ByDestPoint(&m_MouseHitPoint, speed);
		//	if (!m_bRunning)
		//		m_bDirty = true;
		//}
	}
	{	// Sphere 픽킹
		if (CheckMouseButtonDownOneTime(MOUSEBUTTON2)) {
			SPHERE* spherePicked = nullptr;
			bool bPickSphere = GET_SINGLE(CPickingSphereMgr)->GetSpherePicked(this, &spherePicked);
			if (bPickSphere) {
				spherePicked->isPicked = !spherePicked->isPicked;
				m_bRunning = true;
				m_MouseHitPoint = D3DXVECTOR3(*spherePicked->vpCenter);
				int a = 6;
			}

		}
	}
}

void CUdyr::QWERControl()
{
	static int iAniIndex = 0;
	if (CheckPushKeyOneTime(VK_0)) {	// 애니메이션 정보 콘솔 출력
		m_pAnimationCtrl->DisplayAniSetNameOnConsole();
	}
	if (CheckPushKeyOneTime(VK_Q)) {
		m_pAnimationCtrl->BlendAnimationSet("Attack_Left");
		//GET_SINGLE(SoundManager)->PlayEffectSound("Udyr1");
	}
	if (CheckPushKeyOneTime(VK_W)) {
		m_vStateFlag.resize(STATETYPE_END, false);
		m_vStateFlag[STATETYPE_IDLE] = true;
		m_pAnimationCtrl->BlendAnimationSet("Idle");
		//GET_SINGLE(SoundManager)->PlayEffectSound("Udyr2");
	}
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

bool CUdyr::Func1_IDLE()
{
	m_pAnimationCtrl->BlendAnimationSet("Idle");
	
	return true;
}

bool CUdyr::Func2_ATTACK()
{
	return false;
}

bool CUdyr::Func3_RUN()
{
	m_pAnimationCtrl->BlendAnimationSet("Run");
	
	float speed = 2.5f;
	if (m_vStateFlag[STATETYPE_TURNING])
		m_vStateFlag[STATETYPE_TURNING] = TurnSlowly(&m_MouseHitPoint);
	m_vStateFlag[STATETYPE_RUN] = Update_vPos_ByDestPoint(&m_MouseHitPoint, speed);
	if (!m_vStateFlag[STATETYPE_RUN])
		m_vStateFlag[STATETYPE_IDLE] = true;
	return false;
}

bool CUdyr::Func4_AGRESSIVE()
{
	return false;
}

void CUdyr::ProgressStateFunc()
{
	// EnqueueStateFunc
	for (size_t i = 0; i < m_vStateFlag.size(); i++)
	{
		if (i >= m_vStateFunc.size())
			break;
		if (m_vStateFlag[i] == true)
			m_queStateFunc.push(m_vStateFunc[i]);
	}
	// Play StateFunc Enqueued
	FUNCSTATE func;
	while (!m_queStateFunc.empty()) {
		func = m_queStateFunc.front();
		m_queStateFunc.pop();
		bool result = func();
	}
}

//bool CUdyr::TurnSlowly(const D3DXVECTOR3 * destPos)
//{
//	D3DXVECTOR3 vMousePos = *destPos - m_Info.vPos; vMousePos.y = m_fHeight;
//	D3DXVECTOR3 vMouseNor;
//	D3DXVec3Normalize(&vMouseNor, &vMousePos);
//	float fDot = D3DXVec3Dot(&m_Info.vDir, &vMouseNor);
//	float fRadian = acosf(fDot);
//	float fDirLerped = fRadian / 7.f;
//
//	if (fabs(fRadian) <= D3DX_16F_EPSILON) {
//		return false;
//	}
//
//	D3DXVECTOR3 vLeft;
//	D3DXVec3Cross(&vLeft, &m_Info.vDir, &D3DXVECTOR3(0.f, 1.f, 0.f));
//	if (D3DXVec3Dot(&vMouseNor, &vLeft) > 0) {
//		m_fAngle[ANGLE_Y] -= fDirLerped;
//		if (m_fAngle[ANGLE_Y] <= D3DX_PI)
//			m_fAngle[ANGLE_Y] += 2.f * D3DX_PI;
//	}
//	else {
//		m_fAngle[ANGLE_Y] += fDirLerped;
//		if (m_fAngle[ANGLE_Y] >= D3DX_PI)
//			m_fAngle[ANGLE_Y] -= 2.f * D3DX_PI;
//	}
//
//	return false;
//}
