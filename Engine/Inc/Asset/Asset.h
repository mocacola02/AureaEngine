#pragma once

#include "../CoreInc.h"


class Asset : public RefCounted
{
public:
	//! Constructor using asset path.
	explicit Asset(const String& assetPath) : RefCounted(Name(assetPath)) {}

	~Asset() override = default;

	//! Returns the asset path.
	String GetAssetPath() const
	{
		return assetPath_;
	}

	//! Returns whether or not this asset is cached.
	bool IsCached() const
	{
		return cached_;
	}


protected:
	virtual bool Serialize() const = 0;
	virtual bool Deserialize() const = 0;


private:
	//! Whether or not this asset has been cached (aka is currently loaded in memory).
	bool cached_ = false;

	//! Path to the asset.
	//! Example: If a texture asset "FloorBricks" is stored in the package "BrickTex" and in the category "Floor",
	//! the path will be "BrickTex/Floor/FloorBricks".
	String assetPath_;
};