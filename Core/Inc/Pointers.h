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