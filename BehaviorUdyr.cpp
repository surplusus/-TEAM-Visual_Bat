#include "BaseInclude.h"
#include "BehaviorUdyr.h"
#include "Udyr.h"
#include "SoundMgr.h"
#include "EventMgr.h"
#include "CollisionMgr.h"
#include "PickingSphereMgr.h"

UdyrBT::UdyrBTHandler::UdyrBTHandler(CUdyr * pInst)
	: m_pInst(pInst)
{
	for (int i = 0; i < SEQUENCE_END; ++i)
		m_vSequnece.emplace_back(make_shared<Sequence>(m_BlackBoard.get()));
	for (int i = 0; i < SELECTOR_END; ++i)
		m_vSelector.emplace_back(make_shared<Selector>(m_BlackBoard.get()));
	
	{	// vecter에 task와 decorator 보관 & decorator에 task 매달기
		InsertDecorate<WhenFloatLow>(InsertTask<UdyrDeath>(), "fHP", 0.f);
		InsertDecorate<WhenAlive>(InsertTask<UdyrBeaten>());
		InsertDecorate<WhenBoolOn>(InsertTask<UdyrOnTarget>(), "OnTarget");
		InsertDecorate<WhenBoolOn>(InsertTask<UdyrHasCoord>(), "HasCoord");
		InsertDecorate<WhenEnemyNear>(InsertTask<UdyrAggressive>(), m_pInst, m_pInst->m_StatusInfo.fAttackRange);
		InsertDecorate<WhenFloatChecked>(InsertTask<UdyrAttack>(), "TargetAt", "fAttackRange", true);
		InsertDecorate<WhenAlive>(InsertTask<UdyrIdle>());
		InsertDecorate<WhenBoolOn>(InsertTask<UdyrQAction>(), "QAction");
		InsertDecorate<WhenFloatAbove>(InsertTask<UdyrRun>(), "Distance", D3DX_16F_EPSILON);
		InsertDecorate<WhenBoolOn>(InsertTask<UdyrTurn>(), "Turn");
	}
	// Set Root
	m_Root = m_vSelector[SELECTOR_DEATH].get();
	MakeTree();
	SetUpBlackBoard();
}

UdyrBT::UdyrBTHandler::~UdyrBTHandler()
{
	m_vSequnece.clear();
	m_vSelector.clear();
	m_vDecorator.clear();
	m_vTask.clear();
}

void UdyrBT::UdyrBTHandler::MakeTree()
{
	// Move Module
	{
		m_vSequnece[SEQUENCE_MOVE]->AddNode(m_vDecorator[TASK_RUN].get());
		m_vSequnece[SEQUENCE_MOVE]->AddNode(m_vDecorator[TASK_TURN].get());
	}
	// Task를 BehaviorTree에 매단다
	{
		m_vSelector[SELECTOR_DEATH]->AddNode(m_vDecorator[TASK_DEATH].get());
		m_vSelector[SELECTOR_DEATH]->AddNode(m_vSequnece[SEQUENCE_LIFE].get());
		{
			m_vSequnece[SEQUENCE_LIFE]->AddNode(m_vDecorator[TASK_BEATEN].get());
			m_vSequnece[SEQUENCE_LIFE]->AddNode(m_vSelector[SELECTOR_INPUT].get());
			{
				m_vSelector[SELECTOR_INPUT]->AddNode(m_vSelector[SELECTOR_SKILL].get());
				{
					m_vSelector[SELECTOR_SKILL]->AddNode(m_vDecorator[TASK_QACTION].get());
				}
				m_vSelector[SELECTOR_INPUT]->AddNode(m_vDecorator[CONDITION_ONTARGET].get());// OnTarget
				{
					m_vSelector[SELECTOR_ENEMY]->AddNode(m_vDecorator[TASK_ATTACK].get());
					m_vSelector[SELECTOR_ENEMY]->AddNode(m_vSequnece[SEQUENCE_MOVE].get());
					{
						// Move Module
					}
				}
				m_vSelector[SELECTOR_INPUT]->AddNode(m_vDecorator[CONDITION_HASCOORD].get());// HasCoord
				{
					// Move Module
					// UdyrHasCoord 내부에 들어있음
				}
				m_vSelector[SELECTOR_INPUT]->AddNode(m_vSelector[SELECTOR_AGGRESSIVE].get());
				{
					m_vSelector[SELECTOR_AGGRESSIVE]->AddNode(m_vSequnece[SEQUENCE_MOVE].get());
					{
						// Move Module
					}
					m_vSelector[SELECTOR_AGGRESSIVE]->AddNode(m_vDecorator[TASK_IDLE].get());
				}
			}
		}
	}
}

