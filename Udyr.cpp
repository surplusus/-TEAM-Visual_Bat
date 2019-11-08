#include "BaseInclude.h"
#include "Udyr.h"
#include "SoundMgr.h"
#include "PickingSphereMgr.h"
#include "EventMgr.h"
#include "CollisionMgr.h"
#include "ObjectColider.h"
#include "BoundingBox.h"
#include "ParticleMgr.h"
using namespace UdyrBT;

CUdyr::CUdyr()
	: m_pBehavior(nullptr)
{
}

CUdyr::~CUdyr()
{
	Release();
}

void CUdyr::Release()
{
	SAFE_RELEASE(m_pMeshSphere);
	SAFE_RELEASE(m_pAnimationCtrl);
	SAFE_DELETE(m_pBehavior);
}

void CUdyr::WriteOnBlackBoard(string sKey, bool bValue)
{
	m_pBehavior->m_BlackBoard->setBool(sKey, bValue);
}

void CUdyr::WriteOnBlackBoard(string sKey, int iValue)
{
	m_pBehavior->m_BlackBoard->setInt(sKey, iValue);
}

void CUdyr::WriteOnBlackBoard(string sKey, float fValue)
{
	m_pBehavior->m_BlackBoard->setFloat(sKey, fValue);
}

void CUdyr::WriteOnBlackBoard(string sKey, double llValue)
{
	m_pBehavior->m_BlackBoard->setDouble(sKey, llValue);
}

void CUdyr::WriteOnBlackBoard(string sKey, string sValue)
{
	m_pBehavior->m_BlackBoard->setString(sKey, sValue);
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
	{	//<< : SetUp StatusInfo
		m_stStatusInfo.fHP = 100.f;
		m_stStatusInfo.fBase_Attack = 10.f;
		m_stStatusInfo.fMoveSpeed = 1.f;
	}
	{	//<< : SetUp m_AniSetNameList;
		SetUpAniSetNameList();
	}
	{	//<< : Collision
		m_pCollider = new CObjectColider(this);
		m_pCollider->SetUp(m_Info, 1.0f, new CBoundingBox);
		m_ColiderList.push_back(m_pCollider);
		GET_SINGLE(CParticleMgr)->InsertColList(this, &m_ColiderList);
		GET_SINGLE(CCollisionMgr)->InsertColistion(this, &m_ColiderList);
		GET_SINGLE(EventMgr)->Subscribe(this, &CUdyr::OperateOnPaticleCollisionEvent);
	}
	{	//<< : PickingSphere
		//SetUpPickingShere(1.f);
		GET_SINGLE(CPickingSphereMgr)->AddSphere(this, m_pCollider->GetSphere());
		GET_SINGLE(EventMgr)->Subscribe(this, &CUdyr::OperateOnFindPickingSphere);
	}
	{	//<< : Behavior Tree
		m_pBehavior = new UdyrBTHandler(this);
	}
	return S_OK;
}

void CUdyr::Progress()
{
	{
		//if (CheckPushKeyOneTime(VK_1))
		//	m_stStatusInfo.PrintAll();
		//if (CheckPushKeyOneTime(VK_2))
		//	m_stStatusInfo.fHP -= 100.f;
		//if (CheckPushKeyOneTime(VK_3)) {
		//	for (size_t i = 0; i < m_AniSetNameList.size(); i++)
		//		cout << "Ani Num " << i << " : " << m_AniSetNameList[i] << '\n';
		//}
		//if (CheckPushKeyOneTime(VK_4))
		//	m_stStatusInfo.fMoveSpeed += 0.1f;
		//if (CheckPushKeyOneTime(VK_5)) {
		//	bool b = m_pBehavior->GetBlackBoard().getBool("Die");
		//	m_pBehavior->GetBlackBoard().setBool("Die", !b);
		//}
	}

	
	{	//<< : Behavior Tree
		m_pBehavior->UpdateBlackBoard();
		m_pBehavior->Run();
	}
	m_pCollider->Update(m_Info.vPos);
	CChampion::UpdateWorldMatrix();
	if (!m_pBehavior->GetBlackBoard().getBool("ChampIsOver"))
		m_pAnimationCtrl->FrameMove(L"Udyr", g_fDeltaTime);
}

