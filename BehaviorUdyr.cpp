#include "BaseInclude.h"
#include "BehaviorUdyr.h"
#include "Udyr.h"
#include "SoundMgr.h"
#include "EventMgr.h"

UdyrBT::UdyrBTHandler::UdyrBTHandler(CUdyr * pInst)
	: m_pInst(pInst)
{
	for (int i = 0; i < SEQUENCE_END; ++i)
		m_vSequnece.emplace_back(make_shared<Sequence>(m_BlackBoard.get()));
	for (int i = 0; i < SELECTOR_END; ++i)
		m_vSelector.emplace_back(make_shared<Selector>(m_BlackBoard.get()));
	
	{	// vecter�� task�� decorator ���� & decorator�� task �Ŵޱ�
		InsertDecorate<WhenFloatLow>(InsertTask<UdyrDeath>(), "fHP", 0.f);
		InsertDecorate<WhenAlive>(InsertTask<UdyrBeaten>());
		InsertDecorate<WhenBoolOn>(InsertTask<UdyrOnTarget>(), "OnTarget");
		InsertDecorate<WhenBoolOn>(InsertTask<UdyrHasCoord>(), "HasCoord");
		InsertDecorate<WhenFloatChecked>(InsertTask<UdyrAttack>(), "TargetAt", "fAttackRange", true);
		InsertDecorate<WhenAlive>(InsertTask<UdyrIdle>());
		InsertDecorate<WhenBoolOn>(InsertTask<UdyrQAction>(), "QAction");
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
	// Task�� BehaviorTree�� �Ŵܴ�
	{
		m_vSelector[SELECTOR_DEATH]->AddNode(m_vDecorator[TASK_DEATH].get());
		m_vSelector[SELECTOR_DEATH]->AddNode(m_vSequnece[SEQUENCE_LIFE].get());
		{
			m_vSequnece[SEQUENCE_LIFE]->AddNode(m_vDecorator[TASK_BEATEN].get());
			m_vSequnece[SEQUENCE_LIFE]->AddNode(m_vSelector[SELECTOR_INPUT].get());
			{
				m_vSelector[SELECTOR_INPUT]->AddNode(m_vSelector[SELECTOR_SKILL].get());
				{
					m_vSelector[SELECTOR_SKILL]->AddNode(m_vDecorator[TASK_QACTION].get());
				}
				m_vSelector[SELECTOR_INPUT]->AddNode(m_vDecorator[CONDITION_ONTARGET].get());// OnTarget
				{
					m_vSelector[SELECTOR_ENEMY]->AddNode(m_vDecorator[TASK_ATTACK].get());
					m_vSelector[SELECTOR_ENEMY]->AddNode(m_vSequnece[SEQUENCE_MOVE].get());
					{
						m_vSequnece[SEQUENCE_MOVE]->AddNode(m_vDecorator[TASK_RUN].get());
						m_vSequnece[SEQUENCE_MOVE]->AddNode(m_vDecorator[TASK_TURN].get());
					}
				}
				m_vSequnece[SELECTOR_INPUT]->AddNode(m_vDecorator[CONDITION_HASCOORD].get());// HasCoord
				{
					// �̹� SEQUENCE_MOVE�� �־����
					//m_vSequnece[SEQUENCE_MOVE]->AddNode(m_vDecorator[TASK_RUN].get());
					//m_vSequnece[SEQUENCE_MOVE]->AddNode(m_vDecorator[TASK_TURN].get());
				}
			}
			m_vSelector[SEQUENCE_LIFE]->AddNode(m_vSelector[SELECTOR_AGGRESSIVE].get());
			{
				m_vSelector[SELECTOR_AGGRESSIVE]->AddNode(m_vSequnece[SEQUENCE_MOVE].get());
				{
					// �̹� SEQUENCE_MOVE�� �־����
					//m_vSequnece[SEQUENCE_MOVE]->AddNode(m_vDecorator[TASK_RUN].get());
					//m_vSequnece[SEQUENCE_MOVE]->AddNode(m_vDecorator[TASK_TURN].get());
				}
				m_vSelector[SELECTOR_AGGRESSIVE]->AddNode(m_vDecorator[TASK_IDLE].get());
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
	{	// Initialize (StatusInfo�� ���� ����)
		m_BlackBoard->setBool("Alive", true);
		m_BlackBoard->setBool("Beaten", false);
		m_BlackBoard->setBool("QAction", false);
		m_BlackBoard->setBool("WAction", false);
		m_BlackBoard->setBool("EAction", false);
		m_BlackBoard->setBool("RAction", false);
		m_BlackBoard->setFloat("AttackFrom", 1000.f);
		m_BlackBoard->setFloat("TargetAt", 1000.f);
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

	{	// Initialize (StatusInfo�� ���� ����)
		//m_BlackBoard->setFloat("Distance", 0.f);
		//m_BlackBoard->setFloat("Direction", 0.f);
	}
}

void UdyrBT::UdyrAccessor::ChangeAnySet(string key)
{
	auto it = find(m_pInst->m_AniSetNameList.begin(), m_pInst->m_AniSetNameList.end(), key);
	if (it == m_pInst->m_AniSetNameList.end()) {
		cout << "�׷� �ִ� �� �����ϴ�." << '\n';
		return;
	}
	m_pInst->m_pAnimationCtrl->BlendAnimationSet(key);
}

bool UdyrBT::UdyrAccessor::TurnSlowly(const D3DXVECTOR3 * destPos, float fLerpRate)
{
	return m_pInst->TurnSlowly(destPos,fLerpRate);
}

D3DXVECTOR3 & UdyrBT::UdyrAccessor::GetChampMousePickPos()
{
	return m_pInst->m_MouseHitPoint;
}

STATUSINFO & UdyrBT::UdyrAccessor::GetStatusInfo() const
{
	return m_pInst->m_stStatusInfo;
}

UdyrBT::UdyrBTHandler * UdyrBT::UdyrAccessor::GetBehaviorTree()
{
	return m_pInst->GetBehaviorTree();
}

SPHERE * UdyrBT::UdyrAccessor::GetEnemySphere()
{
	return m_pInst->m_sphereTarget;
}

#pragma region �ڽ� TASK ����
//////////// Death /////////////
void UdyrBT::UdyrDeath::Init()
{
	m_BlackBoard->setBool("Dying", true);
	ChangeAnySet("Death");
}
void UdyrBT::UdyrDeath::Do()
{
	++iCntAni;
	if (iCntAni >= 168) {
		iCntAni = 0;
		m_status = TERMINATED;
	}
}
void UdyrBT::UdyrDeath::Terminate()
{
	m_BlackBoard->setBool("Dying", false);
	m_BlackBoard->setBool("ChampIsOver", true);
}
//////////// Beaten /////////////
void UdyrBT::UdyrBeaten::Do()
{
	if (m_BlackBoard->getBool("Beaten")) {
		GET_SINGLE(SoundMgr)->PlayUdyrSound(T_SOUND::Udyr_Beaten);
		m_status = TERMINATED;
	}
}
void UdyrBT::UdyrBeaten::Terminate()
{
	m_BlackBoard->setBool("Beaten", false);
}
//////////// OnTarget /////////////
void UdyrBT::UdyrOnTarget::Init()
{
	if (GetEnemySphere() != spEnemy) {
		spEnemy = GetEnemySphere();
		bNewTarget = true;
	}
}
void UdyrBT::UdyrOnTarget::Do()
{
	GetBehaviorTree()->m_vSelector[SELECTOR_ENEMY]->Run();
}
void UdyrBT::UdyrOnTarget::Terminate()
{
	spEnemy == nullptr;
	bNewTarget = false;
}
//////////// hasCoord /////////////
void UdyrBT::UdyrHasCoord::Init()
{
	if (UdyrAccessor::GetChampMousePickPos() != vecPrevPos) {
		vecPrevPos = UdyrAccessor::GetChampMousePickPos();
		bNewPos = true;
	}
}
void UdyrBT::UdyrHasCoord::Do()
{
	GetBehaviorTree()->m_vSequnece[SEQUENCE_MOVE]->Run();
}
void UdyrBT::UdyrHasCoord::Terminate()
{
	vecPrevPos = D3DXVECTOR3(0,0,0);
	bNewPos = false;
}
//////////// Attack /////////////
void UdyrBT::UdyrAttack::Init()
{
	ChangeAnySet("Attack_Left");
}
void UdyrBT::UdyrAttack::Do()
{
	++iCntAni;
	// ī�� ���� 30 = 0.5��
	if (iCntAni == 30) {
		STATUSINFO infoDemage;	infoDemage.fBase_Attack = 10.f;
		GET_SINGLE(EventMgr)->Publish(new PHYSICALATTACKEVENT(&D3DXVECTOR3(), &infoDemage));
	}
	// �ִϸ��̼� ������ ���� 60:25 = iCntAni:25
	if (iCntAni >= 60) {
		iCntAni = 0;
		m_status = TERMINATED;
	}
}
void UdyrBT::UdyrAttack::Terminate()
{
	m_BlackBoard->setBool("Attack", false);
	ChangeAnySet("Idle");
}
//////////// Idle /////////////
void UdyrBT::UdyrIdle::Init()
{
	ChangeAnySet("Idle");
}
void UdyrBT::UdyrIdle::Do()
{
	m_status = INVALID;
}
//////////// QAction /////////////
void UdyrBT::UdyrQAction::Init()
{
	m_BlackBoard->setBool("QAction", false);
	// Q ��ų ���� �ִϸ��̼�

}
void UdyrBT::UdyrQAction::Do()
{
	// ��ų ����ϴ� �ִϸ��̼�

	// ��ų�� ��� �ൿ.

	// ��ų ��� ����
}
void UdyrBT::UdyrQAction::Terminate()
{
	ChangeAnySet("Idle");
}
//////////// Targeting /////////////
void UdyrBT::UdyrTargeting::Init()
{
	if (vecPrevTargetPos != GetChampMousePickPos())
	{
		vecPrevTargetPos = GetChampMousePickPos();
		bNewTarget = true;
	}
}
void UdyrBT::UdyrTargeting::Do()
{
	// �� ���� Selector�� (�����Ѵ�) �Ŵܴ�
	GetBehaviorTree()->m_vSelector[SELECTOR_ENEMY]->Run();

	if (bNewTarget)
	{
		cout << "���ο�� ������.\n";
		bNewTarget = false;
		m_status = TERMINATED;
	}
}
void UdyrBT::UdyrTargeting::Terminate()
{
	m_BlackBoard->setBool("OnTarget", false);
}
//////////// SetCoord /////////////
void UdyrBT::UdyrSetCoord::Init()
{
}
void UdyrBT::UdyrSetCoord::Do()
{
}
void UdyrBT::UdyrSetCoord::Terminate()
{
}
//////////// Run /////////////
void UdyrBT::UdyrRun::Init()
{
	ChangeAnySet("Run");
}
void UdyrBT::UdyrRun::Do()
{
	m_BlackBoard->setFloat("Distance", D3DXVec3Length(&(GetChampMousePickPos() - m_pInst->GetInfo()->vPos)));
	bool bDest = m_pInst->Update_vPos_ByDestPoint(&GetChampMousePickPos(), m_BlackBoard->getFloat("fMoveSpeed"));
	if (!bDest)
		m_status = TERMINATED;
}
void UdyrBT::UdyrRun::Terminate()
{
	ChangeAnySet("Idle");
}
//////////// Turn /////////////
void UdyrBT::UdyrTurn::Do()
{
	m_BlackBoard->setFloat("Direction", D3DXVec3Length(&(GetChampMousePickPos() - m_pInst->GetInfo()->vPos)));
	bool bTurning = TurnSlowly(&GetChampMousePickPos(), m_BlackBoard->getFloat("fMoveSpeed"));
	if (!bTurning)
		m_status = TERMINATED;
}

#pragma endregion
