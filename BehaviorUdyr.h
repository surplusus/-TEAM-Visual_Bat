#pragma once
#include "Behavior.h"
class CUdyr;

namespace UdyrBT
{
	using namespace BehaviorTree;

	enum {SEQUENCE_ROOT, SEQUENCE_IDLE, SEQUENCE_ATTACK, SEQUENCE_END};
	enum {SELECTOR_IDLE, SELECTOR_RUN, SELECTOR_ATTACK, SELECTOR_END};
	enum {TASK_IDLE, TASK_RUN, TASK_ATTACK, TASK_END};

	class UdyrBTHandler : public BehaviorTreeHandler
	{
	public:
		//UdyrBTHandler(const CUdyr** inst);
		UdyrBTHandler();
		~UdyrBTHandler();
		//static CUdyr*		g_UdyrInst;
		vector<Sequence*>	m_vSequnece;
		vector<Selector*>	m_vSelector;
		vector<Task*>		m_vTask;
		void SetRoot(int eNode);
		void MakeTree();
		void AddTask(int eSequenceType, function<void(void)> pFunc);
	};

	class UdyrTask : public Task
	{
	public:
		UdyrTask() : Task(this) {}
		virtual ~UdyrTask() {}
		virtual bool Condition() = 0;
		virtual bool Do() { m_Func(); return true; }
		function<void(void)> m_Func;
	};

	class UdyrIdle : public UdyrTask
	{
	public:
		UdyrIdle(function<void(void)> func) {
			m_Func = func;
		}
		virtual bool Condition() override;
	};

	class UdyrRun : public UdyrTask
	{
	public:
		UdyrRun(function<void(void)> func) {
			m_Func = func;
		}
		virtual bool Condition() override;
	};
}
