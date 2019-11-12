#include "BaseInclude.h"
#include "BehaviorMinion.h"
#include "Minion.h"
#include "EventMgr.h"

MinionBT::MinionBTHandler::MinionBTHandler(CMinion* pInst)
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
		InsertDecorate<WhenBoolOn>(InsertTask<MinionAggressive>(), "Aggressive");
		InsertDecorate<WhenFloatAbove>(InsertTask<MinionRun>(), "Distance", D3DX_16F_EPSILON);
		InsertDecorate<WhenBoolOn>(InsertTask<MinionTurn>(), "Turn");
		InsertDecorate<WhenBoolOn>(InsertTask<MinionIdle>(), "QAction");
	}

	// Set Root
	m_Root = m_vSelector[SELECTOR_DEATH].get();
	MakeTree();
	SetUpBlackBoard();
}

MinionBT::MinionBTHandler::~MinionBTHandler()
{
	m_vSequnece.clear();
	m_vSelector.clear();
	m_vDecorator.clear();
	m_vTask.clear();
}

void MinionBT::MinionBTHandler::MakeTree()
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
			m_vSequnece[SEQUENCE_LIFE]->AddNode(m_vSelector[SELECTOR_FOLLOW].get());
			{
				m_vSelector[SELECTOR_FOLLOW]->AddNode(m_vDecorator[DECORATOR_AGGRESSIVE].get());
				{
					m_vSelector[SELECTOR_AGGRESSIVE]->AddNode(m_vDecorator[TASK_ATTACK].get());
					m_vSelector[SELECTOR_AGGRESSIVE]->AddNode(m_vSequnece[SEQUENCE_MOVE].get());
				}
				m_vSelector[SELECTOR_FOLLOW]->AddNode(m_vSequnece[SEQUENCE_MOVE].get());
				
			}
		}
	}
}

void MinionBT::MinionBTHandler::SetUpBlackBoard()
{
	{	// stStatusInfo
		m_BlackBoard->setFloat("fBase_Attack", m_pInst->m_stStatusInfo.fBase_Attack);
		m_BlackBoard->setFloat("fMagic_Attack", m_pInst->m_stStatusInfo.fMagic_Attack);
		m_BlackBoard->setFloat("fBase_Defence", m_pInst->m_stStatusInfo.fBase_Defence);
		m_BlackBoard->setFloat("fMagic_Defence", m_pInst->m_stStatusInfo.fMagic_Defence);
		m_BlackBoard->setFloat("fCriticalRatio", m_pInst->m_stStatusInfo.fCriticalRatio);
		m_BlackBoard->setFloat("fMoveSpeed", m_pInst->m_stStatusInfo.fMoveSpeed);
		m_BlackBoard->setFloat("fMana", m_pInst->m_stStatusInfo.fMana);
		m_BlackBoard->setFloat("fHP", m_pInst->m_stStatusInfo.fHP);
		m_BlackBoard->setFloat("fSkillTimeRatio", m_pInst->m_stStatusInfo.fSkillTimeRatio);
		m_BlackBoard->setFloat("fAttackRange", m_pInst->m_stStatusInfo.fAttackRange);
	}
	{	// Initialize (StatusInfo에 없는 내용)
		m_BlackBoard->setBool("Alive", true);
		m_BlackBoard->setBool("Beaten", false);
		m_BlackBoard->setFloat("AttackFrom", 1000.f);
		m_BlackBoard->setFloat("TargetAt", 1000.f);
		m_BlackBoard->setBool("Aggressive", false);
		m_BlackBoard->setFloat("Distance", 0.f);
		m_BlackBoard->setBool("Turn", false);
	}
}

