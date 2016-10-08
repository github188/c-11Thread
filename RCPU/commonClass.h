#ifndef COMMON_CLASS
#define COMMON_CLASS
#include <mutex>

class AutoLock
{
public:
	AutoLock(std::mutex &mux)
	{
		m_mutex = &mux;
		(*m_mutex).lock();
	}
	~AutoLock()
	{
		(*m_mutex).unlock();
	}
private:
	std::mutex *m_mutex;
};
#endif
