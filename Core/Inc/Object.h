#pragma once

#include "Math/Int.h"
#include "String/Name.h"


class Object
{
public:
	Object()
	{
		SetName(Name(Object::GetClassName(), true));
	}

	explicit Object(const Name& name) : name_(name) {}
	Object(const uint32 id, const Name& name) : id_(id), name_(name) {}

	virtual ~Object() = default;

	virtual bool Initialize();
	virtual void Shutdown() {}

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
	void SetName(const Name& name)
	{
		name_ = name;
	}

	void SetID(const uint32 id)
	{
		id_ = id;
	}

private:
	uint32 id_ = 0;
	Name name_;
};