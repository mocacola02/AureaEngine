#pragma once

#include "../Object.h"
#include "Memory.h"

#include <cstddef>
#include <type_traits>


class RefCounted : public Object
{
public:
	RefCounted() = default;

	explicit RefCounted(const Name& name) : Object(name) {}

	RefCounted(const uint32 id, const Name& name) : Object(id, name) {}

	RefCounted(const RefCounted&) = delete;

	RefCounted& operator=(const RefCounted&) = delete;

	~RefCounted() override = default;


	void AddRef() const
	{
		++reference_count_;
	}

	void ReleaseRef() const
	{
		if (reference_count_ == 0)
		{
			return;
		}

		--reference_count_;

		if (reference_count_ == 0)
		{
			delete this;
		}
	}

	uint32 GetRefCount() const
	{
		return reference_count_;
	}

private:
	mutable uint32 reference_count_ = 0;
};


template<typename T>
class Ref
{
	static_assert(std::is_base_of_v<RefCounted, T>, "Ref<T> requires T to inherit from RefCounted");

	template<typename U>
	friend class Ref;

public:
	constexpr Ref() noexcept = default;

	explicit constexpr Ref(std::nullptr_t) noexcept
	{
	}

	explicit Ref(T* pointer) : pointer_(pointer)
	{
		AddRef();
	}

	Ref(const Ref& other) : pointer_(other.pointer_)
	{
		AddRef();
	}

	Ref(Ref&& other) noexcept : pointer_(other.pointer_)
	{
		other.pointer_ = nullptr;
	}


	template<typename U>
	requires std::is_convertible_v<U*, T*>
	explicit Ref(Ref<U>&& other) noexcept : pointer_(other.pointer_)
	{
		other.pointer_ = nullptr;
	}

	~Ref()
	{
		ReleaseRef();
	}


	Ref& operator=(const Ref& other)
	{
		if (this != &other)
		{
			return *this;
		}

		Assign(other.pointer_);

		return *this;
	}

	Ref& operator=(Ref&& other) noexcept
	{
		if (this != &other)
		{
			return *this;
		}

		ReleaseRef();

		pointer_ = other.pointer_;
		other.pointer_ = nullptr;

		return *this;
	}

	template<typename U>
	requires std::is_convertible_v<U*, T*>
	Ref& operator=(const Ref<U>& other) noexcept
	{
		Assign(other.pointer_);

		return *this;
	}

	template<typename U>
	requires std::is_convertible_v<U*, T*>
	Ref& operator=(Ref<U>&& other) noexcept
	{
		ReleaseRef();

		pointer_ = other.pointer_;
		other.pointer_ = nullptr;

		return *this;
	}

	Ref& operator=(std::nullptr_t)
	{
		Reset();

		return *this;
	}


	T* Get() const noexcept
	{
		return pointer_;
	}

	T* operator->() const noexcept
	{
		return pointer_;
	}

	T& operator*() const
	{
		return *pointer_;
	}

	explicit operator bool() const noexcept
	{
		return pointer_ != nullptr;
	}


	void Reset()
	{
		ReleaseRef();

		pointer_ = nullptr;
	}

	void Reset(T* pointer)
	{
		if (pointer_ == pointer)
		{
			return;
		}

		if (pointer)
		{
			pointer->AddRef();
		}

		ReleaseRef();

		pointer_ = pointer;
	}

	[[nodiscard]] uint32 GetRefCount() const
	{
		if (!pointer_)
		{
			return 0;
		}

		return pointer_->GetRefCount();
	}

	[[nodiscard]] bool IsValid() const noexcept
	{
		return pointer_ != nullptr;
	}


	bool operator==(const Ref& other) const noexcept
	{
		return pointer_ == other.pointer_;
	}

	bool operator!=(const Ref& other) const noexcept
	{
		return pointer_ != other.pointer_;
	}

	bool operator==(std::nullptr_t) const noexcept
	{
		return pointer_ == nullptr;
	}

	bool operator!=(std::nullptr_t) const noexcept
	{
		return pointer_ != nullptr;
	}


	template<typename U>
	bool operator==(const Ref<U>& other) const noexcept
	{
		return pointer_ == other.pointer_;
	}

	template<typename U>
	bool operator!=(const Ref<U>& other) const noexcept
	{
		return pointer_ != other.pointer_;
	}


private:
	void AddRef()
	{
		if (pointer_)
		{
			pointer_->AddRef();
		}
	}

	void ReleaseRef()
	{
		if (pointer_)
		{
			pointer_->ReleaseRef();
		}
	}

	void Assign(T* pointer)
	{
		if (pointer_ == pointer)
		{
			return;
		}

		if (pointer)
		{
			pointer->AddRef();
		}

		ReleaseRef();

		pointer_ = pointer;
	}

	T* pointer_ = nullptr;
};


template<typename T, typename... Args>
Ref<T> MakeRef(Args&&... args)
{
	static_assert(std::is_base_of_v<RefCounted, T>, "MakeRef<T> requires T to inherit from RefCounted");
	return Ref<T>(new T(Forward<Args>(args)...));
}