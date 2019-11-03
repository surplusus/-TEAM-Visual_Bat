#pragma once
#include <memory>
#include <cassert>
namespace BehaviorTree
{
	class Node;
	class Task;
	class BlackBoard;
	using pBlackBoard = std::shared_ptr<BlackBoard>;

	enum Status
	{
		INVALID,
		SUCCESS,
		FAILURE,
		RUNNING
	};

	class Node {
	public:
		pBlackBoard* m_BlackBoard;
		virtual bool Run() = 0;
	};

	using ManyNodes = vector<Node*>;
	class Composite : public Node
	{
	public:
		Composite(pBlackBoard* blackboard) {
			m_BlackBoard = blackboard;
		}
		virtual ~Composite() { m_Nodes.clear(); }
	public:
		void AddNode(Node* node) {
			node->m_BlackBoard = this->m_BlackBoard;
			m_Nodes.emplace_back(node); }
		ManyNodes GetComposites() const{ return m_Nodes; }
		ManyNodes GetCompositesShuffled() const {
			ManyNodes tmp = m_Nodes;
			random_shuffle(tmp.begin(),tmp.end());
			return tmp;
		}
		template<typename CONTAINER>
		void AddManyNodes(const CONTAINER& nodes) {
			for (Node* it : nodes) {
				it->m_BlackBoard = this->m_BlackBoard;
				AddNode(it);
			}
		}
	protected:
		ManyNodes m_Nodes;
	};

	class Selector : public Composite
	{
	public:
		Selector(pBlackBoard* blackboard)
			: Composite(blackboard) {}
		virtual ~Selector() {}
	public :
		virtual bool Run() override {
			for (Node* it : GetComposites())
				if (it->Run())	return true;
			return false;
		}
	};

	class RandomSelector : public Composite
	{
	public:
		RandomSelector(pBlackBoard* blackboard)
			: Composite(blackboard) {}
		virtual ~RandomSelector() {}
	public :
		virtual bool Run() override {
			for (Node* it : GetCompositesShuffled())
				if (it->Run())	return true;
			return false;
		}
	};

	class Sequence : public Composite
	{
	public:
		Sequence(pBlackBoard* blackboard)
			: Composite(blackboard) {}
		virtual ~Sequence() {}
	public:
		virtual bool Run() override {
			for (Node* it : GetComposites())
				if (!it->Run())	return false;
			return true;
		}
	};

	// Condition & Task (Decorator)
	class Task : public Node
	{
	public:
		Task* m_pChild;
		Task(Task* child)
			: m_pChild(child) {}
		virtual ~Task() {}
		virtual bool Run() override {
			if (Condition())
				return m_pChild->Do();
			return false;
		}
		virtual bool Condition() = 0;
		virtual bool Do() = 0;
	};
	
	// BlackBoard
	class BlackBoard
	{
		
	public:
		void setBool(std::string key, bool value) { bools[key] = value; }
		bool getBool(std::string key)	{
			if (bools.find(key) == bools.end()) {
				bools[key] = false;
			}
			return bools[key];
		}
		bool hasBool(std::string key) const { return bools.find(key) != bools.end(); }

		void setInt(std::string key, int value) { ints[key] = value; }
		int getInt(std::string key)	{
			if (ints.find(key) == ints.end()) {
				ints[key] = 0;
			}
			return ints[key];
		}
		bool hasInt(std::string key) const { return ints.find(key) != ints.end(); }

		void setFloat(std::string key, float value) { floats[key] = value; }
		float getFloat(std::string key)	{
			if (floats.find(key) == floats.end()) {
				floats[key] = 0.0f;
			}
			return floats[key];
		}
		bool hasFloat(std::string key) const { return floats.find(key) != floats.end(); }

		void setDouble(std::string key, double value) { doubles[key] = value; }
		double getDouble(std::string key)	{
			if (doubles.find(key) == doubles.end()) {
				doubles[key] = 0.0f;
			}
			return doubles[key];
		}
		bool hasDouble(std::string key) const { return doubles.find(key) != doubles.end(); }

		void setString(std::string key, std::string value) { strings[key] = value; }
		std::string getString(std::string key)	{
			if (strings.find(key) == strings.end()) {
				strings[key] = "";
			}
			return strings[key];
		}
		bool hasString(std::string key) const { return strings.find(key) != strings.end(); }
	protected:
		std::unordered_map<std::string, bool> bools;
		std::unordered_map<std::string, int> ints;
		std::unordered_map<std::string, float> floats;
		std::unordered_map<std::string, double> doubles;
		std::unordered_map<std::string, std::string> strings;
	};

	class BehaviorTreeHandler
	{
	public:
		Node* m_Root;
		pBlackBoard m_BlackBoard;
	public:
		BehaviorTreeHandler() {
			m_BlackBoard = make_shared<BlackBoard>();
		}
		~BehaviorTreeHandler() {
			m_BlackBoard = nullptr;
			m_Root = nullptr;
		}
		bool Run() const { return m_Root->Run(); }
		BlackBoard& GetBlackBoard() { return *m_BlackBoard.get(); }
	};
}