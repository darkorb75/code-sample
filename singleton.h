// singleton class
//
// usage
//
// class TestSingleTon : public Singleton<TestSingleTon>
// {
// public:
//     void test() {}
// };
//
// int main()
// {
//     TestSingleTon::Instance().test();
// }

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <memory>
#include <mutex>

template <typename T>
class Singleton
{
public:
	static T& Instance()
	{
		std::call_once(singleton_flag_,
			[]()
			{
				instance_ = std::make_unique<T>();
			});

		return *instance_;
	}

	static void Destroy()
	{
		if (instance_)
			instance_.reset(nullptr);
	}

protected:
	Singleton() = default;
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

private:
	static std::unique_ptr<T> 	instance_;
	static std::once_flag 		singleton_flag_;
};

template<typename T>
std::unique_ptr<T> Singleton<T>::instance_;

template<typename T>
std::once_flag Singleton<T>::singleton_flag_;

#endif // __SINGLETON_H__
