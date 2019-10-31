#include "BaseInclude.h"
#include "Behavior.h"
#include ""

inline void BehaviorTree::Behavior::SetUp(Node & node) {
	Release();
	m_pNode = &node;
	m_pTask = node.Init();
}

void BehaviorTree::Behavior::Release()
{
	if (m_pTask == nullptr)
		return;
	assert(m_eStatus != RUNNING);
	m_pNode->Release(m_pTask);
	m_pTask = nullptr;
}

BehaviorTree::Status BehaviorTree::Behavior::Tick()
{
	if (m_eStatus == INVALID)
		m_pTask->OnInit();

	m_eStatus = m_pTask->Progress();

	if (m_eStatus != RUNNING)
		m_pTask->OnRelease(m_pTask);
	return m_eStatus;
}
