#include "BaseInclude.h"
#include "BehaviorMeleeMinion.h"
#include "MeleeMinion.h"
#include "EventMgr.h"
#include "SoundMgr.h"
#include "CollisionMgr.h"
#include "PickingSphereMgr.h"

MeleeMinionBT::MinionBTHandler::MinionBTHandler(CMeleeMinion* pInst)
	: m_pInst(pInst)
{
	for (int i = 0; i < SEQUENCE_END; ++i)
		m_vSequnece.emplace_back(make_shared<Sequence>(m_BlackBoard.get()));
	for (int i = 0; i < SELECTOR_END; ++i)
		m_vSelector.emplace_back(make_shared<Selector>(m_BlackBoard.get()));

	{	// vecter에 task와 decorator 보관 & decorator에 task 매달기
		InsertDecorate<WhenFloatLow>(InsertTask<MinionDeath>(), "fHP", 0.f);
		InsertDecorate<WhenAlive>(InsertTask<MinionBeaten>());
		InsertDecorate<WhenFloatChecked>(InsertTask<MinionAttack>(), "TargetAt", "fAttackRange", true);
		InsertDecorate<WhenEnemyNear>(InsertTask<MinionAggressive>(), m_pInst, m_pInst->m_StatusInfo.fAttackRange);
		InsertDecorate<WhenAlive>(InsertTask<MinionNextPos>());
		InsertDecorate<WhenFloatAbove>(InsertTask<MinionRun>(), "Distance", D3DX_16F_EPSILON);
		InsertDecorate<WhenBoolOn>(InsertTask<MinionTurn>(), "Turn");
		InsertDecorate<WhenBoolOn>(InsertTask<MinionIdle>(), "QAction");
	}

	// Set Root
	m_Root = m_vSelector[SELECTOR_DEATH].get();
	MakeTree();
	SetUpBlackBoard();
}

MeleeMinionBT::MinionBTHandler::~MinionBTHandler()
{
	m_vSequnece.clear();
	m_vSelector.clear();
	m_vDecorator.clear();
	m_vTask.clear();
}

void MeleeMinionBT::MinionBTHandler::MakeTree()
{
	// Move Module
	{
		m_vSequnece[SEQUENCE_MOVE]->AddNode(m_vDecorator[TASK_RUN].get());
		m_vSequnece[SEQUENCE_MOVE]->AddNode(m_vDecorator[TASK_RUN].get());
		m_vSequnece[SEQUENCE_MOVE]->AddNode(m_vDecorator[TASK_TURN].get());
	}
	// Task를 BehaviorTree에 매단다
	{
		m_vSelector[SELECTOR_DEATH]->AddNode(m_vDecorator[TASK_DEATH].get());
		m_vSelector[SELECTOR_DEATH]->AddNode(m_vSequnece[SEQUENCE_LIFE].get());
		{
			m_vSequnece[SEQUENCE_LIFE]->AddNode(m_vDecorator[TASK_BEATEN].get());
			m_vSequnece[SEQUENCE_LIFE]->AddNode(m_vSelector[SELECTOR_FOLLOW].get());
			{
				m_vSelector[SELECTOR_FOLLOW]->AddNode(m_vDecorator[DECORATOR_AGGRESSIVE].get());
				{
					m_vSelector[SELECTOR_AGGRESSIVE]->AddNode(m_vDecorator[TASK_ATTACK].get());
					m_vSelector[SELECTOR_AGGRESSIVE]->AddNode(m_vSequnece[SEQUENCE_MOVE].get());
					{
						// Move Module
					}
				}
				m_vSelector[SELECTOR_FOLLOW]->AddNode(m_vSequnece[SEQUENCE_MOVE].get());
				{
					// Move Module
				}
			}
		}
	}
}

void MeleeMinionBT::MinionBTHandler::SetUpBlackBoard()
{
	{	// stStatusInfo
		m_BlackBoard->setFloat("fBase_Attack", m_pInst->m_StatusInfo.fBase_Attack);
		m_BlackBoard->setFloat("fMagic_Attack", m_pInst->m_StatusInfo.fMagic_Attack);
		m_BlackBoard->setFloat("fBase_Defence", m_pInst->m_StatusInfo.fBase_Defence);
		m_BlackBoard->setFloat("fMagic_Defence", m_pInst->m_StatusInfo.fMagic_Defence);
		m_BlackBoard->setFloat("fCriticalRatio", m_pInst->m_StatusInfo.fCriticalRatio);
		m_BlackBoard->setFloat("fMoveSpeed", m_pInst->m_StatusInfo.fMoveSpeed);
		m_BlackBoard->setFloat("fMana", m_pInst->m_StatusInfo.fMana);
		m_BlackBoard->setFloat("fHP", m_pInst->m_StatusInfo.fHP);
		m_BlackBoard->setFloat("fSkillTimeRatio", m_pInst->m_StatusInfo.fSkillTimeRatio);
		m_BlackBoard->setFloat("fAttackRange", m_pInst->m_StatusInfo.fAttackRange);
	}
	{	// Initialize (StatusInfo에 없는 내용)
		m_BlackBoard->setBool("Alive", true);
		m_BlackBoard->setBool("Beaten", false);
		m_BlackBoard->setFloat("AttackFrom", 1000.f);
		m_BlackBoard->setFloat("TargetAt", 1000.f);
		m_BlackBoard->setBool("Aggressive", false);
		m_BlackBoard->setFloat("Distance", D3DXVec3Length(&(m_pInst->GetInfo()->vPos - m_pInst->m_NextPoint)));
		m_BlackBoard->setBool("Turn", false);
	}
}