void UdyrBT::UdyrBTHandler::SetUpBlackBoard()
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
		m_BlackBoard->setBool("QAction", false);
		m_BlackBoard->setBool("WAction", false);
		m_BlackBoard->setBool("EAction", false);
		m_BlackBoard->setBool("RAction", false);
		m_BlackBoard->setFloat("AttackFrom", 1000.f);
		m_BlackBoard->setFloat("TargetAt", 1000.f);
		m_BlackBoard->setBool("OnTarget", false);
		m_BlackBoard->setBool("HasCoord", false);
		m_BlackBoard->setBool("Aggressive", false);
		m_BlackBoard->setFloat("Distance", 0.f);
		m_BlackBoard->setBool("Turn", false);
	}
}
void UdyrBT::UdyrBTHandler::UpdateBlackBoard()
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

	{	// Initialize (StatusInfo에 없는 내용)
		//m_BlackBoard->setFloat("Distance", 0.f);
		//m_BlackBoard->setFloat("Direction", 0.f);
	}
}

void UdyrBT::UdyrAccessor::ChangeAnySet(string key)
{
	auto it = find(m_pInst->m_AniSetNameList.begin(), m_pInst->m_AniSetNameList.end(), key);
	if (it == m_pInst->m_AniSetNameList.end()) {
		cout << "그런 애니 또 없습니다." << '\n';
		return;
	}
	m_pInst->m_pAnimationCtrl->BlendAnimationSet(key);
}

bool UdyrBT::WhenEnemyNear::Ask()
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
#pragma region 리펙토링 대상
bool UdyrBT::UdyrAccessor::TurnSlowly(const D3DXVECTOR3 * destPos, float fLerpRate)
{
	return m_pInst->TurnSlowly(destPos,fLerpRate);
}

D3DXVECTOR3 & UdyrBT::UdyrAccessor::GetChampMousePickPos()
{
	return m_pInst->m_MouseHitPoint;
}

STATUSINFO & UdyrBT::UdyrAccessor::GetStatusInfo() const
{
	return m_pInst->m_StatusInfo;
}

const UdyrBT::UdyrBTHandler * UdyrBT::UdyrAccessor::GetBehaviorTree()
{
	return m_pInst->GetBehaviorTree();
}

SPHERE * UdyrBT::UdyrAccessor::GetEnemySphere()
{
	return m_pInst->m_sphereTarget;
}
#pragma endregion

