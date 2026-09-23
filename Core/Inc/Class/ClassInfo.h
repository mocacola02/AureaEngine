#pragma once

#include "../Containers/Dictionary.h"
#include "../Math/Math.h"
#include "../String/String.h"
#include "../String/Name.h"

//! Value types supported by AureaScript.
enum class ValueType : uint8
{
	Void,		//void

	Bool,		//bool

	Byte,		//uint8
	Short,		//int16
	Int,		//int32
	Long,		//int64

	Float,		//float
	Double,		//double

	String,		//String
	Name,		//Name

	Resource,	//Resource
	Class		//Class
};

//! Represents a function of a class.
struct ClassFunction
{
	//! Is this function imported from native C++?
	bool isImported = false;

	//! Is this function static.
	bool isStatic = false;

	//! Is this function private.
	bool isPrivate = false;

	//! Can this function be overriden in child classes.
	bool isOverridable = true;

	//! Can this function be patched by other packages.
	bool isPatchable = true;

	//! What type does this function return.
	ValueType returnType = ValueType::Void;

	//! Dictionary of this function's arguments. Key = Argument name, Value = Argument type
	Dictionary<Name, ValueType> arguments;
};

//! Represents a property of a class.
struct ClassProperty
{
	//! Is this property constant.
	bool isConstant = false;

	//! Is this property able to be changed in AureaEd.
	bool isEditable = true;

	//! Value type of this property.
	ValueType propertyType = ValueType::Bool;

	//! Default value of this property.
	String defaultValue = "false";
};

//! Stores general information about a class.
struct ClassInfo
{
	//! Is this class abstract.
	bool isAbstract = false;

	//! Is this class acting as a patch for another class.
	bool isPatch = false;

	//! Name of this class.
	Name className;

	//! Name of this class' parent.
	Name parentName;

	//! Functions of this class.
	Dictionary<Name, ClassFunction> functions;

	//! Properties of this class.
	Dictionary<Name, ClassProperty> properties;
};