#include "BaseInclude.h"
#include "BehaviorEzreal.h"
#include "Ezreal.h"

EzrealBT::EzrealBTHandler::EzrealBTHandler(CEzreal * pInst)
	: m_pInst(pInst)
{
	for (int i = 0; i < SEQUENCE_END; ++i)
		m_vSequnece.emplace_back(make_shared<Sequence>(m_BlackBoard.get()));
	for (int i = 0; i < SELECTOR_END; ++i)
		m_vSelector.emplace_back(make_shared<Selector>(m_BlackBoard.get()));

	{	// vecter에 task와 decorator 보관 & decorator에 task 매달기
		InsertDecorate<WhenBoolOn>(InsertTask<EzrealIDLE1>(), "fHP");
		InsertDecorate<WhenBoolOn>(InsertTask<EzrealIDLE2>(), "fHP");
		InsertDecorate<WhenBoolOn>(InsertTask<EzrealIDLE3>(), "fHP");
		InsertDecorate<WhenBoolOn>(InsertTask<EzrealATTACK1>(), "fHP");
		InsertDecorate<WhenBoolOn>(InsertTask<EzrealATTACK2>(), "fHP");
		InsertDecorate<WhenBoolOn>(InsertTask<EzrealSPELL1>(), "fHP");
		InsertDecorate<WhenBoolOn>(InsertTask<EzrealSPELL2>(), "fHP");
		InsertDecorate<WhenBoolOn>(InsertTask<EzrealSPELL3>(), "fHP");
		InsertDecorate<WhenBoolOn>(InsertTask<EzrealSPELL4>(), "fHP");
		InsertDecorate<WhenBoolOn>(InsertTask<EzrealRUN>(), "fHP");
		InsertDecorate<WhenBoolOn>(InsertTask<EzrealDEATH>(), "fHP");
		InsertDecorate<WhenBoolOn>(InsertTask<EzrealDEFAULT>(), "fHP");
		InsertDecorate<WhenBoolOn>(InsertTask<EzrealANIEND>(), "fHP");
	}
	// Set Root
	m_Root = m_vSelector[SELECTOR_ROOT].get();
	MakeTree();
	SetUpBlackBoard();
}

EzrealBT::EzrealBTHandler::~EzrealBTHandler()
{
	m_vSequnece.clear();
	m_vSelector.clear();
	m_vDecorator.clear();
	m_vTask.clear();
}

void EzrealBT::EzrealBTHandler::MakeTree()
{
	// Task를 BehaviorTree에 매단다
	{
		m_vSelector[SELECTOR_ROOT]->AddNode(m_vDecorator[TASK_IDLE1].get());
		m_vSelector[SELECTOR_ROOT]->AddNode(m_vDecorator[TASK_IDLE2].get());
		m_vSelector[SELECTOR_ROOT]->AddNode(m_vDecorator[TASK_IDLE3].get());
		m_vSelector[SELECTOR_ROOT]->AddNode(m_vDecorator[TASK_ATTACK1].get());
		m_vSelector[SELECTOR_ROOT]->AddNode(m_vDecorator[TASK_ATTACK2].get());
		m_vSelector[SELECTOR_ROOT]->AddNode(m_vDecorator[TASK_SPELL1].get());
		m_vSelector[SELECTOR_ROOT]->AddNode(m_vDecorator[TASK_SPELL2].get());
		m_vSelector[SELECTOR_ROOT]->AddNode(m_vDecorator[TASK_SPELL3].get());
		m_vSelector[SELECTOR_ROOT]->AddNode(m_vDecorator[TASK_SPELL4].get());
		m_vSelector[SELECTOR_ROOT]->AddNode(m_vDecorator[TASK_RUN].get());
		m_vSelector[SELECTOR_ROOT]->AddNode(m_vDecorator[TASK_DEATH].get());
		m_vSelector[SELECTOR_ROOT]->AddNode(m_vDecorator[TASK_DEFAULT].get());
		m_vSelector[SELECTOR_ROOT]->AddNode(m_vDecorator[TASK_ANIEND].get());
	}
}

void EzrealBT::EzrealBTHandler::SetUpBlackBoard()
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
		//ex)  m_BlackBoard->setBool("Beaten", false);
	}
}

void EzrealBT::EzrealBTHandler::UpdateBlackBoard()
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
		//ex)  m_BlackBoard->setBool("Beaten", false);
	}
}

void EzrealBT::EzrealAccessor::ChangeAnySet(string key)
{
	// Ezreal 내부에 구현된 함수 래핑
	//ex)
	//auto it = find(m_pInst->m_AniSetNameList.begin(), m_pInst->m_AniSetNameList.end(), key);
	//if (it == m_pInst->m_AniSetNameList.end()) {
	//	cout << "그런 애니 또 없습니다." << '\n';
	//	return;
	//}
	//m_pInst->m_pAnimationCtrl->BlendAnimationSet(key);
}
