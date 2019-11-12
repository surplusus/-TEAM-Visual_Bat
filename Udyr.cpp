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
	GET_SINGLE(EventMgr)->Unsubscribe(this, &CUdyr::OperateOnFindPickingSphere);
	GET_SINGLE(EventMgr)->Unsubscribe(this, &CUdyr::OperateOnPhysicalAttackEvent);
	SAFE_RELEASE(m_pAnimationCtrl);
	SAFE_DELETE(m_pBehavior);
	SAFE_DELETE(m_pCollider);
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

bool CUdyr::IsEnemyNearInSphere(float fRadius)
{
	vector<SPHERE*> vCloseEnemy;
	bool result = GET_SINGLE(CCollisionMgr)->IsCloseSphereInRadius(&vCloseEnemy, this, &m_Info.vPos, fRadius);
	auto iter = find(vCloseEnemy.begin(), vCloseEnemy.end(), m_sphereTarget);
	if (iter != vCloseEnemy.end())
		WriteOnBlackBoard("Attack", true);
	
	return result;
}

void CUdyr::UpdatePickPointToEnemySphereCenter()
{
	float distance = D3DXVec3Length(&(m_Info.vPos - m_MouseHitPoint));
	WriteOnBlackBoard("TargetAt", distance);
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
		m_StatusInfo.fHP = 100.f;
		m_StatusInfo.fBase_Attack = 10.f;
		m_StatusInfo.fMoveSpeed = 4.f;
		m_StatusInfo.fAttackRange = 2.f;
	}
	{	//<< : SetUp m_AniSetNameList;
		SetUpAniSetNameList();
	}
	{	//<< : Collision
		m_pCollider = new CObjectColider(this);
		m_pCollider->SetUp(m_Info, 1.0f, new CBoundingBox);
		m_ColliderList.push_back(m_pCollider);
		auto obj = this;		auto list= &m_ColliderList;
		GET_SINGLE(EventMgr)->Publish(new INSERTCOLLIDEREVENT(
			reinterpret_cast<void**>(&obj), reinterpret_cast<void**>(&list)));
	}
	{	//<< : PickingSphere
		//SetUpPickingShere(1.f);
		GET_SINGLE(CPickingSphereMgr)->AddSphere(this, m_pCollider->GetSphere());
		GET_SINGLE(EventMgr)->Subscribe(this, &CUdyr::OperateOnFindPickingSphere);
	}
	{	//<< : Behavior Tree
		m_pBehavior = new UdyrBTHandler(this);

		GET_SINGLE(EventMgr)->Subscribe(this, &CUdyr::OperateOnPhysicalAttackEvent);
	}
	return S_OK;
}

void CUdyr::Progress()
{
	UpdateColliderList();

	{	// test
		if (CheckPushKeyOneTime(VK_N))
			m_pAnimationCtrl->DisplayAniSetNameOnConsole();
		if (CheckPushKeyOneTime(VK_1)) {
			m_StatusInfo.PrintAll();
			cout << "OnTarget : " << m_pBehavior->m_BlackBoard->getBool("OnTarget") << '\n';
		}
		if (CheckPushKeyOneTime(VK_2)) {
			STATUSINFO info; info.fBase_Attack = 25.f;
			cout << "Beaten : " << info.fBase_Attack << endl;
			GET_SINGLE(EventMgr)->Publish(new PHYSICALATTACKEVENT(&D3DXVECTOR3(m_Info.vPos), &info));
			m_StatusInfo.fHP -= 25.f;
		}
		if (CheckPushKeyOneTime(VK_4))
			m_StatusInfo.fMoveSpeed += 0.1f;
		if (CheckPushKeyOneTime(VK_5))
			m_StatusInfo.fMoveSpeed -= 0.1f;
		if (CheckPushKeyOneTime(VK_6))
			m_StatusInfo.fHP = 0.f;

	}
	// Collider Update
	if (m_pCollider != nullptr)
		m_pCollider->Update(m_Info.vPos);
	else
		m_StatusInfo.fHP = 0.f;


	{
		DoOnMouseLButton();
		DoOnMouseRButton();
	}
	{	//<< : Behavior Tree
		m_pBehavior->UpdateBlackBoard();
		m_pBehavior->Run();
		//cout << "Onterget : " << (bool)m_pBehavior->m_BlackBoard->getBool("OnTarget")
		//	<< " HasCoord :  " << (bool)m_pBehavior->m_BlackBoard->getBool("HasCoord") << endl;
	}
	//m_pCollider->Update(m_Info.vPos);
	CChampion::UpdateWorldMatrix();
	if (m_pBehavior->GetBlackBoard().getBool("Alive") == true)
		m_pAnimationCtrl->FrameMove(L"Udyr", g_fDeltaTime);
}

