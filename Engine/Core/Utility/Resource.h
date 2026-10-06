#pragma once

#include "RefCounted.h"

class Resource : public RefCounted
{
public:
	String GetResourcePath() const
	{
		return resourcePath_;
	}

protected:
	friend class ResourceManager;

	void SetResourcePath(const String& path)
	{
		resourcePath_ = path;
	}

private:
	String resourcePath_;
};