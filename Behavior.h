#pragma once
#include <memory>
#include <cassert>
#include <deque>
namespace BehaviorTree
{
	class Node;
	class Task;
	class BlackBoard;
	using sharedpBlackBoard = std::shared_ptr<BlackBoard>;

	enum Status
	{
		INVALID,
		SUCCESS,
		RUNNING,
		TERMINATED,
	};

	class Node {
	public:
		BlackBoard* m_BlackBoard;
		virtual bool Run() = 0;
		Status m_status = INVALID;
	};

	using ManyNodes = vector<Node*>;
	class Composite : public Node
	{
	public:
		Composite(BlackBoard* pBlackboard) {
			m_BlackBoard = pBlackboard;
		}
		virtual ~Composite() { m_Nodes.clear(); }
	public:
		void AddNode(Node* node) {
			if (node == nullptr) {
				ERR_MSG(g_hWnd, L"Error on Addnode Function.");
				return;
			}
			node->m_BlackBoard = m_BlackBoard;
			m_Nodes.emplace_back(node); 
		}
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
		Selector(BlackBoard* pBlackboard)
			: Composite(pBlackboard) {}
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
		RandomSelector(BlackBoard* pBlackboard)
			: Composite(pBlackboard) {}
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
		Sequence(BlackBoard* pBlackboard)
			: Composite(pBlackboard) {}
		Sequence(const Sequence* pSqc)
			:Composite(pSqc->m_BlackBoard) {}
		virtual ~Sequence() {}
	public:
		virtual bool Run() override {
			for (Node* it : GetComposites())
				if (!it->Run())	return false;
			return true;
		}
	};

	// Decorator & Task
	class Task : public Node
	{
	public:
		Task(Task* pChild) : m_pChild(pChild) {}
		virtual ~Task() {}
		virtual bool Run() override {
			if (m_status == SUCCESS)
				Init();
			Do();
			if (m_status != RUNNING) {
				if (m_status == TERMINATED)
					Terminate();
				return false;
			} 
		}
		void SetStatus(Status status) { m_status = status; }
	private:
		virtual void Init() = 0;
		virtual void Do() = 0;
		virtual void Terminate() = 0;
		Task* m_pChild;
	};

	class Decorator : public Node
	{
	public:
		virtual ~Decorator() {}
		virtual bool Ask() = 0;
		bool Run() override {
			bool bAsk = Ask();
			WriteStatusInTask(bAsk);
			if (m_pTask->m_status == INVALID)
				return false;
			m_pTask->Run();
			return true;
		}
		void WriteStatusInTask(bool bSuccess) {
			if (!bSuccess) {
				if (m_pTask->m_status == TERMINATED)
					m_pTask->m_status = INVALID;
				if (m_pTask->m_status != INVALID)
					m_pTask->m_status = TERMINATED;
				return;
			}
			if (m_pTask->m_status == SUCCESS)
				m_pTask->m_status = RUNNING;
			if (m_pTask->m_status == INVALID)
				m_pTask->m_status = SUCCESS;
		}
		void SetTask(Node* pTask) { 
			m_pTask = pTask; 
			m_pTask->m_BlackBoard = m_BlackBoard; }
		bool HasTask() const { return m_pTask != nullptr; }
	protected:
		Node* m_pTask = nullptr;
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
	public:
		std::unordered_map<std::string, bool> bools;
		std::unordered_map<std::string, int> ints;
		std::unordered_map<std::string, float> floats;
		std::unordered_map<std::string, double> doubles;
		std::unordered_map<std::string, std::string> strings;
	};

	class BehaviorTreeHandler
	{
	public:
		Node*				m_Root;
		sharedpBlackBoard	m_BlackBoard;
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
		virtual void UpdateBlackBoard() = 0;
	};
}