void CUdyr::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), L"Udyr");
	//Render_PickingShere();
}

const UdyrBT::UdyrBTHandler * CUdyr::GetBehaviorTree()
{
	return m_pBehavior;
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

void CUdyr::DoOnMouseLButton()
{
	if (CheckMouseButtonDown(MOUSEBUTTON0))
	{
		if (GET_SINGLE(CPickingSphereMgr)->GetSpherePicked(this, &m_sphereTarget))
		{
			WriteOnBlackBoard("OnTarget", true);
			float distance = D3DXVec3Length(&(m_Info.vPos - m_MouseHitPoint));
			WriteOnBlackBoard("Distance", distance);
			return;
		}
		else
		{
			WriteOnBlackBoard("OnTarget", false);
			WriteOnBlackBoard("Distance", 0.f);
		}

		if (SearchPickingPointInHeightMap(GetVertexNumInHeightMap(), GetVertexInHeightMap()))
		{
			WriteOnBlackBoard("HasCoord", true);
			float distance = D3DXVec3Length(&(m_Info.vPos - m_MouseHitPoint));
			WriteOnBlackBoard("Distance", distance);
			//m_MouseHitPoint = /////m_MouseHitPoint 로직이 SearchPickingPointInHeightMap안에 있음
		}
		else
		{
			WriteOnBlackBoard("HasCoord", false);
		}
	}
}

void CUdyr::DoOnMouseRButton()
{

}

void CUdyr::OperateOnFindPickingSphere(PICKSPHEREEVENT * evt)
{
	m_MouseHitPoint = evt->m_pObj->GetInfo()->vPos;
	//m_pTargetObj = evt->m_pObj;
}

void CUdyr::OperateOnPaticleCollisionEvent(COLLISIONEVENT * evt)
{
	
	m_pBehavior->m_BlackBoard->setBool("Beaten", true);
	//m_StatusInfo -= dynamic_cast<CChampion*>(evt->)->m_StatusInfo;
}

void CUdyr::OperateOnPhysicalAttackEvent(PHYSICALATTACKEVENT * evt)
{
	SPHERE stSphere = *m_pCollider->GetSphere();
	D3DXVECTOR3 distance = *stSphere.vpCenter - evt->m_vecAttackPos;
	float distFrom = D3DXVec3Length(&distance);
	// 근접 공격 피격 거리 stSphere.fRadius로 퉁쳤음
	if (distFrom <= stSphere.fRadius) {
		m_pBehavior->m_BlackBoard->setBool("Beaten", true);
		m_pBehavior->m_BlackBoard->setFloat("AttackFrom", distFrom);
	}
}

void CUdyr::QWERControl()
{
	//if (CheckPushKeyOneTime(VK_Q)) {
	//	WriteOnBlackBoard("QAction", true);
	//}
	//if (CheckPushKeyOneTime(VK_W)) {
	//	WriteOnBlackBoard("WAction", true);
	//}
	//if (CheckPushKeyOneTime(VK_E)) {
	//	WriteOnBlackBoard("EAction", true);
	//}
	//if (CheckPushKeyOneTime(VK_R)) {
	//	WriteOnBlackBoard("RAction", true);
	//}
	// sound check
	//if (CheckPushKeyOneTime(VK_1))
	//	GET_SINGLE(SoundMgr)->PlayUdyrSound(T_SOUND::Udyr_Attack_Left);
}

void CUdyr::UpdateColliderList()
{
	// 아직 안씀
	list<ColiderComponent*>::iterator iter = m_ColliderList.begin();
	for (iter; iter != m_ColliderList.end();)
	{
		if ((*iter)->GetStateCol())
		{
			iter = m_ColliderList.erase(iter);
		}
		else iter++;
	}
}

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
