#pragma once
#include "Behavior.h"
#include <type_traits>
class CUdyr;

namespace UdyrBT
{
	using namespace BehaviorTree;

	enum {SEQUENCE_ROOT, SEQUENCE_RUN, SEQUENCE_END};
	enum {SELECTOR_DEATH, SELECTOR_RUN, SELECTOR_END};
	enum {DECORATOR_REPEATER, DECORATOR_WHENTRUE, DECORATOR_END};
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
		CUdyr*							m_pInst;
		vector<shared_ptr<Sequence>>	m_vSequnece;
		vector<shared_ptr<Selector>>	m_vSelector;
		vector<shared_ptr<Decorator>>	m_vDecorator;
		vector<shared_ptr<Task>>		m_vTask;

		void SetRoot(int eNode); 
		void MakeTree();
		void SetUpBlackBoard();
		virtual void UpdateBlackBoard() override;
		void SetUpTask(int eTaskType, function<void(void)> pFunc);

		template <typename T, typename enable_if<is_base_of<Task, T>::value, T>::type* = nullptr>
		inline Task* InsertTask() {
			auto task = make_shared<T>();
			task->SetMemberInst(m_pInst);
			task->m_BlackBoard = m_BlackBoard.get();
			m_vTask.emplace_back(static_pointer_cast<Task>(task));
			return m_vTask[m_vTask.size()-1].get();
		}
		template <typename U, typename enable_if<is_base_of<Decorator, U>::value, U>::type* = nullptr, typename... Args>
		inline void InsertDecorate(Task* pTask, Args &&... args) {
			auto deco = make_shared<U>(std::forward<Args>(args)...);
			deco->m_BlackBoard = m_BlackBoard.get();
			deco.get()->SetTask(static_cast<Node*>(pTask));
			m_vDecorator.emplace_back(move(deco));
		}
	};

	using MemberFunc = function<void(void)>;
	class UdyrAccessor : public Task
	{
	public:
		UdyrAccessor() :Task(this) {}
		virtual ~UdyrAccessor() {}
		virtual void Init() override {}
		virtual void Do() override = 0;
		virtual void Terminate() override {}
		void SetMemberInst(CUdyr* pInst) { m_pInst = pInst; }
		void SetMemberFunc(string key, function<void(void)> func) { 
			m_Funcs.insert(make_pair(key, func));
		}
	protected:
		CUdyr*	m_pInst = nullptr;
		map<string, MemberFunc> m_Funcs;
		// 밑에서 받아쓸 함수
		void ChangeAnySet(string key);
	};

	/*class UdyrCondition : public Condition
	{
	protected:
		CUdyr*	m_pInst = nullptr;
	public:
		UdyrCondition() : Task(this) {}
		virtual ~UdyrCondition() {}
		virtual bool Run() = 0;
		virtual Status Ask() = 0;
		void SetMemberInst(CUdyr* pInst) { m_pInst = pInst; }
	};*/

#pragma region DECORATOR
	class Successor : public Decorator
	{
		virtual bool Ask() override { return true; }
	};

	class Repeater : public Decorator
	{
	public:
		Repeater(int iLimit = 0) : m_iLimit(iLimit) {}
		virtual bool Ask() override {
			return (m_iLimit > 0 && ++m_iCount <= m_iLimit);
		}
	protected:
		int m_iLimit;
		int m_iCount = 0;
	};

	class BoolChecker : public Decorator
	{
	public:
		BoolChecker(string sKey) : m_bKey(sKey) {}
		virtual bool Ask() override {
			m_bTrigger = m_BlackBoard->getBool(m_bKey);
			return m_bTrigger;
		}
	private:
		bool m_bTrigger = false;
		string m_bKey;
	};
#pragma endregion

#pragma region UdyrTask 자식 클래스들
	struct UdyrDeath : public UdyrAccessor
	{
		virtual void Init() override {}
		virtual void Do() override;
		virtual void Terminate() override;
	};
	//struct UdyrClick : public UdyrTask
	//{	
	//	virtual bool Condition() override;
	//	virtual void Do() override;
	//};
	//struct UdyrRun : public UdyrTask
	//{
	//	virtual bool Condition() override;
	//	virtual void Do() override;
	//};
	//struct UdyrTurn : public UdyrTask
	//{
	//	virtual bool Condition() override;
	//	virtual void Do() override;
	//};
	//struct UdyrIdle : public UdyrTask
	//{
	//	virtual bool Condition() override;
	//	virtual void Do() override;
	//};
	//struct UdyrAni : public UdyrTask
	//{
	//	virtual bool Condition() override;
	//	virtual void Do() override;
	//};

	//// UdyrCondition 자식 클래스들(조건을 정의한다.)
	//struct UdyrAni : public UdyrCondition
	//{
	//	virtual bool Condition() override;
	//	virtual void Do() override;
	//};
	//struct UdyrAni : public UdyrCondition
	//{
	//	virtual bool Condition() override;
	//	virtual void Do() override;
	//};

}
