#pragma once

#include "../Containers/Dictionary.h"
#include "../Math/Int.h"
#include "../Utility/Hash.h"

class NameTable
{
public:
	NameTable() : entryCount_(1), entryCapacity_(64), bucketCapacity_(128)
	{
		entries_ = new Entry[entryCapacity_];
		buckets_ = new uint32[bucketCapacity_];

		for (uint32 i = 0; i < bucketCapacity_; ++i)
		{
			buckets_[i] = 0;
		}

		entries_[0].data = new char[1];
		entries_[0].data[0] = '\0';
		entries_[0].length = 0;
		entries_[0].hash = 0;
	}

	NameTable(const NameTable&) = delete;
	NameTable& operator=(const NameTable&) = delete;

	~NameTable()
	{
		for (uint32 i = 0; i < entryCount_; ++i)
		{
			delete[] entries_[i].data;
		}

		delete[] entries_;
		delete[] buckets_;
	}

	bool Find(const char* value, uint32& outID) const
	{
		if (value == nullptr || value[0] == '\0')
		{
			outID = 0;
			return true;
		}

		const uint32 length = StringLength(value);
		const uint32 hash	= Hashing::FNV1a(value, length);

		uint32 index = hash % bucketCapacity_;

		while (buckets_[index] != 0)
		{
			const uint32 id = buckets_[index] - 1;

			if (const Entry& entry = entries_[id];
				entry.hash == hash && entry.length == length && Equal(entry.data, value, length)
			)
			{
				outID = id;
				return true;
			}

			++index;

			if (index >= bucketCapacity_)
			{
				index = 0;
			}
		}

		outID = 0;
		return false;
	}

	uint32 FindOrAdd(const char* value)
	{
		if (value == nullptr || value[0] == '\0')
		{
			return 0;
		}

		const uint32 length = StringLength(value);
		const uint32 hash	= Hashing::FNV1a(value, length);

		uint32 index = hash % bucketCapacity_;

		while (buckets_[index] != 0)
		{
			const uint32 id = buckets_[index] - 1;

			if (const Entry& entry = entries_[id];
				entry.hash == hash && entry.length == length && Equal(entry.data, value, length)
			)
			{
				return id;
			}

			++index;

			if (index >= bucketCapacity_)
			{
				index = 0;
			}
		}

		if ((entryCount_ + 1) * 2 >= bucketCapacity_)
		{
			GrowBuckets();

			index = FindEmptyBucket(hash);
		}

		if (entryCount_ >= entryCapacity_)
		{
			GrowEntries();
		}

		const uint32 id = entryCount_;

		entries_[id].data	= new char[length + 1];
		entries_[id].length = length;
		entries_[id].hash	= hash;

		Copy(entries_[id].data, value, length);

		buckets_[index] = id + 1;

		++entryCount_;

		return id;
	}

	[[nodiscard]] const char* GetString(const uint32 id) const
	{
		if (id >= entryCount_)
		{
			return "";
		}

		return entries_[id].data;
	}

	[[nodiscard]] uint32 GetLength(const uint32 id) const
	{
		if (id >= entryCount_)
		{
			return 0;
		}

		return entries_[id].length;
	}

	[[nodiscard]] uint32 Count() const
	{
		return entryCount_ - 1;
	}

	// Singleton
	static NameTable& Get()
	{
		static NameTable table;
		return table;
	}

	uint32 GetUniqueSuffixCounter(const char* base) const
	{
		const auto entry = uniqueSuffixDict_.FindEntry(base);
		return entry ? entry->value : 0;
	}

	void IncrementUniqueSuffixCounter(const char* base)
	{
		const uint32 current = GetUniqueSuffixCounter(base);
		uniqueSuffixDict_[base] = current + 1;
	}

private:
	struct Entry
	{
		char* data = nullptr;
		uint32 length = 0;
		uint32 hash	  = 0;
	};

	Entry* entries_ = nullptr;
	uint32 entryCount_	  = 0;
	uint32 entryCapacity_ = 0;

	uint32* buckets_		 = nullptr;
	uint32  bucketCapacity_ = 0;

	Dictionary<const char*, uint32> uniqueSuffixDict_;


	//==================
	// Private Helpers
	//==================

	static uint32 StringLength(const char* value)
	{
		if (!value)
		{
			return 0;
		}

		uint32 length = 0;

		while (value[length] != '\0')
		{
			++length;
		}

		return length;
	}

	static void Copy(char* destination, const char* source, const uint32 length)
	{
		for (uint32 i = 0; i < length; ++i)
		{
			destination[i] = source[i];
		}

		destination[length] = '\0';
	}

	static bool Equal(const char* a, const char* b, const uint32 length)
	{
		for (uint32 i = 0; i < length; ++i)
		{
			if (a[i] != b[i])
			{
				return false;
			}
		}

		return true;
	}

	void GrowEntries()
	{
		const uint32 newCapacity = entryCapacity_ * 2;

		auto* newEntries = new Entry[newCapacity];

		for (uint32 i = 0; i < entryCount_; ++i)
		{
			newEntries[i] = entries_[i];
		}

		delete[] entries_;

		entries_ = newEntries;
		entryCapacity_ = newCapacity;
	}

	[[nodiscard]] uint32 FindEmptyBucket(const uint32 hash) const
	{
		uint32 index = hash % bucketCapacity_;

		while (buckets_[index] != 0)
		{
			++index;

			if (index >= bucketCapacity_)
			{
				index = 0;
			}
		}

		return index;
	}

	void InsertBucket(const uint32 id) const
	{
		const uint32 index = FindEmptyBucket(entries_[id].hash);

		buckets_[index] = id + 1;
	}

	void GrowBuckets()
	{
		const uint32 newCapacity = bucketCapacity_ * 2;

		delete[] buckets_;

		bucketCapacity_ = newCapacity;

		buckets_ = new uint32[bucketCapacity_];

		for (uint32 i = 0; i < bucketCapacity_; ++i)
		{
			buckets_[i] = 0;
		}

		for (uint32 i = 1; i < entryCount_; ++i)
		{
			InsertBucket(i);
		}
	}
};