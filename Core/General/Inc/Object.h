#pragma once

#include "../../Math/Inc/Int.h"
#include "../../String/Inc/Name.h"
#include "../../Utility/Inc/Log.h"

class Runtime;

class Object
{
public:
	Object() = default;

	explicit Object(Runtime* runtime) : runtime_(runtime)
	{
		if (!runtime)
		{
			ERROR(String("New object was not given a pointer to the runtime!!!"));
			// gun emoji
			// CONSIDER: Do some research on if self-deletion is safe
			delete this;
		}

		SetName(Name(Object::GetClassName(), true));
	}

	virtual ~Object() = default;

	Name GetName() const;

	uint64 GetUUID() const;

	virtual constexpr String GetClassName() const;

	template<typename T>
	bool IsOfType() const;

	Runtime* GetRuntime() const;

protected:
	friend class Runtime;

	virtual bool Initialize();
	virtual void Shutdown();

	void Delete();

	void SetName(const Name& name);
	void SetUUID(uint32 uuid);

private:
	uint64 uuid_ = 0;
	Name name_;
	Runtime* runtime_ = nullptr;
};