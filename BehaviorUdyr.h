#pragma once
#include "Behavior.h"
#include <type_traits>
class CUdyr;

namespace UdyrBT
{
	using namespace BehaviorTree;
	
	enum {SEQUENCE_LIFE, SEQUENCE_MOVE, SEQUENCE_END};
	enum {SELECTOR_DEATH, SELECTOR_INPUT, SELECTOR_SKILL, SELECTOR_ENEMY, SELECTOR_AGGRESSIVE, SELECTOR_END};
	//enum {DECORATOR_YES, DECORATOR_REPEAT, DECORATOR_BOOLON, DECORATOR_FLOATLOW, DECORATOR_FLOATABOVE, DECORATOR_END};
	enum {TASK_DEATH, TASK_BEATEN, CONDITION_ONTARGET, CONDITION_HASCOORD
		, TASK_ATTACK, TASK_IDLE, TASK_QACTION
		, TASK_RUN, TASK_TURN, TASK_END};
	class UdyrBTHandler : public BehaviorTreeHandler
	{
	private:
		friend class CUdyr;
	public:
		UdyrBTHandler(CUdyr* pInst);
		~UdyrBTHandler();
		CUdyr*							m_pInst;
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
		bool TurnSlowly(const D3DXVECTOR3 * destPos, float fLerpRate);
		D3DXVECTOR3& GetChampMousePickPos();
		STATUSINFO& GetStatusInfo() const;
		UdyrBTHandler*	GetBehaviorTree();
		SPHERE* GetEnemySphere();
	};

#pragma region DECORATOR
	class WhenAlive : public Decorator
	{
		virtual bool Ask() override {
			if (!m_BlackBoard->getBool("Alive"))
				return false;
			return true; }
	};

	class WhenTillEnd : public Decorator
	{
	public:
		WhenTillEnd(string sKey, int iLimit = 0) 
			: m_sKey(sKey), m_iLimit(iLimit) {}
		virtual bool Ask() override {
			if (!m_bStartSign)
				m_bStartSign = m_BlackBoard->getBool(m_sKey);
			else
				if (m_iLimit > 0 && ++m_iCount <= m_iLimit)
					return true;
			m_bStartSign = false;
			return false;
		}
	protected:
		string m_sKey;
		bool m_bStartSign = false;
		int m_iLimit;
		int m_iCount = 0;
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
			if (bLesserThan = false)
				result = ~result;
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
			float fValue =  fabs(m_BlackBoard->getFloat(m_bKey));
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
	struct UdyrDeath : public UdyrAccessor
	{
		int iCntAni = 0;
		virtual void Init() override;
		virtual void Do() override;
		virtual void Terminate() override;
	};
	struct UdyrBeaten : public UdyrAccessor
	{
		virtual void Do() override;
		virtual void Terminate() override;
	};
	struct UdyrOnTarget : public UdyrAccessor
	{
		SPHERE*	spEnemy = nullptr;
		bool bNewTarget = false;
		virtual void Init() override;
		virtual void Do() override;
		virtual void Terminate() override;
	};
	struct UdyrHasCoord : public UdyrAccessor
	{
		D3DXVECTOR3	vecPrevPos;
		bool bNewPos = false;
		virtual void Init() override;
		virtual void Do() override;
		virtual void Terminate() override;
	};
	struct UdyrAttack : public UdyrAccessor
	{
		int iCntAni = 0;
		virtual void Init() override;
		virtual void Do() override;
		virtual void Terminate() override;
	};
	struct UdyrIdle : public UdyrAccessor
	{
		virtual void Init() override;
		virtual void Do() override;
	};
	struct UdyrQAction : public UdyrAccessor
	{
		virtual void Init() override;
		virtual void Do() override;
		virtual void Terminate() override;
	};
	struct UdyrTargeting : public UdyrAccessor
	{
		D3DXVECTOR3 vecPrevTargetPos;
		bool bNewTarget = true;
		virtual void Init() override;
		virtual void Do() override;
		virtual void Terminate() override;
	};
	struct UdyrSetCoord : public UdyrAccessor
	{
		virtual void Init() override;
		virtual void Do() override;
		virtual void Terminate() override;
	};
	struct UdyrRun : public UdyrAccessor
	{
		bool bRunning = false;
		virtual void Init() override;
		virtual void Do() override;
		virtual void Terminate() override;
	};
	struct UdyrTurn : public UdyrAccessor
	{
		virtual void Do() override;
	};
#pragma endregion
}
