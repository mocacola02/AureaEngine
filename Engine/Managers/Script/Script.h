#pragma once

#include "Core.h"
#include "ClassInfo.h"

class Script : public Resource
{
public:
	bool ScriptIsAbstract() const
	{
		return classInfo_.isAbstract;
	}

	bool ScriptIsPatch() const
	{
		return classInfo_.isPatch;
	}

	Name GetScriptClassName() const
	{
		return classInfo_.className;
	}

	Name GetScriptParentName() const
	{
		return classInfo_.parentName;
	}

	bool HasScriptFunction(const Name& functionName) const
	{
		return classInfo_.functions.ContainsKey(functionName);
	}

	ClassFunction GetScriptFunction(const Name& functionName) const
	{
		return classInfo_.functions.Get(functionName);
	}

	bool HasScriptProperty(const Name& propertyName) const
	{
		return classInfo_.properties.ContainsKey(propertyName);
	}

	ClassProperty GetScriptProperty(const Name& propertyName) const
	{
		return classInfo_.properties.Get(propertyName);
	}

protected:
	friend class ResourceManager;

	void SetClassInfo(const ClassInfo& classInfo)
	{
		classInfo_ = classInfo;
	}

private:
	ClassInfo classInfo_;

	String sourceCode_;
	String byteCode_;
};