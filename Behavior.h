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
	protected:
		pBlackBoard* m_BlackBoard;
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
		virtual void Release() override{
			for (auto & it : m_Nodes) {
				it->Release();
				SAFE_DELETE(it);
			}
			m_Nodes.clear();
		}
	protected:
		ManyNodes m_Nodes;
	};

	class Selector : public Composite
	{
	public :
		virtual bool Run() override {
			for (Node* it : GetComposites())
				if (it->Run())	return true;
			return false;
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
	};

	class Sequence : public Composite
	{
	public:
		virtual bool Run() override {
			for (Node* it : GetComposites())
				if (!it->Run())	return false;
			return true;
		}
	};

	// Condition & Task (Decorator)
	class Condition : public Node
	{
	private:
		Condition* m_pChild;
	public:
		Condition(Condition* child)
			: m_pChild(child) {}
		virtual ~Condition() {}
		virtual void Release() override {}
		virtual bool Run() override {
			return m_pChild->Do();
		}
		virtual bool Do() = 0;
	};

	class Task : public Node
	{
	public:
		Task* m_pChild;
	public:
		Task(Task* child)
			: m_pChild(child) {}
		virtual ~Task() {}
		virtual void Release() override {}
		virtual bool Run() override {
			return m_pChild->Do();
		}
		virtual bool Do() = 0;
	};

	class BehaviorTree
	{
	private:
		Node* m_Root;
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
}