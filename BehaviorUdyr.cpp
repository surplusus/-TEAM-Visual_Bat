#include "BaseInclude.h"
#include "BehaviorUdyr.h"
#include "Udyr.h"

UdyrBT::UdyrBTHandler::UdyrBTHandler(CUdyr ** inst)
	: m_pUdyrInst(*inst)
{
	m_vSequnece.resize(SEQUENCE_END);
	m_vSelector.resize(SELECTOR_END);
	m_vTask.resize(TASK_END);

	for (int i = 0; i < SEQUENCE_END; ++i)
		m_vSequnece[i] = make_shared<Sequence>(&m_BlackBoard);
	for (int i = 0; i < SELECTOR_END; ++i)
		m_vSelector[i] = make_shared<Selector>(&m_BlackBoard);

	SetRoot(SEQUENCE_ROOT);
}

UdyrBT::UdyrBTHandler::UdyrBTHandler()
{
	m_vSequnece.resize(SEQUENCE_END);
	m_vSelector.resize(SELECTOR_END);
	m_vTask.resize(TASK_END);

	for (int i = 0; i < SEQUENCE_END; ++i)
		m_vSequnece[i] = make_shared<Sequence>(&m_BlackBoard);
	for (int i = 0; i < SELECTOR_END; ++i)
		m_vSelector[i] = make_shared<Selector>(&m_BlackBoard);

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
	m_vSequnece[SEQUENCE_RUN]->AddNode(m_vTask[TASK_WALK].get());
	m_vSequnece[SEQUENCE_RUN]->AddNode(m_vTask[TASK_TURN].get());
}

void UdyrBT::UdyrBTHandler::SetUpBlackBoard()
{
	m_BlackBoard->setBool("Click", false);
	m_BlackBoard->setFloat("HP", 100.f);
	m_BlackBoard->setFloat("Base_Attack", 10.f);
	m_BlackBoard->setFloat("MoveSpeed", 3.5f);
}

void UdyrBT::UdyrBTHandler::AddTask(int eSequenceType, function<void(void)> pFunc)
{
	switch (eSequenceType)
	{
	case UdyrBT::TASK_DEATH:
		m_vTask[TASK_DEATH] = make_shared<UdyrDeath>(m_pUdyrInst, pFunc);
		break;
	case UdyrBT::TASK_CLICK:
		m_vTask[TASK_CLICK] = make_shared<UdyrDeath>(m_pUdyrInst, pFunc);
		break;
	case UdyrBT::TASK_WALK:
		m_vTask[TASK_WALK] = make_shared<UdyrDeath>(m_pUdyrInst, pFunc);
		break;
	case UdyrBT::TASK_TURN:
		m_vTask[TASK_TURN] = make_shared<UdyrDeath>(m_pUdyrInst, pFunc);
		break;
	case UdyrBT::TASK_IDLE:
		m_vTask[TASK_IDLE] = make_shared<UdyrDeath>(m_pUdyrInst, pFunc);
		break;
	case UdyrBT::TASK_ANI:
		m_vTask[TASK_ANI] = make_shared<UdyrDeath>(m_pUdyrInst, pFunc);
		break;
	default:
		break;
	}
}

bool UdyrBT::UdyrTask::Condition()
{
	if (m_BlackBoard->get()->hasBool("Attack"))
		return (m_BlackBoard->get()->getBool("Attack") == true);
	cout << "BlackBoard에 키 Attack이 없습니다." << '\n';
}

bool UdyrBT::UdyrDeath::Condition()
{
	
	if (!m_BlackBoard->get()->hasBool("Death"))
		return m_BlackBoard->get()->hasBool("Death");
		return (m_BlackBoard->get()->getBool("Attack") == true);
}
