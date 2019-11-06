#pragma once
#include "Behavior.h"
class CMinion;

namespace MinionBT
{
	using namespace BehaviorTree;

	enum { SEQUENCE_ROOT, SEQUENCE_RUN, SEQUENCE_END };
	enum { SELECTOR_DEATH, SELECTOR_END };
	enum { TASK_DEATH, TASK_CLICK, TASK_WALK, TASK_TURN, TASK_IDLE, TASK_ANI, TASK_END };

	class MinionBTHandler : public BehaviorTreeHandler
	{
	public:
		MinionBTHandler(CMinion* inst);
		MinionBTHandler() {}
		~MinionBTHandler();
		CMinion*						m_pMinionInst;
		vector<shared_ptr<Sequence>>	m_vSequnece;
		vector<shared_ptr<Selector>>	m_vSelector;
		vector<shared_ptr<Task>>		m_vTask;

		void SetRoot(int eNode);
		void MakeTree();
		void SetUpBlackBoard();
		void AddTask(int eSequenceType, function<void(void)> pFunc);
	};

	class MinionTask : public Task
	{
		CMinion*	m_pMinionInst;
	public:
		MinionTask(CMinion* pMinion) : Task(this), m_pMinionInst(pMinion) {}
		virtual ~MinionTask() {}
		virtual bool Condition() = 0;
		virtual bool Do() { m_Func(); return true; }
		function<void(void)> m_Func;
	};

	// UdyrTask 자식 클래스들
	struct MinionDeath : public MinionTask
	{
		MinionDeath(CMinion* pMinion, function<void(void)> func)
			: MinionTask(pMinion) {
			m_Func = func;
		}
		virtual bool Condition() override;
	};
}
