#pragma once
#include "Behavior.h"

namespace BehaviorTree
{
	class UdyrWalkCond : public Condition
	{
	public:
		UdyrWalkCond()
			: Condition(this) {}
		virtual ~UdyrWalkCond() {}
	private:
		virtual bool Do() override {
			return m_BlackBoard.get()->getBool("Walk");
		}
	};

	class UdyrWalkTask : public Task
	{
	private:
		function<void(void)> m_Func;
	public:
		UdyrWalkTask(function<void(void)> func)
			:Task(this) {
			m_Func = func;
		}
		virtual ~UdyrWalkTask() {}
	private:
		virtual bool Do() override {
			m_Func();
			return true;
		}
	};

}
