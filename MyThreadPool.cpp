#include "BaseInclude.h"
#include "MyThreadPool.h"	
ThreadPool* ThreadPool::Inst = NULL;
void ThreadPool::StopThraed(THREADMENU eState)
{

}
void ThreadPool::WorkerThread() {
	while (true) {
		std::unique_lock<std::mutex> lock(m_job_q_);
		m_cv_job_q_.wait(lock, [this]() { return !this->m_jobs_.empty() || m_stop_all; });
		if (m_stop_all && this->m_jobs_.empty()) {
			return;
		}

		// 맨 앞의 job 을 뺀다.
		std::function<void()> job = std::move(m_jobs_.front());
		m_jobs_.pop_front();
		lock.unlock();

		// 해당 job 을 수행한다 :)
		job();
	}
}

ThreadPool::ThreadPool(std::size_t num_threads)
	: m_num_threads_(num_threads), m_stop_all(false)
{
	m_worker_threads_.resize(m_num_threads_);
	for (int i = 0; i < m_worker_threads_.size();i++)
	{
		if (m_worker_threads_[i].joinable())
			m_worker_threads_[i].join();
	}
	
}

ThreadPool::~ThreadPool() {
	m_stop_all = true;
	m_cv_job_q_.notify_all();

	for (auto& t : m_worker_threads_) {
		t.join();
	}
}




// namespace ThreadPool