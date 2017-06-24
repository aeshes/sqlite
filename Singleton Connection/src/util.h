#ifndef UTIL_H
#define UTIL_H

#include <memory>


template <typename T, typename Del = std::default_delete<T>>
inline auto raii_ptr(T* t, Del&& del = std::default_delete<T>)
{
	return std::unique_ptr<T, Del> {t, del};
}

template <typename T>
inline T& global_instance()
{
	static T instance;
	return instance;
}

#endif