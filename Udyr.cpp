#include "BaseInclude.h"
#include "Udyr.h"
#include "SoundMgr.h"
#include "PickingSphereMgr.h"
#include "EventMgr.h"
#include "ColitionMgr.h"
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
		//INFO pInfo = m_Info;
		m_pCollider->SetUp(m_Info, 1.0f, new CBoundingBox);
		m_ColiderList.push_back(m_pCollider);
		GET_SINGLE(CParticleMgr)->InsertColList(this, &m_ColiderList);
		GET_SINGLE(CColitionMgr)->InsertColistion(this, &m_ColiderList);
		GET_SINGLE(EventMgr)->Subscribe(this, &CUdyr::PaticleCollisionEvent);
	}
	{	//<< : PickingSphere
		//SetUpPickingShere(1.f);
		GET_SINGLE(CPickingSphereMgr)->AddSphere(this, &m_pCollider->GetSphere());
		GET_SINGLE(EventMgr)->Subscribe(this, &CUdyr::OnFindPickingSphere);
	}
	{	//<< : Behavior Tree
		m_pBehavior = new UdyrBTHandler;
		m_pBehavior->AddTask(TASK_DEATH, [this]() {this->ChangeAniSetByKey("Run"); });
		m_pBehavior->MakeTree();
		m_pBehavior->SetUpBlackBoard();
	}
	return S_OK;
}

