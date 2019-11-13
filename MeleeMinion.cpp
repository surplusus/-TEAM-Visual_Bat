#include "BaseInclude.h"
#include "MeleeMinion.h"
#include <random>
#include "EventMgr.h"
#include "ObjectColider.h"
#include "BoundingBox.h"
#include "ParticleMgr.h"
#include "CollisionMgr.h"

CMeleeMinion::CMeleeMinion()
{
	GET_SINGLE(EventMgr)->Subscribe(this, &CMeleeMinion::StopAttackWhenEnemyDie);
}


CMeleeMinion::~CMeleeMinion()
{
	GET_SINGLE(EventMgr)->Unsubscribe(this, &CMeleeMinion::OperateOnPhysicalAttackEvent);
	GET_SINGLE(EventMgr)->Unsubscribe(this, &CMeleeMinion::StopAttackWhenEnemyDie);
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

		m_StatusInfo.fHP = 100.f;
		m_StatusInfo.fBase_Attack = 10.f;
		m_StatusInfo.fMoveSpeed = 0.1f;
		m_StatusInfo.fAttackRange = 2.f;
	}

	UpdateWorldMatrix();
	SetUpPickingShere(1.f);

	m_bBeginProgressRender = true;
	return S_OK;
}

void CMeleeMinion::Progress()
{
	if (!m_bBeginProgressRender)
		return;
	//UpdateColliderList();

	if (D3DXVec3Length(&(m_Info.vPos - m_NextPoint)) <= 3.f)
		ChangeNextPoint();

	SearchNearBy();

	{	//<< : Behavior Tree
		m_pBehavior->UpdateBlackBoard();
		m_pBehavior->Run();
	}

	m_pCollider->Update(m_Info.vPos);
	CMinion::UpdateWorldMatrix();
	if (m_pBehavior->m_BlackBoard->getBool("Alive") == true)
		m_pAnimationCtrl->FrameMove(m_MeshName, g_fDeltaTime);
}

void CMeleeMinion::Render()
{
	if (!m_bBeginProgressRender)
		return;

	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), m_MeshName);
	Render_PickingShere();	// 문제가 있음
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
	D3DXVECTOR3 mypos = *m_SphereForPick.vpCenter;
	float distFrom = D3DXVec3Length(&(mypos - evt->m_vecAttackFrom));
	float distAt = D3DXVec3Length(&(mypos - evt->m_vecAttackTo));
	// 근접 공격 피격 거리 stSphere.fRadius로 퉁쳤음
	if (distAt <= 1.f) {
		m_pBehavior->m_BlackBoard->setBool("Beaten", true);
		m_pBehavior->m_BlackBoard->setFloat("AttackFrom", distFrom);
		// status 반영
		m_StatusInfo.fHP -= evt->m_infoDemage.fBase_Attack;
		m_StatusInfo.PrintAll();
		cout << "- minion 정보 -\n";
	}
}

void CMeleeMinion::SearchNearBy()
{
	vector<SPHERE*> vEnemyNear;
	// 어그로 당하는 범위 퉁쳐서 4.f
	GET_SINGLE(CCollisionMgr)->IsCloseSphereInRadius(&vEnemyNear, this, &D3DXVECTOR3(m_Info.vPos), 4.f);
	if (vEnemyNear.size() != 0)
	{
		float dist = 100000.f;
		for (size_t i = 0; i < vEnemyNear.size(); i++)
		{
			float newdist = D3DXVec3Length(&(m_Info.vPos - *vEnemyNear[i]->vpCenter));
			if (dist < newdist)
			{
				m_sphereTarget = vEnemyNear[i];
				dist = newdist;
			}
		}
	}
}

void CMeleeMinion::UpdateColliderList()
{
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

void CMeleeMinion::StopAttackWhenEnemyDie(OBJDIEEVENT * evt)
{

}
