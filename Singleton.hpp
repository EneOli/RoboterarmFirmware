#ifndef __SINGLETON_HPP
#define __SINGLETON_HPP

template <class T> class TSingleton
{
public:
	static T* Get()
	{
		if (!m_instance)
			m_instance = new T;
		return m_instance;
	}

	static void Del()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = 0;
		}
	}

protected:
	static T* m_instance;
};

template <class T>
T* TSingleton<T>::m_instance = 0;
#endif