void CUdyr::Progress()
{
	if (CheckPushKeyOneTime(VK_SPACE))
		m_stStatusInfo.PrintAll();

	{	//<< : Behavior Tree
		UpdateBlackBoard();
		m_pBehavior->Run();
	}
	m_pCollider->Update(m_Info.vPos);
	CChampion::UpdateWorldMatrix();
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

void CUdyr::OnFindPickingSphere(PICKSPHEREEVENT * evt)
{
	//m_pTargetObj = evt->m_pObj;
}

void CUdyr::PaticleCollisionEvent(COLLISIONEVENT * evt)
{
	m_pBehavior->m_BlackBoard->setBool("OnCollision", true);
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
//	//if (CheckPushKeyOneTime(VK_2))
//	//	GET_SINGLE(SoundMgr)->PlayUdyrSound(T_SOUND::Udyr_Idle);
//	//if (CheckPushKeyOneTime(VK_3))
//	//	GET_SINGLE(SoundMgr)->PlayUdyrSound(T_SOUND::Udyr_Search);
//	//if (CheckPushKeyOneTime(VK_4))
//	//	GET_SINGLE(SoundMgr)->PlayUdyrSound(T_SOUND::Udyr_Run);
//	//if (CheckPushKeyOneTime(VK_5))
//	//	GET_SINGLE(SoundMgr)->PlayUdyrSound(T_SOUND::Udyr_Taunt);
//	//if (CheckPushKeyOneTime(VK_6))
//	//	GET_SINGLE(SoundMgr)->PlayUdyrSound(T_SOUND::Udyr_Dance);
//	//if (CheckPushKeyOneTime(VK_7))
//	//	GET_SINGLE(SoundMgr)->PlayUdyrSound(T_SOUND::Udyr_Death);
//}
//
//#pragma region STATE FUNC
//bool CUdyr::Func1_IDLE()
//{
//	m_pAnimationCtrl->BlendAnimationSet("Idle");
//	
//	return true;
//}
//
//bool CUdyr::Func2_ATTACK()
//{
//	return true;
//}
//
//bool CUdyr::Func3_RUN()
//{
//	m_pAnimationCtrl->BlendAnimationSet("Run");
//	
//	float speed = 2.5f;
//	//if (m_vStateFlag[STATETYPE_TURNING])
//	//	m_vStateFlag[STATETYPE_TURNING] = TurnSlowly(&m_MouseHitPoint);
//	//m_vStateFlag[STATETYPE_RUN] = Update_vPos_ByDestPoint(&m_MouseHitPoint, speed);
//	//if (!m_vStateFlag[STATETYPE_RUN])
//	//	m_vStateFlag[STATETYPE_IDLE] = true;
//	if ((m_iStateFlag & (1 << STATETYPE_TURNING)) != 0)
//		m_iStateFlag = (Update_vPos_ByDestPoint(&m_MouseHitPoint, speed)) ? (m_iStateFlag |= (1 << STATETYPE_RUN)) : (m_iStateFlag &= ~(1 << STATETYPE_RUN));
//		//m_iStateFlag = (TurnSlowly(&m_pTargetObj->GetInfo()->vPos)) ? (m_iStateFlag |= (1 << STATETYPE_TURNING)) : (m_iStateFlag &= ~(1 << STATETYPE_TURNING));
//
//	m_iStateFlag = (Update_vPos_ByDestPoint(&m_MouseHitPoint, speed)) ? (m_iStateFlag |= (1 << STATETYPE_RUN)) : (m_iStateFlag &= ~(1 << STATETYPE_RUN));
//	//m_iStateFlag = (Update_vPos_ByDestPoint(&m_pTargetObj->GetInfo()->vPos, speed)) ? (m_iStateFlag |= (1 << STATETYPE_RUN)) : (m_iStateFlag &= ~(1 << STATETYPE_RUN));
//	if (!(m_iStateFlag & (1 << STATETYPE_RUN)))
//		m_iStateFlag = 1 << STATETYPE_IDLE;
//	return true;
//}
//
//bool CUdyr::Func4_AGRESSIVE()
//{
//	m_pAnimationCtrl->BlendAnimationSet("Run");
//	m_iStateFlag &= ~(1 << STATETYPE_AGRESSIVE);
//	m_iStateFlag |= (1 << STATETYPE_RUN);
//	float speed = 2.5f;
//	//if (m_pTargetObj != nullptr)
//		m_iStateFlag = (TurnSlowly(&m_pTargetObj->GetInfo()->vPos)) ? (m_iStateFlag |= (1 << STATETYPE_TURNING)) : (m_iStateFlag &= ~(1 << STATETYPE_TURNING));
//
//	m_iStateFlag = (Update_vPos_ByDestPoint(&m_pTargetObj->GetInfo()->vPos, speed)) ? (m_iStateFlag |= (1 << STATETYPE_RUN)) : (m_iStateFlag &= ~(1 << STATETYPE_RUN));
//	//if (!(m_iStateFlag & (1 << STATETYPE_AGRESSIVE))) {
//	//	m_iStateFlag = 0;
//	//	m_iStateFlag = 1 << STATETYPE_IDLE;
//	//}
//
//	return true;
//}
//
//void CUdyr::ProgressStateFunc()
//{
//	// EnqueueStateFunc
//	int i = m_iStateFlag;
//	int cnt = 0;
//	FUNCSTATE func;
//	while (i >=1)
//	{
//		if (cnt >= m_vStateFunc.size())
//			break;
//		if (i & 1) {
//			m_queStateFunc.push(m_vStateFunc[cnt]);
//		}
//		cnt++;
//		i = (i >> 1);
//	}
//
//	// Play StateFunc Enqueued
//	while (!m_queStateFunc.empty()) {
//		func = m_queStateFunc.front();
//		m_queStateFunc.pop();
//		bool result = func();
//	}
//}
//
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

void CUdyr::UpdateBlackBoard()
{
	if (CheckMouseButtonDownOneTime(MOUSEBUTTON0)) {
		m_pBehavior->GetBlackBoard().setBool("Click", true);
	}
	m_pBehavior->GetBlackBoard().setFloat("HP", m_stStatusInfo.fHP);
	m_pBehavior->GetBlackBoard().setFloat("Base_Attack", m_stStatusInfo.fBase_Attack);
	m_pBehavior->GetBlackBoard().setFloat("MoveSpeed", m_stStatusInfo.fMoveSpeed);
}
