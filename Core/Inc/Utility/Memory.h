#pragma once

#include <memory>


template<typename T>
using unique_ptr = std::unique_ptr<T>;

template<typename T>
using shared_ptr = std::shared_ptr<T>;

template<typename T>
using weak_ptr = std::weak_ptr<T>;

using std::make_unique;
using std::make_shared;

template<typename T>
struct RemoveReference
{
	using Type = T;
};

template<typename T>
struct RemoveReference<T&>
{
	using Type = T;
};

template<typename T>
struct RemoveReference<T&&>
{
	using Type = T;
};


template<typename T>
constexpr RemoveReference<T>::Type&& Move(T&& value)
{
	using Type = RemoveReference<T>::Type;

	return static_cast<Type&&>(value);
}


template<typename T>
constexpr T&& Forward(typename RemoveReference<T>::Type& value)
{
	return static_cast<T&&>(value);
}

template<typename T>
constexpr T&& Forward(typename RemoveReference<T>::Type&& value)
{
	return static_cast<T&&>(value);
}