void MeleeMinionBT::MinionBTHandler::UpdateBlackBoard()
{
	STATUSINFO& Info = m_pInst->m_StatusInfo;

	{	// stStatusInfo
		m_BlackBoard->setFloat("fBase_Attack", Info.fBase_Attack);
		m_BlackBoard->setFloat("fMagic_Attack", Info.fMagic_Attack);
		m_BlackBoard->setFloat("fBase_Defence", Info.fBase_Defence);
		m_BlackBoard->setFloat("fMagic_Defence", Info.fMagic_Defence);
		m_BlackBoard->setFloat("fCriticalRatio", Info.fCriticalRatio);
		m_BlackBoard->setFloat("fMoveSpeed", Info.fMoveSpeed);
		m_BlackBoard->setFloat("fMana", Info.fMana);
		m_BlackBoard->setFloat("fHP", Info.fHP);
		m_BlackBoard->setFloat("fSkillTimeRatio", Info.fSkillTimeRatio);
		m_BlackBoard->setFloat("fAttackRange", Info.fAttackRange);
	}
}
void MeleeMinionBT::MinionAccessor::ChangeAnySet(string key)
{
	auto it = find(m_pInst->m_AniSetNameList.begin(), m_pInst->m_AniSetNameList.end(), key);
	if (it == m_pInst->m_AniSetNameList.end()) {
		cout << "그런 애니 또 없습니다." << '\n';
		return;
	}
	m_pInst->m_pAnimationCtrl->BlendAnimationSet(key);
}

bool MeleeMinionBT::WhenEnemyNear::Ask()
{
	vector<CObj*> vEnemyNear;
	// 어그로 당하는 범위 퉁쳐서 4.f
	D3DXVECTOR3 mypos = m_MyInst->GetInfo()->vPos;
	GET_SINGLE(CCollisionMgr)->IsCloseObjInRadius(&vEnemyNear, m_MyInst
		, &mypos, m_fSearchRange);
	if (vEnemyNear.size() != 0)
	{
		float dist = 100000.f;
		for (size_t i = 0; i < vEnemyNear.size(); ++i)
		{
			auto enemyinfo = *vEnemyNear[i]->GetInfo();
			float newdist = D3DXVec3Length(&(mypos - enemyinfo.vPos));
			if (dist < newdist)
			{
				GET_SINGLE(CPickingSphereMgr)->GetSphereByKeyOfCObjptr(&vEnemyNear[i], &m_spTarget);
				dist = newdist;
			}
		}
		m_MyInst->m_sphereTarget = m_spTarget;
		return true;
	}
	return false;
}