#pragma region 자식 TASK 정의
//////////// Death /////////////
void UdyrBT::UdyrDeath::Init()
{
	m_BlackBoard->setBool("Dying", true);
	ChangeAnySet("Death");
	auto obj = m_pInst;		auto pos = &m_pInst->m_Info.vPos;
	GET_SINGLE(EventMgr)->Publish(new OBJDIEEVENT(
		reinterpret_cast<void**>(&obj), reinterpret_cast<void**>(&pos)));
}
void UdyrBT::UdyrDeath::Do()
{
	++iCntAni;
	if (iCntAni == iSoundSec) {
		GET_SINGLE(SoundMgr)->PlayUdyrSound(T_SOUND::Udyr_Death);
	}
	if (iCntAni >= 162) {
		iCntAni = 0;
		m_status = TERMINATED;
	}
}
void UdyrBT::UdyrDeath::Terminate()
{
	m_BlackBoard->setBool("Dying", false);
	m_BlackBoard->setBool("Alive", false);
}
//////////// Beaten /////////////
void UdyrBT::UdyrBeaten::Do()
{
	if (m_BlackBoard->getBool("Beaten")) {
		GET_SINGLE(SoundMgr)->PlayUdyrSound(T_SOUND::Udyr_Beaten);
		m_status = TERMINATED;
	}
}
void UdyrBT::UdyrBeaten::Terminate()
{
	m_BlackBoard->setBool("Beaten", false);
}
//////////// OnTarget /////////////
void UdyrBT::UdyrOnTarget::Init()
{
	m_BlackBoard->setBool("HasCoord", false);
	if (GetEnemySphere() != spEnemy) {
		spEnemy = GetEnemySphere();
		bNewTarget = true;
	}
	
}
void UdyrBT::UdyrOnTarget::Do()
{
	D3DXVECTOR3& vecPickPos = GetChampMousePickPos();
	vecPickPos = *spEnemy->vpCenter;

	float dist = D3DXVec3Length(&(m_pInst->m_Info.vPos - m_pInst->m_MouseHitPoint));
	m_BlackBoard->setFloat("TargetAt", dist);
	//if (dist > m_pInst->m_StatusInfo.fAttackRange)
		GetBehaviorTree()->m_vSelector[SELECTOR_ENEMY]->Run();
	//else
	//	m_BlackBoard->setBool("Attack", true);
	

	if (m_BlackBoard->getBool("OnTarget") == false)
		m_status = TERMINATED;
}
void UdyrBT::UdyrOnTarget::Terminate()
{
	spEnemy = nullptr;
	bNewTarget = false;
}
//////////// hasCoord /////////////
void UdyrBT::UdyrHasCoord::Init()
{
	m_BlackBoard->setBool("OnTarget", false);
	if (UdyrAccessor::GetChampMousePickPos() != vecPrevPos) {
		vecPrevPos = UdyrAccessor::GetChampMousePickPos();
		bNewPos = true;
	}
}
void UdyrBT::UdyrHasCoord::Do()
{
	GetBehaviorTree()->m_vSequnece[SEQUENCE_MOVE]->Run();
	if (m_BlackBoard->getBool("HasCoord") == false)
		m_status = TERMINATED;
}
void UdyrBT::UdyrHasCoord::Terminate()
{
	vecPrevPos = D3DXVECTOR3(0,0,0);
	bNewPos = false;
}
//////////// Aggressive /////////////
void UdyrBT::UdyrAggressive::Do()
{
	cout << "어크로 끌림.\n";
	//GetBehaviorTree()->m_vSequnece[SEQUENCE_MOVE]->Run();
}
//////////// Attack /////////////
void UdyrBT::UdyrAttack::Init()
{

	ChangeAnySet("Attack_Left");
}
void UdyrBT::UdyrAttack::Do()
{
	if (m_BlackBoard->getBool("OnTarget") == false) {
		m_status = TERMINATED;
		ChangeAnySet("Run");
		return;
	}

	++iCntAni;
	// 카격 시점 30 = 0.5초
	if (iCntAni == iSoundSec) {
		GET_SINGLE(SoundMgr)->PlayUdyrSound(T_SOUND::Udyr_Attack_Left);
	}
	// 애니메이션 끝나는 시점 60:25 = iCntAni:25
	if (iCntAni >= 60) {
		auto enemypos = m_pInst->m_sphereTarget->vpCenter;
		STATUSINFO infoDemage;	infoDemage.fBase_Attack = m_pInst->m_StatusInfo.fBase_Attack;
		GET_SINGLE(EventMgr)->Publish(new PHYSICALATTACKEVENT(&D3DXVECTOR3(m_pInst->m_Info.vPos)
			, &D3DXVECTOR3(*enemypos), &infoDemage));
		iCntAni = 0;
		m_status = TERMINATED;
	}
}
void UdyrBT::UdyrAttack::Terminate()
{
	//m_BlackBoard->setBool("OnTarget", false);
	//iCntAni = 0;
	m_status = INVALID;
}
//////////// Idle /////////////
void UdyrBT::UdyrIdle::Init()
{
	ChangeAnySet("Idle");
}
void UdyrBT::UdyrIdle::Do()
{
	m_status = INVALID;
}
//////////// QAction /////////////
void UdyrBT::UdyrQAction::Init()
{
	m_BlackBoard->setBool("QAction", false);
	// Q 스킬 관련 애니메이션
	ChangeAnySet("Taunt");
}
void UdyrBT::UdyrQAction::Do()
{
	// 스킬 사용하는 애니메이션

	// 스킬을 사용 행동.

	// 스킬 사용 사운드
}
void UdyrBT::UdyrQAction::Terminate()
{
	ChangeAnySet("Idle");
}
//////////// Run /////////////
void UdyrBT::UdyrRun::Init()
{
	ChangeAnySet("Run");
	m_BlackBoard->setBool("Turn", true);
}
void UdyrBT::UdyrRun::Do()
{
	m_BlackBoard->setFloat("Distance", D3DXVec3Length(&(GetChampMousePickPos() - m_pInst->GetInfo()->vPos)));
	bool bDest = m_pInst->Update_vPos_ByDestPoint(&GetChampMousePickPos(), m_BlackBoard->getFloat("fMoveSpeed"));
	if (!bDest) {
		m_status = TERMINATED;
		m_BlackBoard->setBool("HasCoord", false);
	}
}
void UdyrBT::UdyrRun::Terminate()
{
	m_status = INVALID;
}
//////////// Turn /////////////
void UdyrBT::UdyrTurn::Do()
{
	//m_BlackBoard->setFloat("Direction", m_pInst->m_fAngle[ANGLE_Y]);
	bool bTurning = m_pInst->TurnSlowly(&m_pInst->m_MouseHitPoint);
	if (!bTurning)
		m_status = INVALID;
}
void UdyrBT::UdyrTurn::Terminate()
{
	m_BlackBoard->setBool("Turn", false);
}
#pragma endregion