#pragma once
#include "Behavior.h"
class CMeleeMinion;

namespace MeleeMinionBT
{
	using namespace BehaviorTree;

	enum { SEQUENCE_LIFE, SEQUENCE_MOVE, SEQUENCE_END };
	enum { SELECTOR_DEATH, SELECTOR_FOLLOW, SELECTOR_AGGRESSIVE, SELECTOR_END };
	enum {
		TASK_DEATH, TASK_BEATEN, TASK_ATTACK, DECORATOR_AGGRESSIVE
		, TASK_NEXTPOS, TASK_RUN, TASK_TURN, TASK_IDLE, TASK_END
	};

	class MinionBTHandler : public BehaviorTreeHandler
	{
	public:
		MinionBTHandler(CMeleeMinion* pInst);
		~MinionBTHandler();
		CMeleeMinion*					m_pInst;
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
	class MinionAccessor : public Task
	{
	public:
		MinionAccessor() :Task(this) {}
		virtual ~MinionAccessor() {}
		virtual void Init() override {}
		virtual void Do() override = 0;
		virtual void Terminate() override {}
		void SetMemberInst(CMeleeMinion* pInst) { m_pInst = pInst; }
		void SetMemberFunc(string key, function<void(void)> func) {
			m_Funcs.insert(make_pair(key, func));
		}
	protected:
		CMeleeMinion*	m_pInst = nullptr;
		map<string, MemberFunc> m_Funcs;
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

	class WhenEnemyNear : public Decorator
	{
	public:
		WhenEnemyNear(CMeleeMinion* me, float fSearchRange)
			: m_MyInst(me), m_fSearchRange(fSearchRange) {}
		virtual bool Ask() override;
	protected:
		SPHERE* m_spTarget;
		CMeleeMinion* m_MyInst;
		float m_fSearchRange;
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

	class WhenFloatLow : public Decorator
	{
	public:
		WhenFloatLow(string sKey, float fLimit)
			: m_bKey(sKey), m_fLimit(fLimit) {}
		virtual bool Ask() override {
			float fValue = m_BlackBoard->getFloat(m_bKey);
			if (fValue <= m_fLimit)
				return true;
			return false;
		}
	private:
		string m_bKey;
		float m_fLimit;
	};

	class WhenFloatChecked : public Decorator
	{
	public:
		WhenFloatChecked(string sInputKey, string sStdKey, bool bLesserThan = true)
			: m_sInputKey(sInputKey), m_sStdKey(sStdKey), bLesserThan(bLesserThan) {}
		virtual bool Ask() override {
			float fStdValue = m_BlackBoard->getFloat(m_sStdKey);
			float fInputValue = m_BlackBoard->getFloat(m_sInputKey);
			bool result = true;
			if (fInputValue <= fStdValue)
				result = true;
			else
				result = false;

			if (bLesserThan == false)
				result = !result;
			return result;
		}
	private:
		string m_sInputKey;
		string m_sStdKey;
		bool bLesserThan;
	};

	class WhenFloatAbove : public Decorator
	{
	public:
		WhenFloatAbove(string sKey, float fLimit)
			: m_bKey(sKey), m_fLimit(fLimit) {}
		virtual bool Ask() override {
			float fValue = fabs(m_BlackBoard->getFloat(m_bKey));
			if (fValue >= m_fLimit)
				return true;
			return false;
		}
	private:
		string m_bKey;
		float m_fLimit;
	};
#pragma endregion


#pragma region UdyrTask 자식 클래스들
	struct MinionDeath : public MinionAccessor
	{
		int iCntAni = 0;
		int iSoundSec = 3;
		virtual void Init() override;
		virtual void Do() override;
		virtual void Terminate() override;
	};
	struct MinionBeaten : public MinionAccessor
	{
		virtual void Do() override;
		virtual void Terminate() override;
	};
	struct MinionAttack : public MinionAccessor
	{
		int iCntAni = 0;
		virtual void Init() override;
		virtual void Do() override;
		virtual void Terminate() override;
	};
	struct MinionAggressive : public MinionAccessor
	{
		D3DXVECTOR3 	vecEnemy = D3DXVECTOR3(0,0,0);
		bool bNewTarget = false;
		virtual void Init() override;
		virtual void Do() override;
		virtual void Terminate() override;
	};
	struct MinionNextPos : public MinionAccessor
	{
		size_t m_Idx = 0;
		virtual void Do() override;
		virtual void Terminate() override;
	};
	struct MinionRun : public MinionAccessor
	{
		D3DXVECTOR3 m_vecNextPos = D3DXVECTOR3(0,0,0);
		virtual void Init() override;
		virtual void Do() override;
		virtual void Terminate() override;
	};
	struct MinionTurn : public MinionAccessor
	{
		D3DXVECTOR3 m_vecNextPos = D3DXVECTOR3(0, 0, 0);
		virtual void Init() override;
		virtual void Do() override;
		virtual void Terminate() override;
	};
	struct MinionIdle : public MinionAccessor
	{
		virtual void Init() override;
		virtual void Do() override;
	};
#pragma endregion
}
