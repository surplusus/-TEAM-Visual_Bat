#pragma once
class EventFunc {
public:
	void Execute(EVENT* evt) {
		Call(evt);
	}
private:
	virtual void Call(EVENT* evt) = 0;
};

template<typename T, typename EventType>
class EventFuncHandler : public EventFunc
{
public:
	typedef void (T::*MemberFunc)(EventType*);

	EventFuncHandler(T * instance, MemberFunc function)
		: m_Instance(instance), m_Function(function) {}

	void Call(EVENT * evt) {
		(m_Instance->*m_Function)(static_cast<EventType*>(evt));
	}
private:
	T* m_Instance;
	MemberFunc m_Function;
};