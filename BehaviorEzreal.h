#pragma once
#include "Behavior.h"
#include <type_traits>
class CEzreal;

namespace EzrealBT
{
	using namespace BehaviorTree;

	enum { SEQUENCE_LIFE, SEQUENCE_END };
	enum { SELECTOR_ROOT, SELECTOR_END };
	enum { TASK_IDLE1, TASK_IDLE2, TASK_IDLE3 
		, TASK_ATTACK1, TASK_ATTACK2
		, TASK_SPELL1, TASK_SPELL2, TASK_SPELL3, TASK_SPELL4
		, TASK_RUN, TASK_DEATH, TASK_DEFAULT, TASK_ANIEND, TASK_END	};

	class EzrealBTHandler : public BehaviorTreeHandler
	{
	private:
		friend class CEzreal;
	public:
		EzrealBTHandler(CEzreal* pInst);
		EzrealBTHandler() {}
		~EzrealBTHandler();
		CEzreal*						m_pInst;
		vector<shared_ptr<Sequence>>	m_vSequnece;
		vector<shared_ptr<Selector>>	m_vSelector;
		vector<shared_ptr<Decorator>>	m_vDecorator;
		vector<shared_ptr<Task>>		m_vTask;

		void MakeTree();
		void SetUpBlackBoard();
		virtual void UpdateBlackBoard() override;

		template <typename T, typename enable_if<is_base_of<Task, T>::value, T>::type* = nullptr>
		inline Task* InsertTask() {
			auto task = make_shared<T>();
			task->SetMemberInst(m_pInst);
			task->m_BlackBoard = m_BlackBoard.get();
			m_vTask.emplace_back(static_pointer_cast<Task>(task));
			return m_vTask[m_vTask.size() - 1].get();
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
	class EzrealAccessor : public Task
	{
	public:
		EzrealAccessor() :Task(this) {}
		virtual ~EzrealAccessor() {}
		virtual void Init() override {}
		virtual void Do() override = 0;
		virtual void Terminate() override {}
		void SetMemberInst(CEzreal* pInst) { m_pInst = pInst; }
		void SetMemberFunc(string key, function<void(void)> func) {
			m_Funcs.insert(make_pair(key, func));
		}
	protected:
		CEzreal*	m_pInst = nullptr;
		map<string, MemberFunc> m_Funcs;
		// 밑에서 받아쓸 함수
		void ChangeAnySet(string key);
	};

#pragma region DECORATOR
	class WhenAlive : public Decorator
	{
		virtual bool Ask() override {
			if (!m_BlackBoard->getBool("Alive"))
				return false;
			return true;
		}
	};

	class WhenBoolOn : public Decorator
	{
	public:
		WhenBoolOn(string sKey) : m_bKey(sKey) {}
		virtual bool Ask() override {
			m_bTrigger = m_BlackBoard->getBool(m_bKey);
			return m_bTrigger;
		}
	private:
		bool m_bTrigger = false;
		string m_bKey;
	};

#pragma endregion

#pragma region EzrealTask 자식 클래스들
	struct EzrealIDLE1 : public EzrealAccessor
	{
		virtual void Init() override {}
		virtual void Do() override{}
		virtual void Terminate() override{}
	};
	struct EzrealIDLE2 : public EzrealAccessor
	{
		virtual void Init() override{}
		virtual void Do() override{}
		virtual void Terminate() override{}
	};
	struct EzrealIDLE3 : public EzrealAccessor
	{
		virtual void Init() override{}
		virtual void Do() override{}
		virtual void Terminate() override{}
	};
	struct EzrealATTACK1 : public EzrealAccessor
	{
		virtual void Init() override{}
		virtual void Do() override{}
		virtual void Terminate() override{}
	};
	struct EzrealATTACK2 : public EzrealAccessor
	{
		virtual void Init() override{}
		virtual void Do() override{}
		virtual void Terminate() override{}
	};
	struct EzrealSPELL1 : public EzrealAccessor
	{
		virtual void Init() override{}
		virtual void Do() override{}
		virtual void Terminate() override{}
	};
	struct EzrealSPELL2 : public EzrealAccessor
	{
		virtual void Init() override{}
		virtual void Do() override{}
		virtual void Terminate() override{}
	};
	struct EzrealSPELL3 : public EzrealAccessor
	{
		virtual void Init() override{}
		virtual void Do() override{}
		virtual void Terminate() override{}
	};
	struct EzrealSPELL4 : public EzrealAccessor
	{
		virtual void Init() override{}
		virtual void Do() override{}
		virtual void Terminate() override{}
	};
	struct EzrealRUN : public EzrealAccessor
	{
		virtual void Init() override{}
		virtual void Do() override{}
		virtual void Terminate() override{}
	};
	struct EzrealDEATH : public EzrealAccessor
	{
		virtual void Init() override{}
		virtual void Do() override{}
		virtual void Terminate() override{}
	};
	struct EzrealDEFAULT : public EzrealAccessor
	{
		virtual void Init() override{}
		virtual void Do() override{}
		virtual void Terminate() override{}
	};
	struct EzrealANIEND : public EzrealAccessor
	{
		virtual void Init() override{}
		virtual void Do() override{}
		virtual void Terminate() override{}
	};
#pragma endregion
}
