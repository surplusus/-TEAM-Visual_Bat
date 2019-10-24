#include "BaseInclude.h"
#include "Zealot.h"
#include "Ray.h"
#include "ObjMgr.h"
#include "HeightMap.h"
#include "SoundManager.h"

CZealot::CZealot()
	: m_bRunning(false)
	, m_bTurning(false)
	, m_pHeightMap(nullptr)
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
	UpdateWorldMatrix();
	//m_pAnimationCtrl->SetAnimationSet("Default_Action");
	m_pAnimationCtrl->SetAnimationSet("Stand");
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, -1.0f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, -1.f);
	m_Info.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_fHeight = 0.0f; // 높이맵 적용할 CDynamic 맴버
	return S_OK;
}

void CZealot::Progress()
{
	MouseControl();
	QWERControl();
	UpdateWorldMatrix();
	{	// Animation 상태머신 써야됨
		//if (m_bRunning)
		//	m_pAnimationCtrl->BlendAnimationSet("Walk");
		//if (!m_bRunning)
		//	m_pAnimationCtrl->BlendAnimationSet("Stand");
		m_pAnimationCtrl->FrameMove(L"Zealot", g_fDeltaTime);
	}
}

void CZealot::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), L"Zealot");
}

void CZealot::Release()
{
}

void CZealot::MouseControl()
{
	if (MyGetMouseState().rgbButtons[0]) {
		const VTXTEX* vtx = m_pHeightMap->GetVtxInfo();
		DWORD number = m_pHeightMap->m_VtxNum;
		m_bPicked = MapCheckThreadLoop(number, vtx);
	}

	if (m_bPicked) {
		m_bPicked = false;
		m_bRunning = true;
		m_bTurning = true;
	}

	if (m_bRunning)
	{
		float speed = 2.5f;
		//printf("MouseHitPoint : %.2f,%.2f,%.2f\n",
		//	g_MouseHitPoint.x, g_MouseHitPoint.y, g_MouseHitPoint.z);
		m_bTurning = Turn(&m_MouseHitPoint);
		//if (m_bTurning) {
		//	m_bTurning = Turn(&g_MouseHitPoint);
		//}

		// Update_vPos_ByDestPoint : mouseHitPos와 거리가 작으면 false 리턴
		m_bRunning = Update_vPos_ByDestPoint(&m_MouseHitPoint, speed);
		//if (!m_bRunning)
		//	m_pAnimationCtrl->BlendAnimationSet("Stand");
	}
}

void CZealot::QWERControl()
{
	static int iAniIndex = 0;
	if (CheckPushKeyOneTime(VK_1)) {
		m_pAnimationCtrl->DisplayAniSetNameOnConsole();
	}
	if (CheckPushKeyOneTime(VK_2)) {
		m_pAnimationCtrl->BlendAnimationSet(iAniIndex++);
		GET_SINGLE(SoundManager)->PlayEffectSound("Udyr1");
	}
	if (CheckPushKeyOneTime(VK_3)) {
		m_pAnimationCtrl->BlendAnimationSet("Spell3");
		GET_SINGLE(SoundManager)->PlayEffectSound("Udyr2");
	}
	/*if (CheckPushKeyOneTime(VK_4)) {
		m_pAnimationCtrl->BlendAnimationSet("Search");
		GET_SINGLE(SoundManager)->PlayEffectSound("Udyr3");
	}
	if (CheckPushKeyOneTime(VK_5)) {
		m_pAnimationCtrl->BlendAnimationSet("Run");
		GET_SINGLE(SoundManager)->PlayEffectSound("Udyr4");
	}
	if (CheckPushKeyOneTime(VK_6)) {
		m_pAnimationCtrl->BlendAnimationSet("Taunt");
		GET_SINGLE(SoundManager)->PlayEffectSound("Udyr5");
	}
	if (CheckPushKeyOneTime(VK_7)) {
		m_pAnimationCtrl->BlendAnimationSet("Dance");
		GET_SINGLE(SoundManager)->PlayEffectSound("Udyr6");
	}
	if (CheckPushKeyOneTime(VK_8)) {
		m_pAnimationCtrl->BlendAnimationSet("Death");
		GET_SINGLE(SoundManager)->PlayEffectSound("Udyr7");
	}*/
}

bool CZealot::TurnSlowly(const D3DXVECTOR3 * destPos)
{
	D3DXVECTOR3 vMousePos = *destPos; vMousePos.y = m_fHeight;
	D3DXVECTOR3 vMouseNor;
	D3DXVec3Normalize(&vMouseNor, &vMousePos);
	// m_Info.vDir : (0,0,-1)
	float fDot = D3DXVec3Dot(&m_Info.vDir, &vMouseNor);
	float fRadian = acosf(fDot);
	float fDirLerped = fRadian / 7.f;
	//float fDirLerped = fRadian;
	
	if (fabs(fDirLerped) <= 0.01f){
		m_fAngle[ANGLE_Y] += fRadian;
		return false;
	}

	D3DXVECTOR3 vLeft;
	D3DXVec3Cross(&vLeft, &m_Info.vDir, &D3DXVECTOR3(0.f, 1.f, 0.f));
	if (D3DXVec3Dot(&vMouseNor, &vLeft) > 0)
		m_fAngle[ANGLE_Y] -= fDirLerped;
	else
		m_fAngle[ANGLE_Y] += fDirLerped;

	return true;
}

bool CZealot::Turn(const D3DXVECTOR3 * destPos)
{
	D3DXVECTOR3 vMousePos = *destPos - m_Info.vPos; vMousePos.y = m_fHeight;
	D3DXVECTOR3 vMouseNor;
	D3DXVec3Normalize(&vMouseNor, &vMousePos);
	float fDot = D3DXVec3Dot(&m_Info.vDir, &vMouseNor);
	float fRadian = acosf(fDot);
	
	if (fabs(fRadian) < 0.01f) {
		m_fAngle[ANGLE_Y] = 0.f;
		return false;
	}

	D3DXVECTOR3 vLeft;
	D3DXVec3Cross(&vLeft, &m_Info.vDir, &D3DXVECTOR3(0.f, 1.f, 0.f));
	if (D3DXVec3Dot(&vMouseNor, &vLeft) > 0)
		m_fAngle[ANGLE_Y] = -fRadian;
	else
		m_fAngle[ANGLE_Y] = +fRadian;

	return false;
}

void CZealot::SetHeightMap(CHeightMap * pHeightMap)
{
	m_pHeightMap = pHeightMap;
}

float CZealot::lerp(float p1, float p2, float d)
{
	return (1-d) * p1 + d * p2;
}

