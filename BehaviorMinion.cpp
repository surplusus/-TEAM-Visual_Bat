#include "BaseInclude.h"
#include "BehaviorMinion.h"
#include "Minion.h"

MinionBT::MinionBTHandler::MinionBTHandler(CMinion* inst)
	: m_pMinionInst(inst)
{
	m_vTask.resize(TASK_END);
	for (int i = 0; i < SEQUENCE_END; ++i)
		m_vSequnece.emplace_back(make_shared<Sequence>(m_BlackBoard.get()));
	for (int i = 0; i < SELECTOR_END; ++i)
		m_vSelector.emplace_back(make_shared<Selector>(m_BlackBoard.get()));

	SetRoot(SEQUENCE_ROOT);
}

MinionBT::MinionBTHandler::~MinionBTHandler()
{
	m_vSequnece.clear();
	m_vSelector.clear();
	m_vTask.clear();
}

void MinionBT::MinionBTHandler::SetRoot(int eNode)
{
	m_Root = m_vSequnece[eNode].get();
}

void MinionBT::MinionBTHandler::MakeTree()
{
	// Task를 BehaviorTree에 매단다
	m_vSequnece[SEQUENCE_ROOT]->AddNode(m_vSelector[SELECTOR_DEATH].get());
	m_vSequnece[SEQUENCE_ROOT]->AddNode(m_vTask[TASK_ANI].get());
	m_vSelector[SELECTOR_DEATH]->AddNode(m_vTask[TASK_DEATH].get());
	m_vSelector[SELECTOR_DEATH]->AddNode(m_vSequnece[SEQUENCE_RUN].get());
	m_vSelector[SELECTOR_DEATH]->AddNode(m_vTask[TASK_IDLE].get());
	m_vSequnece[SEQUENCE_RUN]->AddNode(m_vTask[TASK_CLICK].get());
	m_vSequnece[SEQUENCE_RUN]->AddNode(m_vTask[TASK_WALK].get());
	m_vSequnece[SEQUENCE_RUN]->AddNode(m_vTask[TASK_TURN].get());
}

void MinionBT::MinionBTHandler::SetUpBlackBoard()
{
	m_BlackBoard->setBool("Click", false);
	m_BlackBoard->setFloat("fBase_Attack", m_pMinionInst->m_stStatusInfo.fBase_Attack);
	m_BlackBoard->setFloat("fMagic_Attack", m_pMinionInst->m_stStatusInfo.fMagic_Attack);
	m_BlackBoard->setFloat("fBase_Defence", m_pMinionInst->m_stStatusInfo.fBase_Defence);
	m_BlackBoard->setFloat("fMagic_Defence", m_pMinionInst->m_stStatusInfo.fMagic_Defence);
	m_BlackBoard->setFloat("fCriticalRatio", m_pMinionInst->m_stStatusInfo.fCriticalRatio);
	m_BlackBoard->setFloat("fMoveSpeed", m_pMinionInst->m_stStatusInfo.fMoveSpeed);
	m_BlackBoard->setFloat("fMana", m_pMinionInst->m_stStatusInfo.fMana);
	m_BlackBoard->setFloat("fHP", m_pMinionInst->m_stStatusInfo.fHP);
	m_BlackBoard->setFloat("fSkillTimeRatio", m_pMinionInst->m_stStatusInfo.fSkillTimeRatio);
	m_BlackBoard->setFloat("fAttackRange", m_pMinionInst->m_stStatusInfo.fAttackRange);
}

void MinionBT::MinionBTHandler::AddTask(int eSequenceType, function<void(void)> pFunc)
{
	switch (eSequenceType)
	{
	case MinionBT::TASK_DEATH:
		m_vTask[TASK_DEATH] = make_shared<MinionDeath>(m_pMinionInst, pFunc);
		break;
	case MinionBT::TASK_CLICK:
		m_vTask[TASK_CLICK] = make_shared<MinionDeath>(m_pMinionInst, pFunc);
		break;
	case MinionBT::TASK_WALK:
		m_vTask[TASK_WALK] = make_shared<MinionDeath>(m_pMinionInst, pFunc);
		break;
	case MinionBT::TASK_TURN:
		m_vTask[TASK_TURN] = make_shared<MinionDeath>(m_pMinionInst, pFunc);
		break;
	case MinionBT::TASK_IDLE:
		m_vTask[TASK_IDLE] = make_shared<MinionDeath>(m_pMinionInst, pFunc);
		break;
	case MinionBT::TASK_ANI:
		m_vTask[TASK_ANI] = make_shared<MinionDeath>(m_pMinionInst, pFunc);
		break;
	default:
		break;
	}
}

bool MinionBT::MinionDeath::Condition()
{
	if (m_BlackBoard->getFloat("fHP") <= 0)
		return true;
	return false;
}