#pragma region 자식 TASK 정의
//////////// Death /////////////
void MeleeMinionBT::MinionDeath::Init()
{
	m_BlackBoard->setBool("Dying", true);
	ChangeAnySet("Death");
	auto obj = m_pInst;		auto pos = &m_pInst->m_Info.vPos;
	GET_SINGLE(EventMgr)->Publish(new OBJDIEEVENT(
		reinterpret_cast<void**>(&obj), reinterpret_cast<void**>(&pos)));
}
void MeleeMinionBT::MinionDeath::Do()
{
	++iCntAni;
	if (iCntAni == iSoundSec) {
		GET_SINGLE(SoundMgr)->PlayMinionSound(T_SOUND::ANNOUNCER_MinionDie);
	}
	if (iCntAni >= 170) {
		iCntAni = 0;
		m_status = TERMINATED;
	}
}
void MeleeMinionBT::MinionDeath::Terminate()
{
	m_BlackBoard->setBool("Dying", false);
	m_BlackBoard->setBool("Alive", false);
}
//////////// Beaten /////////////
void MeleeMinionBT::MinionBeaten::Do()
{
	if (m_BlackBoard->getBool("Beaten")) {
		m_status = TERMINATED;
	}
}
void MeleeMinionBT::MinionBeaten::Terminate()
{
	m_BlackBoard->setBool("Beaten", false);
}
//////////// Attack /////////////
void MeleeMinionBT::MinionAttack::Init()
{
	ChangeAnySet("Attack1");
}
void MeleeMinionBT::MinionAttack::Do()
{
	++iCntAni;
	if (iCntAni == 24) {
		STATUSINFO infoDemage; infoDemage.fBase_Attack = m_pInst->m_StatusInfo.fBase_Attack;
		GET_SINGLE(SoundMgr)->PlayMinionSound(T_SOUND::ANNOUNCER_MinionAttack);
		GET_SINGLE(EventMgr)->Publish(new PHYSICALATTACKEVENT(&D3DXVECTOR3(m_pInst->m_Info.vPos)
			, &D3DXVECTOR3(*m_pInst->m_sphereTarget->vpCenter), &infoDemage));
	}
	// 애니메이션 끝나는 시점 60:20 = iCntAni:20
	if (iCntAni >= 48) {
		iCntAni = 0;
		m_status = TERMINATED;
	}
}
void MeleeMinionBT::MinionAttack::Terminate()
{
	m_BlackBoard->setBool("OnTarget", false);
	m_status = INVALID;
}
//////////// Aggressive /////////////
void MeleeMinionBT::MinionAggressive::Init()
{
	m_BlackBoard->setBool("Aggressive", false);
	if (m_pInst->m_sphereTarget != spEnemy) {
		spEnemy = m_pInst->m_sphereTarget;
		bNewTarget = true;
	}
}
void MeleeMinionBT::MinionAggressive::Do()
{
	D3DXVECTOR3 vecPickPos = *spEnemy->vpCenter;

	float dist = D3DXVec3Length(&(m_pInst->m_Info.vPos - vecPickPos));
	m_BlackBoard->setFloat("TargetAt", dist);
	m_pInst->m_pBehavior->m_vSelector[SELECTOR_AGGRESSIVE]->Run();

	if (m_BlackBoard->getBool("OnTarget") == false)
		m_status = TERMINATED;
}
void MeleeMinionBT::MinionAggressive::Terminate()
{
	spEnemy = nullptr;
	bNewTarget = false;
}
//////////// NextPos /////////////
void MeleeMinionBT::MinionNextPos::Do()
{
	float dist = D3DXVec3Length(&(m_pInst->m_Info.vPos - m_pInst->m_NextPoint));
	if (dist <= 0.5f)
		m_status = TERMINATED;
}
void MeleeMinionBT::MinionNextPos::Terminate()
{
	++m_Idx;
	m_Idx %= m_pInst->m_vNextPoints.size() - 1;
	m_pInst->m_NextPoint = m_pInst->m_vNextPoints[m_Idx];
	m_status = INVALID;
}
//////////// Run /////////////
void MeleeMinionBT::MinionRun::Init()
{
	ChangeAnySet("Run");
	m_BlackBoard->setBool("Turn", true);
	if (m_BlackBoard->getBool("OnTarget") == true)
		m_vecNextPos = *m_pInst->m_sphereTarget->vpCenter;
	else
		m_vecNextPos = m_pInst->m_NextPoint;
}
void MeleeMinionBT::MinionRun::Do()
{
	m_BlackBoard->setFloat("Distance", D3DXVec3Length(&(m_vecNextPos - m_pInst->m_Info.vPos)));
	bool bDest = m_pInst->Update_vPos_ByDestPoint(&m_vecNextPos, m_BlackBoard->getFloat("fMoveSpeed"));
	if (!bDest) {
		m_status = TERMINATED;
	}
}
void MeleeMinionBT::MinionRun::Terminate()
{
	m_status = INVALID;
}
//////////// Turn /////////////
void MeleeMinionBT::MinionTurn::Init()
{
	if (m_BlackBoard->getBool("OnTarget") == true)
		m_vecNextPos = *m_pInst->m_sphereTarget->vpCenter;
	else
		m_vecNextPos = m_pInst->m_NextPoint;
}
void MeleeMinionBT::MinionTurn::Do()
{
	//m_BlackBoard->setFloat("Direction", m_pInst->m_fAngle[ANGLE_Y]);
	bool bTurning = m_pInst->TurnSlowly(&m_vecNextPos);
	if (!bTurning)
		m_status = INVALID;
}
void MeleeMinionBT::MinionTurn::Terminate()
{
	m_BlackBoard->setBool("Turn", false);
}
//////////// Idle /////////////
void MeleeMinionBT::MinionIdle::Init()
{
	ChangeAnySet("Idle");
}
void MeleeMinionBT::MinionIdle::Do()
{
	m_status = INVALID;
}
#pragma endregion

