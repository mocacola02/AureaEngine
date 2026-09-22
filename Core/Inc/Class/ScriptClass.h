#pragma once

#include "../Containers/Array.h"
#include "../Containers/Dictionary.h"
#include "../Math/Math.h"
#include "../String/String.h"
#include "../String/Name.h"

enum class ValueType : uint8
{
	Void,		//void

	Bool,		//bool

	Byte,		//uint8
	Int,		//int32
	Long,		//int64

	Float,		//float
	Double,		//double

	String,		//String
	Name,		//Name

	Resource,	//Resource
	Class		//Class
};

struct ClassInfo
{
	String className;
	String parentName;

	Array<String> functions;
	Dictionary<String, String> properties;
};

struct ClassFunction
{
	//! Name of this function
	String name;

	//! Is this function static
	bool isStatic = false;

	//! Is this function private
	bool isPrivate = false;

	//! What type does this function return
	ValueType returnType = ValueType::Void;

	//! Dictionary of this function's arguments. Key = Argument name, Value = Argument type
	Dictionary<String, ValueType> arguments;
};

class ClassRegistry;

class ScriptClass
{
protected:
	friend class ClassRegistry;


};