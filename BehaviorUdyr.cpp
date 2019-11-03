#include "BaseInclude.h"
#include "BehaviorUdyr.h"
#include "Udyr.h"

UdyrBT::UdyrBTHandler::UdyrBTHandler()
{
	for (int i = 0; i < SEQUENCE_END; ++i)
		m_vSequnece.emplace_back(new Sequence(&m_BlackBoard));
	for (int i = 0; i < SELECTOR_END; ++i)
		m_vSelector.emplace_back(new Selector(&m_BlackBoard));
	m_vTask.resize(TASK_END);

	MakeTree();

	SetRoot(SEQUENCE_ROOT);
}

UdyrBT::UdyrBTHandler::~UdyrBTHandler()
{
	Release();
	for (auto & it : m_vSequnece)
		SAFE_RELEASE(it);
	for (auto & it : m_vSelector)
		SAFE_RELEASE(it);
	for (auto & it : m_vTask)
		SAFE_DELETE(it);
	m_vSequnece.clear();
	m_vSelector.clear();
	m_vTask.clear();
}

void UdyrBT::UdyrBTHandler::SetRoot(int eNode)
{
	m_Root = m_vSequnece[eNode];
}

void UdyrBT::UdyrBTHandler::MakeTree()
{
	// Task를 BehaviorTree에 매단다
	m_vSequnece[SEQUENCE_ROOT]->AddNode(m_vSelector[SELECTOR_RUN]);
	m_vSelector[SELECTOR_RUN]->AddNode(m_vTask[TASK_IDLE]);
	m_vSelector[SELECTOR_RUN]->AddNode(m_vTask[TASK_RUN]);
}

void UdyrBT::UdyrBTHandler::AddTask(int eSequenceType, function<void(void)> pFunc)
{
	switch (eSequenceType)
	{
	case TASK_IDLE:
		m_vTask[TASK_IDLE] = new UdyrIdle(pFunc);
		break;
	case TASK_RUN:
		m_vTask[TASK_RUN] = new UdyrRun(pFunc);
		break;
	case TASK_ATTACK:
		break;
	case TASK_END:
		break;
	}
}

bool UdyrBT::UdyrTask::Condition()
{
	if (m_BlackBoard->get()->hasBool("Attack"))
		return (m_BlackBoard->get()->getBool("Attack") == true);
	
	cout << "BlackBoard에 키 Attack이 없습니다." << '\n';
}
//
//bool UdyrBT::UdyrTask::Do()
//{
//	return false;
//}

bool UdyrBT::UdyrIdle::Condition()
{
	if (m_BlackBoard->get()->hasBool("Click"))
		return (m_BlackBoard->get()->getBool("Click") == false);
}
//
//bool UdyrBT::UdyrIdle::Do()
//{
//	UdyrBT::UdyrBTHandler::g_UdyrInst->ChangeAniSetByKey("Idle");
//	return true;
//}

bool UdyrBT::UdyrRun::Condition()
{
	if (m_BlackBoard->get()->hasBool("Click"))
		return (m_BlackBoard->get()->getBool("Click") == true);
}
//
//bool UdyrBT::UdyrRun::Do()
//{
//	UdyrBT::UdyrBTHandler::g_UdyrInst->ChangeAniSetByKey("Run");
//	return true;
//}
