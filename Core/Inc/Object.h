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

	[[nodiscard]] virtual constexpr String GetClassName() const
	{
		return "Object";
	}

	template<typename T>
	[[nodiscard]] bool IsOfType() const
	{
		return dynamic_cast<const T*>(this) != nullptr;
	}

protected:
	Object()
	{
		SetName(Name(Object::GetClassName(), true));
	}

	void SetName(const Name& name)
	{
		name_ = name;
	}

	void SetID(const uint32 id)
	{
		id_ = id;
	}

private:
	Name name_;
	uint32 id_ = 0;
};