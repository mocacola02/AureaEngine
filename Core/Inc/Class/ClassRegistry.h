#pragma once

#include "../Object.h"
#include "../Containers/Dictionary.h"
#include "../String/Name.h"


enum class ClassType : uint8
{
	Unknown,
	CPP,
	AureaScript,
	Custom
};

struct ClassInfo
{
	Name name;
	ClassType type = ClassType::CPP;
};

class ClassRegistry final : public Object
{
public:
	void Register(const Name& className, const ClassType classType)
	{
		classes_[className] = {.name = className, .type = classType};
	}

	[[nodiscard]] const ClassInfo* Get(const Name& className) const
	{
		const ClassInfo* temp = classes_.Find(className);

		if (!temp)
		{
			return nullptr;
		}

		return temp;
	}

	[[nodiscard]] bool HasClass(const Name& className) const
	{
		return Get(className) != nullptr;
	}

private:
	Dictionary<Name, ClassInfo> classes_;
};
