#include "BaseInclude.h"
#include "MeleeMinion.h"
#include <random>
#include "EventMgr.h"
#include "ObjectColider.h"
#include "BoundingBox.h"
#include "ParticleMgr.h"

CMeleeMinion::CMeleeMinion()
{
}


CMeleeMinion::~CMeleeMinion()
{
	GET_SINGLE(EventMgr)->Unsubscribe(this, &CMeleeMinion::OperateOnPhysicalAttackEvent);
	Release();
}

HRESULT CMeleeMinion::Initialize()
{
	HRESULT res = CloneMesh(GetDevice(), m_MeshName, &m_pAnimationCtrl);
	SetUpAniSetNameList();
	if (!m_pAnimationCtrl)
		return S_FALSE;
	m_pAnimationCtrl->SetAnimationSet("Default_Action");
	m_pAnimationCtrl->GetAnimationNames(m_AniSetNameList);
	
	m_SortID = SORTID_LAST;
	m_Info.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, -1.0f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, -1.f);
	m_fSize = 1.f;
	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0.f);

	{	// waypoint set up
		m_vNextPoints.emplace_back(D3DXVECTOR3(15.f, 0.f, 15.f));
		m_vNextPoints.emplace_back(D3DXVECTOR3(-15.f, 0.f, 15.f));
		m_vNextPoints.emplace_back(D3DXVECTOR3(-15.f, 0.f, -15.f));
		m_vNextPoints.emplace_back(D3DXVECTOR3(15.f, 0.f, -15.f));

		m_NextPoint = m_vNextPoints[0];
	}
	{	//<< : Collision
		m_pCollider = new CObjectColider(this);
		m_pCollider->SetUp(m_Info, 1.0f, new CBoundingBox);
		m_ColliderList.push_back(m_pCollider);
		auto obj = this;		auto list = &m_ColliderList;
		GET_SINGLE(EventMgr)->Publish(new INSERTCOLLIDEREVENT(
			reinterpret_cast<void**>(&obj), reinterpret_cast<void**>(&list)));
	}
	{	//<< : Behavior Tree
		m_pBehavior = new MeleeMinionBT::MinionBTHandler(this);

		GET_SINGLE(EventMgr)->Subscribe(this, &CMeleeMinion::OperateOnPhysicalAttackEvent);
	}

	UpdateWorldMatrix();
	SetUpPickingShere(1.f);
	return S_OK;
}

void CMeleeMinion::Progress()
{
	if (D3DXVec3Length(&(m_Info.vPos - m_NextPoint)) <= 3.f)
		ChangeNextPoint();

	CMinion::UpdateWorldMatrix();
	if (m_pBehavior->m_BlackBoard->getBool("Alive") == true)
		m_pAnimationCtrl->FrameMove(m_MeshName, g_fDeltaTime);
}

void CMeleeMinion::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), m_MeshName);
	Render_PickingShere();
}

void CMeleeMinion::Release()
{
	SAFE_RELEASE(m_pAnimationCtrl);
	SAFE_DELETE(m_pBehavior);
}

void CMeleeMinion::SetPosition(const D3DXVECTOR3 * pos)
{
	m_Info.vPos.x = pos->x;
	m_Info.vPos.y = pos->y;
	m_Info.vPos.z = pos->z;
}

void CMeleeMinion::OperateOnPaticleCollisionEvent(COLLISIONEVENT * evt)
{
	m_pBehavior->m_BlackBoard->setBool("Beaten", true);
}

void CMeleeMinion::OperateOnPhysicalAttackEvent(PHYSICALATTACKEVENT * evt)
{
	SPHERE stSphere = *m_pCollider->GetSphere();
	D3DXVECTOR3 distance = *stSphere.vpCenter - evt->m_vecAttackPos;
	float distFrom = D3DXVec3Length(&distance);
	// 근접 공격 피격 거리 stSphere.fRadius로 퉁쳤음
	if (distFrom <= stSphere.fRadius) {
		m_pBehavior->m_BlackBoard->setBool("Beaten", true);
		m_pBehavior->m_BlackBoard->setFloat("AttackFrom", distFrom);
		// status 반영
		m_stStatusInfo.fHP -= evt->m_infoDemage.fBase_Attack;
		m_stStatusInfo.PrintAll();
		cout << "- minion 정보 -\n";
	}
}
