#include "BaseInclude.h"
#include "BehaviorMinion.h"
#include "Minion.h"

MinionBT::MinionBTHandler::MinionBTHandler(CMinion* inst)
	: m_pUdyrInst(inst)
{
	m_vTask.resize(TASK_END);
	for (int i = 0; i < SEQUENCE_END; ++i)
		m_vSequnece.emplace_back(make_shared<Sequence>(&m_BlackBoard));
	for (int i = 0; i < SELECTOR_END; ++i)
		m_vSelector.emplace_back(make_shared<Selector>(&m_BlackBoard));

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
	m_vSequnece[SEQUENCE_ROOT]->AddNode(m_vSelector[SELECTOR_RUN].get());
	m_vSelector[SELECTOR_RUN]->AddNode(m_vTask[TASK_IDLE].get());
	m_vSelector[SELECTOR_RUN]->AddNode(m_vTask[TASK_RUN].get());
}

void MinionBT::MinionBTHandler::AddTask(int eSequenceType, function<void(void)> pFunc)
{
	switch (eSequenceType)
	{
	case TASK_IDLE:
		m_vTask[TASK_IDLE] = make_shared<MinionIdle>(pFunc);
	case TASK_RUN:
		//m_vTask[TASK_RUN] = make_shared<MinionRun>(pFunc);
		break;
	case TASK_ATTACK:
		break;
	case TASK_END:
		break;
	}
}

bool MinionBT::MinionTask::Condition()
{
	if (m_BlackBoard->hasBool("Attack"))
		return (m_BlackBoard->getBool("Attack") == true);

	cout << "BlackBoard에 키 Attack이 없습니다." << '\n';
}

bool MinionBT::MinionIdle::Condition()
{
	if (m_BlackBoard->hasBool("Click"))
		return (m_BlackBoard->getBool("Click") == false);
}

bool MinionBT::MinionRun::Condition()
{
	if (m_BlackBoard->hasBool("Click"))
		return (m_BlackBoard->getBool("Click") == true);
}