void MinionBT::MinionBTHandler::UpdateBlackBoard()
{
	STATUSINFO& Info = m_pInst->m_stStatusInfo;

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

void MinionBT::MinionAccessor::ChangeAnySet(string key)
{
	auto it = find(m_pInst->m_AniSetNameList.begin(), m_pInst->m_AniSetNameList.end(), key);
	if (it == m_pInst->m_AniSetNameList.end()) {
		cout << "그런 애니 또 없습니다." << '\n';
		return;
	}
	m_pInst->m_pAnimationCtrl->BlendAnimationSet(key);
}







#pragma region 자식 TASK 정의
//////////// Death /////////////
void MinionBT::MinionDeath::Init()
{
	m_BlackBoard->setBool("Dying", true);
	ChangeAnySet("Death");
}
void MinionBT::MinionDeath::Do()
{
	++iCntAni;
	if (iCntAni >= 182) {
		iCntAni = 0;
		m_status = TERMINATED;
	}
}
void MinionBT::MinionDeath::Terminate()
{
	m_BlackBoard->setBool("Dying", false);
	m_BlackBoard->setBool("Alive", false);
}
//////////// Beaten /////////////
void MinionBT::MinionBeaten::Do()
{
	if (m_BlackBoard->getBool("Beaten")) {
		//GET_SINGLE(SoundMgr)->PlayMinionSound(T_SOUND::Minion_Beaten);
		m_status = TERMINATED;
	}
}
void MinionBT::MinionBeaten::Terminate()
{
	m_BlackBoard->setBool("Beaten", false);
}
//////////// Aggressive /////////////
void MinionBT::MinionAggressive::Init()
{
	m_BlackBoard->setBool("Aggressive", false);
	if (m_pInst->m_sphereTarget != spEnemy) {
		spEnemy = m_pInst->m_sphereTarget;
		bNewTarget = true;
	}
}
void MinionBT::MinionAggressive::Do()
{
	D3DXVECTOR3 vecPickPos = *spEnemy->vpCenter;

	float dist = D3DXVec3Length(&(m_pInst->m_Info.vPos - vecPickPos));
	m_BlackBoard->setFloat("TargetAt", dist);
	m_pInst->m_pBehavior->m_vSelector[SELECTOR_AGGRESSIVE]->Run();

	if (m_BlackBoard->getBool("OnTarget") == false)
		m_status = TERMINATED;
}
void MinionBT::MinionAggressive::Terminate()
{
	spEnemy == nullptr;
	bNewTarget = false;
}
//////////// Attack /////////////
void MinionBT::MinionAttack::Init()
{
	ChangeAnySet("Attack_Left");
}
void MinionBT::MinionAttack::Do()
{
	++iCntAni;
	if (iCntAni == 24) {
		STATUSINFO infoDemage;	infoDemage.fBase_Attack = 10.f;
		GET_SINGLE(EventMgr)->Publish(new PHYSICALATTACKEVENT(&D3DXVECTOR3(), &infoDemage));
	}
	// 애니메이션 끝나는 시점 60:20 = iCntAni:20
	if (iCntAni >= 48) {
		iCntAni = 0;
		m_status = TERMINATED;
	}
}
void MinionBT::MinionAttack::Terminate()
{
	m_BlackBoard->setBool("OnTarget", false);
	m_status = INVALID;
}
//////////// Idle /////////////
void MinionBT::MinionIdle::Init()
{
	ChangeAnySet("Idle");
}
void MinionBT::MinionIdle::Do()
{
	m_status = INVALID;
}
//////////// Run /////////////
void MinionBT::MinionRun::Init()
{
	ChangeAnySet("Run");
	m_BlackBoard->setBool("Turn", true);
	if (m_BlackBoard->getBool("OnTarget") == true)
		m_vecNextPos = *m_pInst->m_sphereTarget->vpCenter;
	else
		m_vecNextPos = m_pInst->m_NextPoint;
}
void MinionBT::MinionRun::Do()
{
	m_BlackBoard->setFloat("Distance", D3DXVec3Length(&(m_vecNextPos - m_pInst->m_Info.vPos)));
	bool bDest = m_pInst->Update_vPos_ByDestPoint(&m_vecNextPos, m_BlackBoard->getFloat("fMoveSpeed"));
	if (!bDest) {
		m_status = TERMINATED;
	}
}
void MinionBT::MinionRun::Terminate()
{
	//ChangeAnySet("Idle");
}
//////////// Turn /////////////
void MinionBT::MinionTurn::Init()
{
	if (m_BlackBoard->getBool("OnTarget") == true)
		m_vecNextPos = *m_pInst->m_sphereTarget->vpCenter;
	else
		m_vecNextPos = m_pInst->m_NextPoint;
}
void MinionBT::MinionTurn::Do()
{
	//m_BlackBoard->setFloat("Direction", m_pInst->m_fAngle[ANGLE_Y]);
	bool bTurning = m_pInst->TurnSlowly(&m_vecNextPos);
	if (!bTurning)
		m_status = INVALID;
}
void MinionBT::MinionTurn::Terminate()
{
	m_BlackBoard->setBool("Turn", false);
}

#pragma endregion

