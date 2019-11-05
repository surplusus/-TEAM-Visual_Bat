#pragma once
#include "Behavior.h"
class CMinion;

namespace MinionBT
{
	using namespace BehaviorTree;

	enum { SEQUENCE_ROOT, SEQUENCE_IDLE, SEQUENCE_ATTACK, SEQUENCE_END };
	enum { SELECTOR_IDLE, SELECTOR_RUN, SELECTOR_ATTACK, SELECTOR_END };
	enum { TASK_IDLE, TASK_RUN, TASK_ATTACK, TASK_END };

	class MinionBTHandler : public BehaviorTreeHandler
	{
	public:
		//MinionBTHandler(const CUdyr** inst);
		MinionBTHandler();
		~MinionBTHandler();
		//static CUdyr*		g_UdyrInst;
		vector<shared_ptr<Sequence>>	m_vSequnece;
		vector<shared_ptr<Selector>>	m_vSelector;
		vector<shared_ptr<Task>>		m_vTask;
		void SetRoot(int eNode);
		void MakeTree();
		void AddTask(int eSequenceType, function<void(void)> pFunc);
	};

	class MinionTask : public Task
	{
	public:
		MinionTask() : Task(this) {}
		virtual ~MinionTask() {}
		virtual bool Condition() = 0;
		virtual bool Do() { m_Func(); return true; }
		function<void(void)> m_Func;
	};

	class MinionIdle : public MinionTask
	{
	public:
		MinionIdle(function<void(void)> func) {
			m_Func = func;
		}
		virtual bool Condition() override;
	};
	class MinionRun : public MinionTask
	{
	public:
		MinionRun(function<void(void)> func) {
			m_Func = func;
		}
		virtual bool Condition() override;
	};
}
