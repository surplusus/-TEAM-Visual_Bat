#include "BaseInclude.h"
#include "BehaviorUdyr.h"
#include "Udyr.h"

UdyrBT::UdyrBTHandler::UdyrBTHandler(CUdyr * pInst)
	: m_pInst(pInst)
{
	for (int i = 0; i < SEQUENCE_END; ++i)
		m_vSequnece.emplace_back(make_shared<Sequence>(m_BlackBoard.get()));
	for (int i = 0; i < SELECTOR_END; ++i)
		m_vSelector.emplace_back(make_shared<Selector>(m_BlackBoard.get()));
	
	{	// vecter에 task와 decorator 보관 & decorator에 task 매달기
		InsertDecorate<WhenFloatLow>(InsertTask<UdyrDeath>(), "fHP", 0.f);
		InsertDecorate<WhenAlive>(InsertTask<UdyrHealth>());
		InsertDecorate<WhenBoolOn>(InsertTask<UdyrBeaten>(), "Beaten");
		InsertDecorate<WhenFloatLow>(InsertTask<UdyrAttack>(), "fAttackRange", 1.f);
		InsertDecorate<WhenAlive>(InsertTask<UdyrIdle>());
		InsertDecorate<WhenBoolOn>(InsertTask<UdyrQAction>(), "QAction");
		InsertDecorate<WhenBoolOn>(InsertTask<UdyrTargeting>(), "OnTarget");
		InsertDecorate<WhenBoolOn>(InsertTask<UdyrSetCoord>(), "HasCoord");
		InsertDecorate<WhenFloatAbove>(InsertTask<UdyrRun>(), "Distance", D3DX_16F_EPSILON);
		InsertDecorate<WhenFloatAbove>(InsertTask<UdyrTurn>(), "Direction", D3DX_16F_EPSILON);
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
	// Task를 BehaviorTree에 매단다
	{
		m_vSelector[SELECTOR_DEATH]->AddNode(m_vDecorator[TASK_DEATH].get());
		m_vSelector[SELECTOR_DEATH]->AddNode(m_vSequnece[SEQUENCE_LIFE].get());
		{
			m_vSequnece[SEQUENCE_LIFE]->AddNode(m_vDecorator[TASK_HEATH].get());
			m_vSequnece[SEQUENCE_LIFE]->AddNode(m_vDecorator[TASK_BEATEN].get());
			m_vSequnece[SEQUENCE_LIFE]->AddNode(m_vSelector[SELECTOR_INPUT].get());
			{
				m_vSelector[SELECTOR_INPUT]->AddNode(m_vSelector[SELECTOR_TARGET].get());
				{
					m_vSelector[SELECTOR_TARGET]->AddNode(m_vSequnece[SEQUENCE_ENEMY].get());
					{
						m_vSequnece[SEQUENCE_ENEMY]->AddNode(m_vDecorator[TASK_TARGETING].get());
						m_vSequnece[SEQUENCE_ENEMY]->AddNode(m_vSelector[SELECTOR_AGGRESSIVE].get());
						{
							m_vSelector[SELECTOR_AGGRESSIVE]->AddNode(m_vSequnece[SEQUENCE_MOVE].get());
							{
								m_vSequnece[SEQUENCE_MOVE]->AddNode(m_vDecorator[TASK_RUN].get());
								m_vSequnece[SEQUENCE_MOVE]->AddNode(m_vDecorator[TASK_TURN].get());
							}
							m_vSelector[SELECTOR_AGGRESSIVE]->AddNode(m_vDecorator[TASK_ATTACK].get());
						}
					}
					m_vSelector[SELECTOR_TARGET]->AddNode(m_vSequnece[SEQUENCE_EARTH].get());
					{
						m_vSequnece[SEQUENCE_EARTH]->AddNode(m_vDecorator[TASK_TARGETING].get());
						m_vSequnece[SEQUENCE_EARTH]->AddNode(m_vSequnece[SEQUENCE_MOVE].get());
						{
							m_vSequnece[SEQUENCE_MOVE]->AddNode(m_vDecorator[TASK_RUN].get());
							m_vSequnece[SEQUENCE_MOVE]->AddNode(m_vDecorator[TASK_TURN].get());
						}
					}
				}
				m_vSelector[SELECTOR_INPUT]->AddNode(m_vDecorator[TASK_QACTION].get());
				m_vSelector[SELECTOR_INPUT]->AddNode(m_vSelector[SELECTOR_AGGRESSIVE].get());
				{
					m_vSelector[SELECTOR_AGGRESSIVE]->AddNode(m_vSequnece[SEQUENCE_MOVE].get());
					{
						m_vSequnece[SEQUENCE_MOVE]->AddNode(m_vDecorator[TASK_RUN].get());
						m_vSequnece[SEQUENCE_MOVE]->AddNode(m_vDecorator[TASK_TURN].get());
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
		m_BlackBoard->setBool("Beaten", false);
		m_BlackBoard->setBool("QAction", false);
		m_BlackBoard->setBool("OnTarget", false);
		m_BlackBoard->setBool("HasCoord", false);
		m_BlackBoard->setFloat("Distance", 0.f);
		m_BlackBoard->setFloat("Direction", 0.f);
	}
}

void UdyrBT::UdyrBTHandler::UpdateBlackBoard()
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

	{	// Initialize (StatusInfo에 없는 내용)
		if (CheckPushKeyOneTime(VK_Q))
			m_BlackBoard->setBool("QAction", false);
		if (CheckPushKeyOneTime(VK_W))
			m_BlackBoard->setBool("Beaten", false);
		if (CheckPushKeyOneTime(VK_W))
		m_BlackBoard->setBool("HasCoord", false);
		m_BlackBoard->setFloat("Distance", 0.f);
		m_BlackBoard->setFloat("Direction", 0.f);
	}
}
#pragma region 예전 TASK
//bool UdyrBT::UdyrDeath::Condition()
//{
//	if (m_BlackBoard->getFloat("fHP") <= 0)
//		return true;
//	return false;
//}
//
//void UdyrBT::UdyrDeath::Do()
//{
//	m_BlackBoard->setBool("Death", true);
//	static float time = 0;
//	time += 1;
//	if (time > 120)
//		m_BlackBoard->setBool("ChampIsOver", true);
//}
//
//bool UdyrBT::UdyrClick::Condition()
//{
//	if (CheckMouseButtonDownOneTime(MOUSEBUTTON0)) {
//		m_BlackBoard->setBool("Pick",true);
//	}
//	return true;
//}
//
//void UdyrBT::UdyrClick::Do()
//{
//	if (m_BlackBoard->getBool("Pick"))
//		m_BlackBoard->setBool("Pick", false);
//	else
//		return;
//	m_Func();
//	m_BlackBoard->setBool("Turn", true);
//	m_BlackBoard->setBool("Run", true);
//	m_BlackBoard->setBool("Idle", false);
//}
//
//bool UdyrBT::UdyrRun::Condition()
//{
//	return m_BlackBoard->getBool("Run");
//}
//
//void UdyrBT::UdyrRun::Do()
//{
//	m_Func();
//}
//
//bool UdyrBT::UdyrTurn::Condition()
//{
//	return true;
//}
//
//void UdyrBT::UdyrTurn::Do()
//{
//	if (m_BlackBoard->getBool("Turn"))
//		m_Func();
//}
//
//bool UdyrBT::UdyrIdle::Condition()
//{
//	return true;
//}
//
//void UdyrBT::UdyrIdle::Do()
//{
//	m_BlackBoard->setBool("Idle", true);
//}
//
//bool UdyrBT::UdyrAni::Condition()
//{
//	return true;
//}
//
//void UdyrBT::UdyrAni::Do()
//{
//	m_Func();
//	m_BlackBoard->setBool("Ani", true);
//}
#pragma endregion

void UdyrBT::UdyrAccessor::ChangeAnySet(string key)
{
	auto it = find(m_pInst->m_AniSetNameList.begin(), m_pInst->m_AniSetNameList.end(), key);
	if (it == m_pInst->m_AniSetNameList.end()) {
		cout << "그런 애니 또 없습니다." << '\n';
		return;
	}
	m_pInst->m_pAnimationCtrl->BlendAnimationSet(key);
}

#pragma region 자식 TASK 정의

void UdyrBT::UdyrDeath::Do()
{
	ChangeAnySet("Death");
}

void UdyrBT::UdyrDeath::Terminate()
{
	ChangeAnySet("Idle");
}


#pragma endregion