#include "BaseInclude.h"
#include "BehaviorUdyr.h"
#include "Udyr.h"

UdyrBT::UdyrBTHandler::UdyrBTHandler(CUdyr * inst)
	: m_pUdyrInst(inst)
{
	for (int i = 0; i < SEQUENCE_END; ++i)
		m_vSequnece.emplace_back(make_shared<Sequence>(m_BlackBoard.get()));
	for (int i = 0; i < SELECTOR_END; ++i)
		m_vSelector.emplace_back(make_shared<Selector>(m_BlackBoard.get()));

	m_vTask.resize(TASK_END);
	{
		m_vTask[TASK_DEATH] = make_shared<UdyrDeath>();
		m_vTask[TASK_CLICK] = make_shared<UdyrClick>();
		m_vTask[TASK_RUN] = make_shared<UdyrRun>();
		m_vTask[TASK_TURN] = make_shared<UdyrTurn>();
		m_vTask[TASK_IDLE] = make_shared<UdyrIdle>();
		m_vTask[TASK_ANI] = make_shared<UdyrAni>();
	}
	SetRoot(SEQUENCE_ROOT);
}

UdyrBT::UdyrBTHandler::~UdyrBTHandler()
{
	m_vSequnece.clear();
	m_vSelector.clear();
	m_vTask.clear();
}

void UdyrBT::UdyrBTHandler::SetRoot(int eNode)
{
	m_Root = m_vSequnece[eNode].get();
}

void UdyrBT::UdyrBTHandler::MakeTree()
{
	// Task를 BehaviorTree에 매단다
	m_vSequnece[SEQUENCE_ROOT]->AddNode(m_vSelector[SELECTOR_DEATH].get());
	m_vSequnece[SEQUENCE_ROOT]->AddNode(m_vTask[TASK_ANI].get());
	m_vSelector[SELECTOR_DEATH]->AddNode(m_vTask[TASK_DEATH].get());
	m_vSelector[SELECTOR_DEATH]->AddNode(m_vSequnece[SEQUENCE_RUN].get());
	m_vSelector[SELECTOR_DEATH]->AddNode(m_vTask[TASK_IDLE].get());
	m_vSequnece[SEQUENCE_RUN]->AddNode(m_vTask[TASK_CLICK].get());
	m_vSequnece[SEQUENCE_RUN]->AddNode(m_vTask[TASK_RUN].get());
	m_vSequnece[SEQUENCE_RUN]->AddNode(m_vTask[TASK_TURN].get());
}

void UdyrBT::UdyrBTHandler::SetUpBlackBoard()
{
	m_BlackBoard->setBool("Click", false);
	m_BlackBoard->setBool("Death", false);
	m_BlackBoard->setBool("Run", false);
	m_BlackBoard->setBool("Idle", false);

	m_BlackBoard->setFloat("fBase_Attack", m_pUdyrInst->m_stStatusInfo.fBase_Attack);
	m_BlackBoard->setFloat("fMagic_Attack", m_pUdyrInst->m_stStatusInfo.fMagic_Attack);
	m_BlackBoard->setFloat("fBase_Defence", m_pUdyrInst->m_stStatusInfo.fBase_Defence);
	m_BlackBoard->setFloat("fMagic_Defence", m_pUdyrInst->m_stStatusInfo.fMagic_Defence);
	m_BlackBoard->setFloat("fCriticalRatio", m_pUdyrInst->m_stStatusInfo.fCriticalRatio);
	m_BlackBoard->setFloat("fMoveSpeed", m_pUdyrInst->m_stStatusInfo.fMoveSpeed);
	m_BlackBoard->setFloat("fMana", m_pUdyrInst->m_stStatusInfo.fMana);
	m_BlackBoard->setFloat("fHP", m_pUdyrInst->m_stStatusInfo.fHP);
	m_BlackBoard->setFloat("fSkillTimeRatio", m_pUdyrInst->m_stStatusInfo.fSkillTimeRatio);
	m_BlackBoard->setFloat("fAttackRange", m_pUdyrInst->m_stStatusInfo.fAttackRange);
}

void UdyrBT::UdyrBTHandler::UpdateBlackBoard()
{
	STATUSINFO& Info = m_pUdyrInst->m_stStatusInfo;

	if (CheckMouseButtonDownOneTime(MOUSEBUTTON0)) {
		m_BlackBoard->setBool("Click", true);
	}
	if (CheckPushKeyOneTime(VK_K))
		m_BlackBoard->setFloat("fHP", Info.fHP);

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

void UdyrBT::UdyrBTHandler::AddTask(int eTaskType, function<void(void)> pFunc)
{
	if (pFunc == nullptr)
		return;

	m_vTask[eTaskType]->SetMemberFunc(pFunc);
}

bool UdyrBT::UdyrDeath::Condition()
{
	if (m_BlackBoard->getFloat("fHP") <= 0)
		return true;
	return false;
}

bool UdyrBT::UdyrClick::Condition()
{
	if (CheckMouseButtonDownOneTime(MOUSEBUTTON0))
		return true;
	return false;
}

bool UdyrBT::UdyrClick::Do()
{
	
	m_BlackBoard->setBool("Click", true);
	return true;
}

bool UdyrBT::UdyrRun::Condition()
{
	return false;
}

bool UdyrBT::UdyrRun::Do()
{
	return false;
}

bool UdyrBT::UdyrTurn::Condition()
{
	return false;
}

bool UdyrBT::UdyrTurn::Do()
{
	return false;
}

bool UdyrBT::UdyrIdle::Condition()
{
	return false;
}

bool UdyrBT::UdyrIdle::Do()
{
	return false;
}

bool UdyrBT::UdyrAni::Condition()
{
	return false;
}

bool UdyrBT::UdyrAni::Do()
{
	return false;
}
