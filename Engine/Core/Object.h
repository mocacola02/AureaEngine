#pragma once

#include "Math/Int.h"
#include "String/Name.h"
#include "Utility/Log.h"
#include "Utility/UUID.h"

class Runtime;

class Object
{
public:
	Object() = default;

	explicit Object(Runtime* runtime) : runtime_(runtime)
	{
		if (!runtime)
		{
			ERROR("New object was not given a pointer to the runtime!!!");

			// CONSIDER: Do some research on if self-deletion is safe
			// gun emoji
			delete this;
			return;
		}
	}

	virtual ~Object() = default;

	Name GetName() const;

	UUID& GetUUID() const;

	virtual constexpr String GetClassName() const;

	template<typename T>
	bool IsOfType() const;

	Runtime* GetRuntime() const;

protected:
	friend class Runtime;
	friend class UUIDManager;

	virtual bool Initialize();
	virtual void Shutdown();

	void Delete();

	void SetName(const Name& name);
	void SetUUID(UUID uuid);
	void SetUUID(uint64 uuid);

private:
	UUID uuid_ = UUID(0);
	Name name_;
	Runtime* runtime_ = nullptr;
};