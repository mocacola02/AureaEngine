#pragma once

#include "../Utility/Hash.h"


template<typename Key, typename Value, typename Hasher = Hash<Key>>
class Dictionary
{
public:
	struct Entry
	{
		Key key;
		Value value;

		Entry* next = nullptr;

		Entry(const Key& key, const Value& value) : key(key), value(value) {}
		Entry(const Key& key, Value&& value) : key(key), value(static_cast<Value&&>(value)) {}
		Entry(Key&& key, const Value& value) : key(static_cast<Key&&>(key)), value(value)	{}
		Entry(Key&& key, Value&& value)		 : key(static_cast<Key&&>(key)), value(static_cast<Value&&>(value)) {}
	};

	//! Default constructor
	Dictionary()
	{
		AllocateBuckets(defaultBucketCount_);
	}

	//! Constructor with a given capacity
	explicit Dictionary(const uint32 capacity)
	{
		ReserveInitial(capacity);
	}

	//! Copy constructor
	Dictionary(const Dictionary& other)
	{
		AllocateBuckets(other.bucketCount_);
		CopyFrom(other);
	}

	//! Move constructor
	Dictionary(Dictionary&& other) noexcept
	{
		MoveFrom(static_cast<Dictionary&&>(other));
	}

	//! Destructor
	~Dictionary()
	{
		Destroy();
	}


	//==========
	// Helpers
	//==========

	uint32 Count() const
	{
		return count_;
	}

	uint32 Capacity() const
	{
		return bucketCount_;
	}

	bool IsEmpty() const
	{
		return count_ == 0;
	}

	double LoadFactor() const
	{
		if (bucketCount_ == 0)
		{
			return 0.0;
		}

		return static_cast<double>(count_) / static_cast<double>(bucketCount_);
	}

	void Set(const Key& key, const Value& value)
	{
		Entry* existing = FindEntry(key);

		if (existing)
		{
			existing->value = value;
			return;
		}

		EnsureInsertCapacity();

		InsertNew(key, value);
	}

	void Set(Key&& key, Value&& value)
	{
		Entry* existing = FindEntry(key);

		if (existing)
		{
			existing->value = static_cast<Value&&>(value);
			return;
		}

		EnsureInsertCapacity();

		InsertNew(static_cast<Key&&>(key), static_cast<Value&&>(value));
	}

	void Set(const Key& key, Value&& value)
	{
		Entry* existing = FindEntry(key);

		if (existing)
		{
			existing->value = static_cast<Value&&>(value);
			return;
		}

		EnsureInsertCapacity();

		InsertNew(key, static_cast<Value&&>(value));
	}

	void Set(Key&& key, const Value& value)
	{
		Entry* existing = FindEntry(key);

		if (existing)
		{
			existing->value = value;
			return;
		}

		EnsureInsertCapacity();

		InsertNew(static_cast<Key&&>(key), value);
	}

	bool Add(const Key& key, const Value& value)
	{
		if (Contains(key))
		{
			return false;
		}

		EnsureInsertCapacity();

		InsertNew(key, value);

		return true;
	}

	bool Add(const Key& key, Value&& value)
	{
		if (Contains(key))
		{
			return false;
		}

		EnsureInsertCapacity();

		InsertNew(key, static_cast<Value&&>(value));

		return true;
	}

	bool Add(Key&& key, Value&& value)
	{
		if (Contains(key))
		{
			return false;
		}

		EnsureInsertCapacity();

		InsertNew(static_cast<Key&&>(key), static_cast<Value&&>(value));

		return true;
	}

	Value* Find(const Key& key)
	{
		Entry* entry = FindEntry(key);

		if (!entry)
		{
			return nullptr;
		}

		return &entry -> value;
	}

	const Value* Find(const Key& key) const
	{
		const Entry* entry = FindEntry(key);

		if (!entry)
		{
			return nullptr;
		}

		return &entry->value;
	}

	Value& Get(const Key& key)
	{
		Entry* entry = FindEntry(key);

		if (!entry)
		{
			FailMissingKey();
		}

		return entry->value;
	}

	const Value& Get(const Key& key) const
	{
		const Entry* entry = FindEntry(key);

		if (!entry)
		{
			FailMissingKey();
		}

		return entry->value;
	}

	bool TryGet(const Key& key, Value& value) const
	{
		const Entry* entry = FindEntry(key);

		if (!entry)
		{
			return false;
		}

		value = entry->value;

		return true;
	}

	bool Contains(const Key& key) const
	{
		return FindEntry(key) != nullptr;
	}

