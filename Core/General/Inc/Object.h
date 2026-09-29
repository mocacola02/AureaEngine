#pragma once

#include "../../Math/Inc/Int.h"
#include "../../String/Inc/Name.h"


class Object
{
public:
	Object()
	{
		SetName(Name(Object::GetClassName(), true));
	}

	explicit Object(const Name& name) : name_(name) {}
	Object(const uint64 uuid, const Name& name) : uuid_(uuid), name_(name) {}

	virtual ~Object() = default;

	virtual bool Initialize();
	virtual void Shutdown() {}

	[[nodiscard]] const Name& GetName() const
	{
		return name_;
	}

	[[nodiscard]] uint64 GetUUID() const
	{
		return uuid_;
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

private:
	uint64 uuid_ = 0;
	Name name_;

	void SetName(const Name& name)
	{
		name_ = name;
	}

	void SetUUID(const uint32 uuid)
	{
		uuid_ = uuid;
	}
};