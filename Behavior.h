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

	class Node {
	public:
		virtual bool Run() = 0;
		virtual void Release() = 0;
	};

	using ManyNodes = vector<Node*>;
	class Composite : public Node
	{
	public:
		ManyNodes GetComposites() const{ return m_Nodes; }
		void AddNode(Node* node) { m_Nodes.emplace_back(node); }
		//void AddManyNodes(initializer_list<Node*>&& nodes) {
		//	for (Node* it : nodes)	AddNode(it);
		//}
		ManyNodes GetCompositesShuffled() const {
			ManyNodes tmp = m_Nodes;
			random_shuffle(tmp.begin(),tmp.end());
			return tmp;
		}
		template<typename CONTAINER>
		void AddManyNodes(const CONTAINER& nodes) {
			for (Node* it : nodes)	AddNode(it);
		}
	protected:
		ManyNodes m_Nodes;
	};

	class Selctor : public Composite
	{
	public :
		virtual bool Run() override {
			for (Node* it : GetComposites())
				if (it->Run())	return true;
			return false;
		}
		virtual void Release() override {
			for (auto & it : m_Nodes)
				if (it != nullptr) delete it;
			m_Nodes.clear();
		}
	};

	class RandomSelector : public Composite
	{
	public :
		virtual bool Run() override {
			for (Node* it : GetCompositesShuffled())
				if (it->Run())	return true;
			return false;
		}
		virtual void Release() override {
			for (auto & it : m_Nodes)
				if (it != nullptr) delete it;
			m_Nodes.clear();
		}
	};

	class Sequence : public Composite
	{
	public:
		virtual bool Run() override {
			for (Node* it : GetComposites())
				if (!it->Run())	return false;
			return true;
		}
		virtual void Release() override {
			for (auto & it : m_Nodes)
				if (it != nullptr) delete it;
			m_Nodes.clear();
		}
	};

	class BehaviorTree
	{
	private:
		Node* m_Root = nullptr;
		BehaviorTree() {
			m_Root = new Sequence;
		}
		~BehaviorTree() {
			m_Root->Release();
			m_Root = nullptr;
		}
		bool Run() const { return m_Root->Run(); }
		void Release() {
			m_Root->Release();
			delete m_Root;
		}
	};
}