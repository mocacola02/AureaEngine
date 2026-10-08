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
	explicit Object(Runtime* runtime) : runtime_(runtime) {}
	virtual ~Object() = default;

	virtual constexpr String GetClassName() const;

	void Delete();

	Name GetName() const;
	UUID GetUUID() const;

	template<typename Base>
	bool IsOfType() const;

	Runtime* GetRuntime();
	const Runtime* GetRuntime() const;

protected:
	friend class Runtime;
	friend class UUIDManager;

	virtual bool Initialize();
	virtual void Shutdown();

	void SetName(const Name& name);
	void SetUUID(const UUID &uuid);
	void SetUUID(uint64 uuid);

private:
	UUID uuid_ = UUID::None();
	Name name_;
	Runtime* runtime_ = nullptr;
};