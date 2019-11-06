#pragma once
#include "Behavior.h"
class CUdyr;

namespace UdyrBT
{
	using namespace BehaviorTree;

	enum {SEQUENCE_ROOT, SEQUENCE_RUN, SEQUENCE_END};
	enum {SELECTOR_DEATH, SELECTOR_RUN, SELECTOR_END};
	enum {TASK_DEATH, TASK_CLICK, TASK_RUN, TASK_TURN, TASK_IDLE, TASK_ANI, TASK_END};
	class UdyrTask;
	class UdyrBTHandler : public BehaviorTreeHandler
	{
	private:
		friend class CUdyr;
	public:
		UdyrBTHandler(CUdyr* inst);
		UdyrBTHandler() {}
		~UdyrBTHandler();
		CUdyr*							m_pUdyrInst;
		vector<shared_ptr<Sequence>>	m_vSequnece;
		vector<shared_ptr<Selector>>	m_vSelector;
		vector<shared_ptr<UdyrTask>>	m_vTask;

		void SetRoot(int eNode);
		void MakeTree();
		void SetUpBlackBoard();
		virtual void UpdateBlackBoard() override;
		void AddTask(int eTaskType, function<void(void)> pFunc);
	};

	class UdyrTask : public Task
	{
	protected:
		CUdyr*	m_pInst = nullptr;
	public:
		UdyrTask() : Task(this){}
		virtual ~UdyrTask() {}
		virtual bool Condition() = 0;
		virtual void Do() = 0;
		void SetMemberInst(CUdyr* pInst) { m_pInst = pInst; }
		void SetMemberFunc(function<void(void)> func) { m_Func = func; }
		function<void(void)> m_Func = nullptr;
	};

	// UdyrTask 자식 클래스들(조건을 정의한다.)
	struct UdyrDeath : public UdyrTask
	{	// only condition
		virtual bool Condition() override;
		virtual void Do() override;
	};
	struct UdyrClick : public UdyrTask
	{	
		virtual bool Condition() override;
		virtual void Do() override;
	};
	struct UdyrRun : public UdyrTask
	{
		virtual bool Condition() override;
		virtual void Do() override;
	};
	struct UdyrTurn : public UdyrTask
	{
		virtual bool Condition() override;
		virtual void Do() override;
	};
	struct UdyrIdle : public UdyrTask
	{
		virtual bool Condition() override;
		virtual void Do() override;
	};
	struct UdyrAni : public UdyrTask
	{
		virtual bool Condition() override;
		virtual void Do() override;
	};
}
