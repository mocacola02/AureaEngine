#include "Object.h"
#include "Runtime.h"

constexpr String Object::GetClassName() const
{
	return "Object";
}

void Object::Delete()
{
	runtime_->DeleteObject(this);
}

Name Object::GetName() const
{
	return name_;
}

UUID Object::GetUUID() const
{
	return uuid_;
}

template<typename Base>
bool Object::IsOfType() const
{
	return dynamic_cast<Base>(this) != nullptr;
}

Runtime* Object::GetRuntime()
{
	return runtime_;
}

const Runtime *Object::GetRuntime() const
{
	return runtime_;
}

bool Object::Initialize()
{
	SetName(Name(GetClassName(), true));
	return GetRuntime() != nullptr;
}

void Object::Shutdown()
{
	runtime_ = nullptr;
}

void Object::SetName(const Name& name)
{
	name_ = name;
}

void Object::SetUUID(const UUID& uuid)
{
	uuid_ = uuid;
}

void Object::SetUUID(const uint64 uuid)
{
	uuid_ = uuid;
}