void CUdyr::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), L"Udyr");
	//Render_PickingShere();
}

void CUdyr::ChangeAniSetByKey(string key)
{
	auto it = find(m_AniSetNameList.begin(), m_AniSetNameList.end(), key);
	if (it == m_AniSetNameList.end()) {
		cout << "그런 애니 또 없습니다." << '\n';
		return;
	}

	m_pAnimationCtrl->BlendAnimationSet(key);
}

void CUdyr::SetUpAniSetNameList()
{
	m_pAnimationCtrl->GetAnimationNames(m_AniSetNameList);
}

void CUdyr::OperateOnFindPickingSphere(PICKSPHEREEVENT * evt)
{
	WriteOnBlackBoard("OnTarget", true);
	m_MouseHitPoint = evt->m_pObj->GetInfo()->vPos;
	if (fabs(m_MouseHitPoint.x) < 10000.f || fabs(m_MouseHitPoint.y) < 10000.f || fabs(m_MouseHitPoint.z) < 10-00.f)
		WriteOnBlackBoard("HasCoord", true);
	//m_pTargetObj = evt->m_pObj;
}

void CUdyr::OperateOnPaticleCollisionEvent(COLLISIONEVENT * evt)
{
	//m_stStatusInfo -= dynamic_cast<CChampion*>(evt->)->m_StatusInfo;
}


//void CUdyr::MouseControl()
//{
//	{	// 방향전환
//		bool bPicked = false;
//		if (CheckMouseButtonDownOneTime(MOUSEBUTTON0)) {
//			bPicked = SearchPickingPointInHeightMap(GetVertexNumInHeightMap(), GetVertexInHeightMap());
//		}
//
//		if (bPicked) {
//			m_iStateFlag = 0;
//			m_iStateFlag |= 1 << STATETYPE_RUN;
//			m_iStateFlag |= 1 << STATETYPE_TURNING;
//		}
//
//	}
//	{	// 적 타켓팅(Sphere 픽킹)
//		if (CheckMouseButtonDownOneTime(MOUSEBUTTON2)) {
//			m_iStateFlag = 0;
//			m_iStateFlag |= 1 << STATETYPE_ATTACK;
//		}
//	}
//	{	// Sphere 픽킹
//		if (CheckMouseButtonDownOneTime(MOUSEBUTTON2)) {
//
//			SPHERE* spherePicked = nullptr;
//			bool bPickSphere = GET_SINGLE(CPickingSphereMgr)->GetSpherePicked(this, &spherePicked);
//			if (bPickSphere) {
//				spherePicked->isPicked = !spherePicked->isPicked;
//				m_iStateFlag = 0;
//				m_iStateFlag |= 1 << STATETYPE_AGRESSIVE;
//			}
//
//		}
//	}
//}
//
//void CUdyr::QWERControl()
//{
//	static int iAniIndex = 0;
//	if (CheckPushKeyOneTime(VK_0)) {	// 애니메이션 정보 콘솔 출력
//		m_pAnimationCtrl->DisplayAniSetNameOnConsole();
//	}
//	if (CheckPushKeyOneTime(VK_Q)) {
//		m_iStateFlag = (1 << STATETYPE_IDLE);
//		//m_pAnimationCtrl->BlendAnimationSet("Attack_Left");
//		//GET_SINGLE(SoundMgr)->PlayEffectSound("Udyr1");
//	}
//	if (CheckPushKeyOneTime(VK_W)) {
//		//m_pAnimationCtrl->BlendAnimationSet("Idle");
//		//GET_SINGLE(SoundMgr)->PlayEffectSound("Udyr2");
//	}
//
//	// sound check
//	//if (CheckPushKeyOneTime(VK_1))
//	//	GET_SINGLE(SoundMgr)->PlayUdyrSound(T_SOUND::Udyr_Attack_Left);

//void CUdyr::ControlFlag()
//{
//	int num, idx;
//	// 비트 값 확인
//	bool r1 = ((num & (1 << idx)) != 0);
//	// 비트 값만 채워넣기
//	int r2 = (num | (1 << idx));
//	// 비트 값만 삭제하기
//	int r3 = (num & ~(1 << idx));
//	// 비트 값만 켜고 나머지 전부 삭제하기
//	int f4 = (1 << idx);
//
//}
//#pragma endregion
