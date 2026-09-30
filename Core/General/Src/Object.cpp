#include "../Inc/Object.h"

Name Object::GetName() const
{
	return name_;
}

uint64 Object::GetUUID() const
{
	return uuid_;
}

constexpr String Object::GetClassName() const
{
	return {"Object"};
}

template<typename ClassType>
bool Object::IsOfType() const
{
	return dynamic_cast<const ClassType*>(this) != nullptr;
}

Runtime* Object::GetRuntime() const
{
	return runtime_;
}

bool Object::Initialize()
{
	return true;
}

void Object::Shutdown()
{
	runtime_ = nullptr;
}

void Object::Delete()
{
	Shutdown();

	Runtime::DeleteObject(this);
}
