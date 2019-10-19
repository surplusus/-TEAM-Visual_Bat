#include "BaseInclude.h"
#include "Zealot.h"
#include "Ray.h"
#include "ObjMgr.h"


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

void CZealot::MouseControl()
{
	if (MyGetMouseState().rgbButtons[0]) {
		m_pAnimationCtrl->BlendAnimationSet("Walk");
		const VTXTEX* vtx = m_ObjMgr->GetVtxInfo(L"Map_Floor");
		int number = m_ObjMgr->GetVtxNumber(L"Map_Floor");
		MapCheckThreadLoop(number, vtx);
		//EnqueueMousePickingFunc();
	}
	if (g_bHitFloor) {
		m_IsRunning = true;
		g_bHitFloor = false;
		m_IsTurning = true;
	}

	if (m_IsRunning)
	{
		float speed = 2.5f;
		printf("MouseHitPoint : %.2f,%.2f,%.2f\n",
			g_MouseHitPoint.x, g_MouseHitPoint.y, g_MouseHitPoint.z);
		if (m_IsTurning) {
			m_IsTurning = TurnSlowly(&g_MouseHitPoint);
		}

		// Update_vPos_ByDestPoint : mouseHitPos와 거리가 작으면 false 리턴
		m_IsRunning = Update_vPos_ByDestPoint(&g_MouseHitPoint, speed);
		if (!m_IsRunning)
			m_pAnimationCtrl->BlendAnimationSet("Stand");
	}
}

void CZealot::QWERControl()
{

	if (CheckPushKeyOneTime(VK_1)) {
		m_pAnimationCtrl->BlendAnimationSet("Walk");
	}
	if (CheckPushKeyOneTime(VK_2)) {
		m_pAnimationCtrl->DisplayAniSetNameOnConsole();
	}
	if (CheckPushKeyOneTime(VK_3)) {
		m_pAnimationCtrl->BlendAnimationSet("Attack_02");
	}
	if (CheckPushKeyOneTime(VK_3)) {
		m_pAnimationCtrl->BlendAnimationSet("Attack_01");
	}
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

float CZealot::lerp(float p1, float p2, float d)
{
	return (1-d) * p1 + d * p2;
}
