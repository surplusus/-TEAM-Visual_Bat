#pragma once
#include <memory>
#include <cassert>
namespace BehaviorTree
{
	class Node;
	class Task;

	enum Status
	{
		INVALID,
		SUCCESS,
		FAILURE,
		RUNNING
	};

	class Node
	{
	public:
		virtual Task* Init() = 0;
		virtual void Release() = 0;
		virtual ~Node() {}
	};

	class Task
	{
	public:
		Task(Node& node)
			: m_pNode(&node) {}
		virtual ~Task() {}
		virtual Status Progress() = 0;
		virtual void OnInit() {}
		virtual void OnRelease(Status) {}
	protected:
		Node* m_pNode;
	};

	class Behavior
	{
	protected:
		Task* m_pTask;
		Node* m_pNode;
		Status m_eStatus;
	public:
		Behavior()
			: m_pTask(nullptr)
			, m_pNode(nullptr)
			, m_eStatus(INVALID) {}
		Behavior(Node& node)
			: m_pTask(nullptr)
			, m_pNode(nullptr)
			, m_eStatus(INVALID) {
			SetUp(node);
		}
		~Behavior() {
			m_eStatus = INVALID;
			Release();
		}
		void SetUp(Node& node);
		void Release();
		Status Tick();
	};
}