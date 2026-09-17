#pragma once

#include "Math/Int.h"
#include "String/Name.h"


class Object
{
public:
	virtual ~Object() = default;

	[[nodiscard]] const Name& GetName() const
	{
		return name_;
	}

	[[nodiscard]] uint32 GetID() const
	{
		return id_;
	}

	template<typename T>
	[[nodiscard]] bool IsOfType() const
	{
		return dynamic_cast<const T*>(this) != nullptr;
	}

protected:
	Name name_;
	uint32 id_ = 0;

	Object() : id_(0) {}
	Object(const uint32 id, const Name& name) : id_(0), name_(name) {}
	explicit Object(const Name& name) : id_(0), name_(name) {}

	void SetName(const Name& name)
	{
		name_ = name;
	}

	void SetID(const uint32 id)
	{
		id_ = id;
	}
};