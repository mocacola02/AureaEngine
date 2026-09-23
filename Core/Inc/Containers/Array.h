//===================================================
// Vector3.h
// Author: Moca 9/14/2026
// Defines an Array type that can be used to store
// an ordered list of values of any type.
//===================================================
#pragma once

#include <algorithm>

#include "../Math/Int.h"

#include <ranges>


//! Array type that can store an ordered list of values of any type. -Moca
template<typename T>
class Array
{

public:
	//! Default Array constructor
	Array() = default;

	//! Copy constructor
	Array(const Array& source)
	{
		if (source.count_ == 0)
		{
			return;
		}

		data_ = Allocate(source.count_);
		capacity_ = source.count_;

		for (uint32 i = 0; i < source.count_; ++i)
		{
			new (&data_[i]) T(source.data_[i]);

			++count_;
		}
	}

	//! Move constructor
	Array(Array&& source) noexcept : data_(source.data_), count_(source.count_), capacity_(source.capacity_)
	{
		source.data_ = nullptr;
		source.count_ = 0;
		source.capacity_ = 0;
	}

	//! Array destructor
	~Array()
	{
		DestroyElements();
		Deallocate(data_);
	}

	//! Copies a given value to the end of this Array.
	void Add(const T& value)
	{
		if (count_ >= capacity_)
		{
			Grow();
		}

		new (&data_[count_]) T(value);

		++count_;
	}

	//! Moves a given value to the end of this Array.
	void Add(T&& value)
	{
		if (count_ >= capacity_)
		{
			Grow();
		}

		new (&data_[count_]) T(static_cast<T&&>(value));

		++count_;
	}

	//! Inserts a given value at a given index.
	//! This does not replace the pre-existing value, pre-existing values are shifted back.
	void Insert(const T& value, const uint32 index)
	{
		if (count_ >= capacity_)
		{
			Grow();
		}

		for (uint32 i = count_ - 1; i >= index; --i)
		{
			data_[i + 1] = data_[i];
		}

		new (&data_[index]) T(static_cast<T&&>(value));

		++count_;
	}

	// AureaScript (or whatever I call it) will likely also have Append as an alias for Add().
	// For internal C++ use, I'd rather keep it to just a single alias to avoid inconsistent use.
	//! Copies a given value to the back (end) of the Array.
	//! Alias of Add().
	void PushBack(const T& value)
	{
		Add(value);
	}

	//! Moves a given value to the back (end) of the Array.
	//! Alias of Add().
	void PushBack(T&& value)
	{
		Add(static_cast<T&&>(value));
	}

	//! Copies a given value to the front of the Array (at index 0).
	void PushFront(const T& value)
	{
		Insert(value, 0);
	}

	//! Moves a given value to the front of the Array (at index 0).
	void PushFront(T&& value)
	{
		Insert(static_cast<T&&>(value), 0);
	}

	//! Allocates a new buffer of a given size, moving pre-existing elements and creating new ones as needed.
	//! Pre-existing elements will keep their original indices.
	//! New capacity must be larger than current capacity.
	void Reserve(const uint32 newCapacity)
	{
		if (newCapacity <= capacity_)
		{
			return;
		}

		T* newData = Allocate(newCapacity);

		for (uint32 i = 0; i < count_; ++i)
		{
			new (&newData[i]) T(static_cast<T&&>(data_[i]));

			data_[i].~T();
		}

		Deallocate(data_);

		data_ = newData;
		capacity_ = newCapacity;
	}

	//! Removes the element at the given index if present.
	void RemoveAt(const uint32 index)
	{
		if (index >= count_)
		{
			return;
		}

		for (uint32 i = index; i + 1 < count_; ++i)
		{
			data_[i] = static_cast<T&&>(data_[i + 1]);
		}

		data_[count_ - 1].~T();

		--count_;
	}

	//! Removes an element of a given value if present, returning whether or not it succeeded.
	bool Remove(const T& value)
	{
		for (uint32 i = 0; i < count_; ++i)
		{
			if (data_[i] == value)
			{
				RemoveAt(i);
				return true;
			}
		}

		return false;
	}

	//! Destroys the element at the end of the Array.
	void PopBack()
	{
		if (count_ == 0)
		{
			return;
		}

		RemoveAt(count_ - 1);
	}

	//! Destroys the element at the front of the Array (index 0).
	void PopFront()
	{
		if (count_ == 0)
		{
			return;
		}

		RemoveAt(0);
	}

	//! Shrinks this Array to match the current element count.
	void Shrink()
	{
		if (count_ == capacity_)
		{
			return;
		}

		if (count_ == 0)
		{
			Reset();
			return;
		}

		T* newData = Allocate(count_);

		for (uint32 i = 0; i < count_; ++i)
		{
			new (&newData[i]) T(static_cast<T&&>(data_[i]));

			data_[i].~T();
		}

		Deallocate(data_);

		data_ = newData;
		capacity_ = count_;
	}

	//! Resizes this Array to the given size. This creates/destroys elements as needed.
	void Resize(const uint32 newCount)
	{
		if (newCount < count_)
		{
			for (uint32 i = newCount; i < count_; ++i)
			{
				data_[i].~T();
			}

			count_ = newCount;
			return;
		}

		if (newCount > capacity_)
		{
			Reserve(newCount);
		}

		while (count_ < newCount)
		{
			new (&data_[count_]) T();

			++count_;
		}
	}

