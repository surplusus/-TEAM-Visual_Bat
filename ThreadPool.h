#pragma once
#define GET_THREADPOOL ThreadPool::GetInstance()
class ThreadPool {
private:
	static ThreadPool* Inst;
public:
	static ThreadPool* GetInstance()
	{
		if (Inst == NULL) Inst = new ThreadPool(10);
		return Inst;
	}
private:
	ThreadPool(std::size_t num_threads);
	~ThreadPool();
public:
	// job 을 추가한다.
	template <class F, class... Args>
	std::future<typename std::result_of<F(Args...)>::type> EnqueueFunc(THREADMENU eState,
		F&& f, Args&&... args);

	void Thread_Stop(THREADMENU eState)
	{
		if (m_worker_threads_[eState].joinable())
			m_worker_threads_[eState].detach();
	}

private:
	// 총 Worker 쓰레드의 개수.
	std::size_t m_num_threads_;
	// Worker 쓰레드를 보관하는 벡터.
	std::vector<std::thread> m_worker_threads_;
	// 할일들을 보관하는 job 큐.
	std::deque<std::function<void()>> m_jobs_;
	// 위의 job 큐를 위한 cv 와 m.
	std::condition_variable m_cv_job_q_;
	std::mutex m_job_q_;

	// 모든 쓰레드 종료
	bool m_stop_all;
	void StopThraed(THREADMENU eState);
	// Worker 쓰레드
	void WorkerThread();
};




template <class F, class... Args>
std::future<typename std::result_of<F(Args...)>::type> ThreadPool::EnqueueFunc(THREADMENU eState,
	F&& f, Args&&... args) {
	if (m_stop_all) {
		throw std::runtime_error("ThreadPool 사용 중지됨");
	}
	using return_type = typename std::result_of<F(Args...)>::type;
	auto job = std::make_shared<std::packaged_task<return_type()>>(
		std::bind(std::forward<F>(f), std::forward<Args>(args)...));

	std::future<return_type> job_result_future = job->get_future();
	{
		std::lock_guard<std::mutex> lock(m_job_q_);
		m_jobs_.push_front([job]() { (*job)(); });
	}
	m_cv_job_q_.notify_one();

	//오브젝트를 중지시키고 다시할당한다.
	if(m_worker_threads_[eState].joinable())
		m_worker_threads_[eState].detach();
	
	m_worker_threads_[eState] = thread(([this]() { this->WorkerThread(); }));
	
	return job_result_future;
}