	bool Remove(const Key& key)
	{
		if (!buckets_ || bucketCount_ == 0)
		{
			return false;
		}

		const uint32 bucketIndex = GetBucketIndex(key, bucketCount_);

		Entry* entry = buckets_[bucketIndex];
		Entry* previous = nullptr;

		while (entry)
		{
			if (entry->key == key)
			{
				if (previous)
				{
					previous->next = entry->next;
				}
				else
				{
					buckets_[bucketIndex] = entry->next;
				}

				delete entry;

				--count_;

				return true;
			}

			previous = entry;
			entry = entry->next;
		}

		return false;
	}

	void Clear()
	{
		if (!buckets_)
		{
			count_ = 0;
			return;
		}

		for (uint32 i = 0; i < bucketCount_; ++i)
		{
			Entry* entry = buckets_[i];

			while (entry)
			{
				Entry* next = entry->next;

				delete entry;

				entry = next;
			}

			buckets_[i] = nullptr;
		}

		count_ = 0;
	}

	void Reserve(const uint32 capacity)
	{
		if (capacity == 0)
		{
			return;
		}

		const uint32 requiredBucketCount = CalculateBucketCount(capacity);

		if (requiredBucketCount <= bucketCount_)
		{
			return;
		}

		Rehash(requiredBucketCount);
	}

	template<typename Function>
	void ForEach(Function&& function)
	{
		for (uint32 i = 0; i < bucketCount_; ++i)
		{
			Entry* entry = buckets_[i];

			while (entry)
			{
				function(entry->key, entry->value);

				entry = entry->next;
			}
		}
	}

	template<typename Function>
	void ForEach(Function&& function) const
	{
		for (uint32 i = 0; i < bucketCount_; ++i)
		{
			const Entry* entry = buckets_[i];

			while (entry)
			{
				function(entry->key, entry->value);

				entry = entry->next;
			}
		}
	}


	//============
	// Operators
	//============

	//! Copies another given Dictionary's data to this Dictionary.
	Dictionary& operator=(const Dictionary& other)
	{
		if (this == other)
		{
			return *this;
		}

		Dictionary copy(other);

		Swap(copy);

		return *this;
	}

	//! Moves another given Dictionary's data to this Dictionary.
	Dictionary& operator=(Dictionary&& other) noexcept
	{
		if (this == other)
		{
			return *this;
		}

		Destroy();

		MoveFrom(static_cast<Dictionary&&>(other));

		return *this;
	}

	Value& operator[](const Key& key)
	{
		Entry* entry = FindEntry(key);

		if (entry)
		{
			return entry->value;
		}

		EnsureInsertCapacity();

		Entry* newEntry = InsertNew(key, Value{});

		return newEntry->value;
	}

	const Value& operator[](const Key& key) const
	{
		return Get(key);
	}


private:
	Entry** buckets_ = nullptr;

	uint32 bucketCount_ = 0;
	uint32 count_		= 0;

	static constexpr uint32 minimumBucketCount_ = 8;
	static constexpr uint32 defaultBucketCount_ = 16;

	static constexpr double maxLoadFactor_ = 0.75;


	Entry* InsertNew(const Key& key, const Value& value)
	{
		const uint32 bucketIndex = GetBucketIndex(key, bucketCount_);

		Entry* entry = new Entry(key, value);

		entry->next = buckets_[bucketIndex];

		buckets_[bucketIndex] = entry;

		++count_;

		return entry;
	}

	Entry* InsertNew(Key&& key, Value&& value)
	{
		const uint32 bucketIndex = GetBucketIndex(key, bucketCount_);

		Entry* entry = new Entry(static_cast<Key&&>(key), static_cast<Value&&>(value));

		entry->next = buckets_[bucketIndex];

		buckets_[bucketIndex] = entry;

		++count_;

		return entry;
	}

	Entry* InsertNew(const Key& key, Value&& value)
	{
		const uint32 bucketIndex = GetBucketIndex(key, bucketCount_);

		Entry* entry = new Entry(key, static_cast<Value&&>(value));

		entry->next = buckets_[bucketIndex];

		buckets_[bucketIndex] = entry;

		++count_;

		return entry;
	}

	Entry* InsertNew(Key&& key, const Value& value)
	{
		const uint32 bucketIndex = GetBucketIndex(key, bucketCount_);

		Entry* entry = new Entry(static_cast<Key&&>(key), value);

		entry->next = buckets_[bucketIndex];

		buckets_[bucketIndex] = entry;

		++count_;

		return entry;
	}

	Entry* FindEntry(const Key& key)
	{
		if (!buckets_ || bucketCount_ == 0)
		{
			return nullptr;
		}

		const uint32 bucketIndex = GetBucketIndex(key, bucketCount_);

		Entry* entry = buckets_[bucketIndex];

		while (entry)
		{
			if (entry->key == key)
			{
				return entry;
			}

			entry = entry->next;
		}

		return nullptr;
	}

