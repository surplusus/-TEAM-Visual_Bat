#include "BaseInclude.h"
#include "BehaviorUdyr.h"
#include "Udyr.h"

UdyrBT::UdyrBTHandler::UdyrBTHandler(CUdyr * inst)
	: m_pUdyrInst(inst)
{
	m_vTask.resize(TASK_END);
	for (int i = 0; i < SEQUENCE_END; ++i)
		m_vSequnece.emplace_back(make_shared<Sequence>(m_BlackBoard.get()));
	for (int i = 0; i < SELECTOR_END; ++i)
		m_vSelector.emplace_back(make_shared<Selector>(m_BlackBoard.get()));

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

void UdyrBT::UdyrBTHandler::AddTask(int eSequenceType, function<void(void)> pFunc)
{
	switch (eSequenceType)
	{
	case UdyrBT::TASK_DEATH:
		m_vTask[TASK_DEATH] = make_shared<UdyrDeath>(m_pUdyrInst, pFunc);
		break;
	case UdyrBT::TASK_CLICK:
		m_vTask[TASK_CLICK] = make_shared<UdyrClick>(m_pUdyrInst, pFunc);
		break;
	case UdyrBT::TASK_RUN:
		m_vTask[TASK_RUN] = make_shared<UdyrRun>(m_pUdyrInst, pFunc);
		break;
	case UdyrBT::TASK_TURN:
		m_vTask[TASK_TURN] = make_shared<UdyrTurn>(m_pUdyrInst, pFunc);
		break;
	case UdyrBT::TASK_IDLE:
		m_vTask[TASK_IDLE] = make_shared<UdyrIdle>(m_pUdyrInst, pFunc);
		break;
	case UdyrBT::TASK_ANI:
		m_vTask[TASK_ANI] = make_shared<UdyrAni>(m_pUdyrInst, pFunc);
		break;
	default:
		break;
	}
}

bool UdyrBT::UdyrDeath::Condition()
{
	if (m_BlackBoard->getFloat("fHP") <= 0)
		return true;
	return false;
}

bool UdyrBT::UdyrClick::Condition()
{
	if (m_BlackBoard->getBool("Click"))
		return true;
	return false;
}

bool UdyrBT::UdyrRun::Condition()
{
	if (m_BlackBoard->getBool("Run"))
		return true;
	return false;
}

bool UdyrBT::UdyrTurn::Condition()
{
	if (m_BlackBoard->getBool("Turn"))
		return true;
	return false;
}

bool UdyrBT::UdyrIdle::Condition()
{
	if (m_BlackBoard->getBool("Idle"))
		return true;
	return false;
}

bool UdyrBT::UdyrAni::Condition()
{
	return true;
}