	//! Clears this Array by destroying all elements.
	void Clear()
	{
		DestroyElements();
	}

	//! Resets this Array by destroying all elements, deallocating data, and setting capacity to 0.
	void Reset()
	{
		DestroyElements();
		Deallocate(data_);

		data_ = nullptr;
		capacity_ = 0;
	}

	//! Sorts the Array based on the type.
	//! Numeric values are sorted smallest to largest.
	//! String/Name values are sorted alphabetically.
	//! Object references are sorted based on object name.
	//! Unsupported types will not change.
	// TODO: Implement this
	// void Sort()
	// {
	// }

	//! Returns the count of valid elements in this Array
	[[nodiscard]] constexpr uint32 Count() const
	{
		return count_;
	}

	//! Returns the capacity (valid elements + empty elements) of this Array
	[[nodiscard]] [[nodiscard]] constexpr uint32 Capacity() const
	{
		return capacity_;
	}

	//! Returns whether or not this Array is empty (aka count_ == 0)
	[[nodiscard]] [[nodiscard]] constexpr bool IsEmpty() const
	{
		return count_ == 0;
	}

	//! Returns whether or not a value is present in this Array
	bool Contains(const T& value) const
	{
		for (uint32 i = 0; i < count_; ++i)
		{
			if (data_[i] == value)
			{
				return true;
			}
		}

		return false;
	}

	//! Return whether or not a value is present in this Array, if true sets outIndex to the found index
	bool Find(const T& value, uint32& outIndex) const
	{
		for (uint32 i = 0; i < count_; ++i)
		{
			if (data_[i] == value)
			{
				outIndex = i;
				return true;
			}
		}

		return false;
	}


	// Data fetching
	//! Returns a pointer to the element buffer.
	constexpr T* Data()
	{
		return data_;
	}

	//! Returns a constant pointer to the element data buffer.
	constexpr const T* Data() const
	{
		return data_;
	}

	//! Returns the first element of the data buffer.
	T& First()
	{
		return data_[0];
	}

	//! Returns the first element of the data buffer as a constant.
	const T& First() const
	{
		return data_[0];
	}

	//! Returns the last element of the data buffer.
	T& Last()
	{
		return data_[count_ - 1];
	}

	//! Returns the last element of the data buffer as a constant.
	const T& Last() const
	{
		return data_[count_ - 1];
	}

	//! Appends and returns a new default-constructed element to the end of the Array.
	T& AddDefault()
	{
		if (count_ >= capacity_)
		{
			Grow();
		}

		T* element = &data_[count_];

		new (element) T();

		++count_;

		return *element;
	}

	//! Returns the data value at a given index.
	T& operator[](const uint32 index)
	{
		return data_[index];
	}

	//! Returns the data value at a given index as a constant.
	const T& operator[](const uint32 index) const
	{
		return data_[index];
	}

	T* begin()
	{
		return data_;
	}

	const T* begin() const
	{
		return data_;
	}

	T* end()
	{
		if (!data_)
		{
			return nullptr;
		}

		return data_ + count_;
	}

	const T* end() const
	{
		if (!data_)
		{
			return nullptr;
		}

		return data_ + count_;
	}


	//============
	// Operators
	//============

	//! Copies a source Array's data to this Array.
	Array& operator=(const Array& source)
	{
		if (this == &source)
		{
			return *this;
		}

		Clear();

		if (source.count_ > capacity_)
		{
			Deallocate(data_);

			data_ = Allocate(source.count_);

			capacity_ = source.count_;
		}

		for (uint32 i = 0; i < source.count_; ++i)
		{
			new (&data_[i]) T(source.data_[i]);

			++count_;
		}

		return *this;
	}

	//! Moves a source Array's data to this Array.
	Array& operator=(Array&& source) noexcept
	{
		if (this == &source)
		{
			return *this;
		}

		DestroyElements();

		Deallocate(data_);

		data_		= source.data_;
		count_		= source.count_;
		capacity_	= source.capacity_;

		source.data_	 = nullptr;
		source.count_	 = 0;
		source.capacity_ = 0;

		return *this;
	}

private:
	//! Pointer to this Array's data.
	T* data_ = nullptr;

	//! Number of valid elements in this Array.
	uint32 count_ = 0;
	//! Allocated buffer size of this Array.
	uint32 capacity_ = 0;

	//! Allocates a given capacity size for the data buffer and returns that buffer.
	static T* Allocate(const uint32 capacity)
	{
		if (capacity == 0)
		{
			return nullptr;
		}

		return static_cast<T*>(operator new(sizeof(T) * capacity));
	}

	//! Deallocates a given buffer.
	static void Deallocate(T* data)
	{
		operator delete(static_cast<void*>(data));
	}

	//! Destroys all elements in the data buffer and sets count to 0.
	void DestroyElements()
	{
		for (uint32 i = 0; i < count_; ++i)
		{
			data_[i].~T();
		}

		count_ = 0;
	}

	//! Calculates the grown capacity and reserves space according to it.
	void Grow()
	{
		const uint32 newCapacity = capacity_ == 0 ? 8 : capacity_ * 2;
		Reserve(newCapacity);
	}

};