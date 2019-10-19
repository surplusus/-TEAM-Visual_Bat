#pragma once
#include "EventFunctionHandler.h"
#include <typeindex>

class EventFunc;
typedef std::list<EventFunc*> EventFuncList;

class EventMgr
{
	DECLARE_SINGLETON(EventMgr);
private:
	EventMgr() {}
	~EventMgr() {}
private:
	std::map < std::type_index, EventFuncList*> subscribers;
public:
	template<typename EventType>
	void Publish(EventType * evt) {
		EventFuncList* funcList = subscribers[typeid(EventType)];

		if (funcList == nullptr)	return;

		for (auto& it : *funcList)
			if (it != nullptr)
				it->Execute(evt);
	}
	template<typename T, typename EventType>
	void Subscribe(T* instance, void (T::*memberFunction)(EventType*)) {
		EventFuncList * funcList = subscribers[typeid(EventType)];

		if (funcList == nullptr) {
			funcList = new EventFuncList();
			subscribers[typeid(EventType)] = funcList;
		}
		funcList->push_back(new EventFuncHandler<T, EventType>(instance, memberFunction));
	}
	template<typename T, typename EventType>
	void Unsubscribe(T* instance, void (T::*memberFunction)(EventType*)) {
		EventFuncList * funcList = subscribers[typeid(EventType)];
		if (funcList == nullptr)	return;
		funcList->clear();
	}
};