	const Entry* FindEntry(const Key& key) const
	{
		if (!buckets_ || bucketCount_ == 0)
		{
			return nullptr;
		}

		const uint32 bucketIndex = GetBucketIndex(key, bucketCount_);

		const Entry* entry = buckets_[bucketIndex];

		while (entry)
		{
			if (entry->key == key)
			{
				return entry;
			}

			entry = entry->next;
		}

		return nullptr;
	}

	static uint32 GetBucketIndex(const Key& key, const uint32 bucketCount)
	{
		return Hasher::Get(key) & (bucketCount - 1);
	}

	void EnsureInsertCapacity()
	{
		if (!buckets_ || bucketCount_ == 0)
		{
			AllocateBuckets(defaultBucketCount_);

			return;
		}

		const uint32 maximumEntries = static_cast<uint32>(static_cast<double>(bucketCount_) * maxLoadFactor_);

		if (count_ + 1 <= maximumEntries)
		{
			return;
		}

		Rehash(bucketCount_ * 2);
	}

	void Rehash(uint32 newBucketCount)
	{
		newBucketCount = NextPowerOfTwo(newBucketCount);

		if (newBucketCount < minimumBucketCount_)
		{
			newBucketCount = minimumBucketCount_;
		}

		if (newBucketCount == bucketCount_)
		{
			return;
		}

		Entry** newBuckets = new Entry*[newBucketCount];

		for (uint32 i = 0; i < newBucketCount; ++i)
		{
			newBuckets[i] = nullptr;
		}

		for (uint32 i = 0; i < bucketCount_; ++i)
		{
			Entry* entry = buckets_[i];

			while (entry)
			{
				Entry* next = entry->next;

				const uint32 bucketIndex = GetBucketIndex(entry->key, newBucketCount);

				entry->next = newBuckets[bucketIndex];

				newBuckets[bucketIndex] = entry;

				entry = next;
			}
		}

		delete[] buckets_;

		buckets_ = newBuckets;

		bucketCount_ = newBucketCount;
	}

	void AllocateBuckets(uint32 bucketCount)
	{
		bucketCount = NextPowerOfTwo(bucketCount);

		if (bucketCount < minimumBucketCount_)
		{
			bucketCount = minimumBucketCount_;
		}

		buckets_ = new Entry*[bucketCount];

		bucketCount_ = bucketCount;

		count_ = 0;

		for (uint32 i = 0; i < bucketCount_; ++i)
		{
			buckets_[i] = nullptr;
		}
	}

	void ReserveInitial(const uint32 capacity)
	{
		if (capacity == 0)
		{
			AllocateBuckets(defaultBucketCount_);
			return;
		}

		AllocateBuckets(CalculateBucketCount(capacity));
	}

	static uint32 CalculateBucketCount(const uint32 capacity)
	{
		uint32 bucketCount = static_cast<uint32>(static_cast<double>(capacity) / maxLoadFactor_) + 1;

		if (bucketCount < minimumBucketCount_)
		{
			bucketCount = minimumBucketCount_;
		}

		return NextPowerOfTwo(bucketCount);
	}

	static uint32 NextPowerOfTwo(uint32 value)
	{
		if (value <= 1)
		{
			return 1;
		}

		--value;

		value |= value >> 1U;
		value |= value >> 2U;
		value |= value >> 4U;
		value |= value >> 8U;
		value |= value >> 16U;

		return value + 1;
	}

	void CopyFrom(const Dictionary& other)
	{
		for (uint32 i = 0; i < other.bucketCount_; ++i)
		{
			const Entry* entry = other.buckets_[i];

			while (entry)
			{
				InsertNew(entry->key, entry->value);

				entry = entry->next;
			}
		}
	}

	void MoveFrom(Dictionary&& other)
	{
		buckets_ = other.buckets_;

		bucketCount_ = other.bucketCount_;

		count_ = other.count_;

		other.buckets_ = nullptr;

		other.bucketCount_ = 0;

		other.count_ = 0;
	}

	void Swap(Dictionary& other)
	{
		Entry** buckets = buckets_;
		buckets_ = other.buckets_;
		other.buckets_ = buckets;

		uint32 bucketCount = bucketCount_;
		bucketCount_ = other.bucketCount_;
		other.bucketCount_ = bucketCount;

		uint32 count = count_;
		count_ = other.count_;
		other.count_ = count;
	}

	void Destroy()
	{
		Clear();

		delete[] buckets_;

		buckets_ = nullptr;

		bucketCount_ = 0;

		count_ = 0;
	}
};