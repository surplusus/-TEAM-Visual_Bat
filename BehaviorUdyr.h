#pragma once
#include "Behavior.h"
class CUdyr;

namespace UdyrBT
{
	using namespace BehaviorTree;

	enum {SEQUENCE_ROOT, SEQUENCE_RUN, SEQUENCE_END};
	enum {SELECTOR_DEATH, SELECTOR_END};
	enum {TASK_DEATH, TASK_CLICK, TASK_WALK, TASK_TURN, TASK_IDLE, TASK_ANI, TASK_END};

	class UdyrBTHandler : public BehaviorTreeHandler
	{
	public:
		UdyrBTHandler(CUdyr** inst);
		UdyrBTHandler();
		~UdyrBTHandler();
		CUdyr*							m_pUdyrInst;
		vector<shared_ptr<Sequence>>	m_vSequnece;
		vector<shared_ptr<Selector>>	m_vSelector;
		vector<shared_ptr<Task>>		m_vTask;

		void SetRoot(int eNode);
		void MakeTree();
		void SetUpBlackBoard();
		void AddTask(int eSequenceType, function<void(void)> pFunc);
	};

	class UdyrTask : public Task
	{
		CUdyr*	m_UdyrInst;
	public:
		UdyrTask(CUdyr* pUdyr) : Task(this), m_UdyrInst(pUdyr) {}
		virtual ~UdyrTask() {}
		virtual bool Condition() = 0;
		virtual bool Do() {	m_Func(); return true;	}
		function<void(void)> m_Func;
	};

	// UdyrTask 자식 클래스들
	struct UdyrDeath : public UdyrTask
	{
		UdyrDeath(CUdyr* pUdyr, function<void(void)> func)
			: UdyrTask(pUdyr) { m_Func = func; }
		virtual bool Condition() override;
	};

}
