//===================================================
// String.h
// Author: Moca 9/14/2026
// Defines a String type to store a sequence
// of characters.
//===================================================
#pragma once

#include "../Math/Int.h"

#include <cstdio>
#include <cstring>

//! String type for storing a sequence of characters.
class String
{
public:
	//! Default String constructor
	String()
	{
		Allocate(1);
		data_[0] = '\0';
	}

	//! Char to String constructor
	String(const char* value)
	{
		if (!value)
		{
			Allocate(1);
			data_[0] = '\0';
			return;
		}

		length_ = StringLength(value);

		Allocate(length_ + 1);

		CopyMemory(data_, value, length_);

		data_[length_] = '\0';
	}

	//! Char with set length to String constructor
	String(const char* value, const uint32 length)
	{
		if (!value || length == 0)
		{
			Allocate(1);

			data_[0] = '\0';

			return;
		}

		length_ = length;

		Allocate(length_ + 1);

		CopyMemory(data_, value, length_);

		data_[length_] = '\0';
	}

	//! int8 to String constructor
	explicit String(const int8 value)
	{
		char buffer[8]{};

		const int32 length = snprintf(buffer, sizeof(buffer), "%hhd", value);

		if (length <= 0)
		{
			Allocate(1);
			data_[0] = '\0';
			return;
		}

		length_ = length;

		Allocate(length_ + 1);

		CopyMemory(data_, buffer, length_);

		data_[length_] = '\0';
	}

	//! int16 to String constructor
	explicit String(const int16 value)
	{
		char buffer[16]{};

		const int32 length = snprintf(buffer, sizeof(buffer), "%hd", value);

		if (length <= 0)
		{
			Allocate(1);
			data_[0] = '\0';
			return;
		}

		length_ = length;

		Allocate(length_ + 1);

		CopyMemory(data_, buffer, length_);

		data_[length_] = '\0';
	}

	//! int32 to String constructor
	explicit String(const int32 value)
	{
		char buffer[16]{};

		const int32 length = snprintf(buffer, sizeof(buffer), "%d", value);

		if (length <= 0)
		{
			Allocate(1);
			data_[0] = '\0';
			return;
		}

		length_ = length;

		Allocate(length_ + 1);

		CopyMemory(data_, buffer, length_);

		data_[length_] = '\0';
	}

	//! int64 to String constructor
	explicit String(const int64 value)
	{
		char buffer[32]{};

		const int32 length = snprintf(buffer, sizeof(buffer), "%lld", value);

		if (length <= 0)
		{
			Allocate(1);
			data_[0] = '\0';
			return;
		}

		length_ = length;

		Allocate(length_ + 1);

		CopyMemory(data_, buffer, length_);

		data_[length_] = '\0';
	}

	//! uint8 to String constructor
	explicit String(const uint8 value)
	{
		char buffer[8]{};

		const int32 length = snprintf(buffer, sizeof(buffer), "%hhu", value);

		if (length <= 0)
		{
			Allocate(1);
			data_[0] = '\0';
			return;
		}

		length_ = length;

		Allocate(length_ + 1);

		CopyMemory(data_, buffer, length_);

		data_[length_] = '\0';
	}

	//! uint16 to String constructor
	explicit String(const uint16 value)
	{
		char buffer[16]{};

		const int32 length = snprintf(buffer, sizeof(buffer), "%hu", value);

		if (length <= 0)
		{
			Allocate(1);
			data_[0] = '\0';
			return;
		}

		length_ = length;

		Allocate(length_ + 1);

		CopyMemory(data_, buffer, length_);

		data_[length_] = '\0';
	}

	//! uint32 to String constructor
	explicit String(const uint32 value)
	{
		char buffer[16]{};

		const int32 length = snprintf(buffer, sizeof(buffer), "%u", value);

		if (length <= 0)
		{
			Allocate(1);
			data_[0] = '\0';
			return;
		}

		length_ = length;

		Allocate(length_ + 1);

		CopyMemory(data_, buffer, length_);

		data_[length_] = '\0';
	}

	//! uint64 to String constructor
	explicit String(const uint64 value)
	{
		char buffer[32]{};

		const int32 length = snprintf(buffer, sizeof(buffer), "%llu", value);

		if (length <= 0)
		{
			Allocate(1);
			data_[0] = '\0';
			return;
		}

		length_ = length;

		Allocate(length_ + 1);

		CopyMemory(data_, buffer, length_);

		data_[length_] = '\0';
	}

	//! Float to String constructor
	explicit String(const float value)
	{
		char buffer[64]{};

		const int32 length = snprintf(buffer, sizeof(buffer), "%g", static_cast<double>(value));

		if (length <= 0)
		{
			Allocate(1);
			data_[0] = '\0';
			return;
		}

		length_ = static_cast<uint64>(length);

		Allocate(length_ + 1);

		CopyMemory(data_, buffer, length_);

		data_[length_] = '\0';
	}

	//! Double to String constructor
	explicit String(const double value)
	{
		char buffer[64]{};

		const int32 length = snprintf(buffer, sizeof(buffer), "%g", value);

		if (length <= 0)
		{
			Allocate(1);
			data_[0] = '\0';
			return;
		}

		length_ = static_cast<uint64>(length);

		Allocate(length_ + 1);

		CopyMemory(data_, buffer, length_);

		data_[length_] = '\0';
	}

	//! Copy constructor
	String(const String& other)
	{
		length_ = other.length_;

		Allocate(length_ + 1);

		CopyMemory(data_, other.data_, length_);

		data_[length_] = '\0';
	}

	//! Move constructor
	String(String&& other) noexcept
	{
		data_	  = other.data_;
		length_	  = other.length_;
		capacity_ = other.capacity_;

		other.data_		= nullptr;
		other.length_	= 0;
		other.capacity_ = 0;
	}

	//! String destructor
	~String()
	{
		delete[] data_;
	}


	//! Clears the data of this String.
	void Clear()
	{
		length_ = 0;

		if (data_)
		{
			data_[0] = '\0';
		}
	}

	//! Allocates a new buffer of a given size.
	//! New capacity must be larger than current capacity.
	void Reserve(const uint32 newCapacity)
	{
		if (newCapacity <= capacity_)
		{
			return;
		}

		if (newCapacity <= length_)
		{
			return;
		}

		char* newData = new char[newCapacity];

		if (data_ && length_ > 0)
		{
			CopyMemory(newData, data_, length_);
		}

		newData[length_] = '\0';

		delete[] data_;

		data_	  = newData;
		capacity_ = newCapacity;
	}

	//! Resizes this String to the given size.
	void Resize(const uint32 newLength, const char character = '\0')
	{
		EnsureCapacity(newLength + 1);

		if (newLength > length_)
		{
			for (uint32 i = length_; i < newLength; ++i)
			{
				data_[i] = character;
			}
		}

		length_ = newLength;
		data_[length_] = '\0';
	}

	//! Appends a given String to this String.
	void Append(const String& other)
	{
		Append(other.CStr(), other.Length());
	}

	//! Appends a given C string to this String.
	void Append(const char* value)
	{
		if (!value)
		{
			return;
		}

		Append(value, StringLength(value));
	}

	//! Appends a single character to this String.
	void Append(const char character)
	{
		EnsureCapacity(length_ + 2);

		data_[length_] = character;

		++length_;

		data_[length_] = '\0';
	}

	//! Returns whether or not this String starts with a given C string.
	bool StartsWith(const char* value) const
	{
		if (!value)
		{
			return false;
		}

		const uint32 valueLength = StringLength(value);

		if (valueLength > length_)
		{
			return false;
		}

		for (uint32 i = 0; i < valueLength; ++i)
		{
			if (data_[i] != value[i])
			{
				return false;
			}
		}

		return true;
	}

	//! Returns whether or not this String starts with another given String.
	[[nodiscard]] bool StartsWith(const String& value) const
	{
		return StartsWith(value.CStr());
	}

	//! Returns whether or not this String ends with a given C string.
	bool EndsWith(const char* value) const
	{
		if (!value)
		{
			return false;
		}

		const uint32 valueLength = StringLength(value);

		if (valueLength > length_)
		{
			return false;
		}

		const uint32 offset = length_ - valueLength;

		for (uint32 i = 0; i < valueLength; ++i)
		{
			if (data_[offset + i] != value[i])
			{
				return false;
			}
		}

		return true;
	}

	//! Returns whether or not this String ends with another given String.
	[[nodiscard]] bool EndsWith(const String& value) const
	{
		return EndsWith(value.CStr());
	}

	//! Returns whether or not this String contains a given C string.
	bool Contains(const char* value) const
	{
		if (!value)
		{
			return false;
		}

		const uint32 valueLength = StringLength(value);

		if (valueLength == 0)
		{
			return true;
		}

		if (valueLength > length_)
		{
			return false;
		}

		for (uint32 i = 0; i <= length_ - valueLength; ++i)
		{
			bool match = true;

			for (uint32 j = 0; j < valueLength; ++j)
			{
				if (data_[i + j] != value[j])
				{
					match = false;
					break;
				}
			}

			if (match)
			{
				return true;
			}
		}

		return false;
	}

	//! Returns whether or not this String contains another given String.
	[[nodiscard]] bool Contains(const String& value) const
	{
		return Contains(value.CStr());
	}

	//! Finds and returns the position of a given C string.
	//! Returns 0 if the given C string's length is 0,
	//! and returns -1 if the given C string is not found in this String.
	uint32 Find(const char* value) const
	{
		if (!value)
		{
			return -1;
		}

		const uint32 valueLength = StringLength(value);

		if (valueLength == 0)
		{
			return 0;
		}

		if (valueLength > length_)
		{
			return -1;
		}

		for (uint32 i = 0; i <= length_ - valueLength; ++i)
		{
			bool match = true;

			for (uint32 j = 0; j < valueLength; ++j)
			{
				if (data_[i + j] != value[j])
				{
					match = false;
					break;
				}
			}

			if (match)
			{
				return i;
			}
		}

		return -1;
	}

	//! Finds and returns the position of another given String.
	//! Returns 0 if the given String's length is 0,
	//! and returns -1 if the given String is not found in this String.
	[[nodiscard]] uint32 Find(const String& value) const
	{
		return Find(value.CStr());
	}

	//! Returns the substring from a given start position up to a given count of characters.
	//! Returns an empty String if invalid start position.
	[[nodiscard]] String Substr(const uint32 start, uint32 count) const
	{
		if (start >= length_)
		{
			return {};
		}

		uint32 available = length_ - start;

		if (count > available)
		{
			count = available;
		}

		return {data_ + start, count};
	}

	//! Converts String characters to all lowercase.
	[[nodiscard]] String ToLower() const
	{
		String result(*this);

		for (uint32 i = 0; i < result.length_; ++i)
		{
			if (result.data_[i] >= 'A' && result.data_[i] <= 'Z')
			{
				result.data_[i] = static_cast<char>(result.data_[i] - 'A' + 'a');
			}
		}

		return result;
	}

	//! Converts String characters to all uppercase.
	[[nodiscard]] String ToUpper() const
	{
		String result(*this);

		for (uint32 i = 0; i < result.length_; ++i)
		{
			if (result.data_[i] >= 'a' && result.data_[i] <= 'z')
			{
				result.data_[i] = static_cast<char>(result.data_[i] - 'a' + 'A');
			}
		}

		return result;
	}

	// Data fetching
	//! Returns this String's char data.
	[[nodiscard]] const char* CStr() const
	{
		return data_ ? data_ : "";
	}

	//! Returns a pointer to this String's data.
	char* Data()
	{
		return data_;
	}

	//! Returns a pointer to this String's data as a constant.
	[[nodiscard]] const char* Data() const
	{
		return data_;
	}

	//! Returns the length of this String.
	[[nodiscard]] constexpr uint32 Length() const
	{
		return length_;
	}

	//! Returns this capacity of this String.
	[[nodiscard]] constexpr uint32 Capacity() const
	{
		return capacity_;
	}

	//! Returns whether or not this String is empty.
	[[nodiscard]] constexpr bool IsEmpty() const
	{
		return length_ == 0;
	}


	//============
	// Operators
	//============

	//Equals
	//! Copies another String's data to this String.
	String& operator=(const String& other)
	{
		if (this == &other)
		{
			return *this;
		}

		EnsureCapacity(other.length_ + 1);

		length_ = other.length_;

		CopyMemory(data_, other.data_, length_);

		data_[length_] = '\0';

		return *this;
	}

	//! Moves another String's data to this String.
	String& operator=(String&& other) noexcept
	{
		if (this == &other)
		{
			return *this;
		}

		delete[] data_;

		data_	  = other.data_;
		length_	  = other.length_;
		capacity_ = other.capacity_;

		other.data_		= nullptr;
		other.length_	= 0;
		other.capacity_ = 0;

		return *this;
	}

	//! Sets this String's data to a given C string's data.
	String& operator=(const char* value)
	{
		if (!value)
		{
			Clear();
			return *this;
		}

		const uint64 valueLength = StringLength(value);

		EnsureCapacity(valueLength + 1);

		CopyMemory(data_, value, valueLength);

		length_		   = valueLength;
		data_[length_] = '\0';

		return *this;
	}

	// Addition
	//! Appends the data of another String to this String.
	String operator+(const String& other) const
	{
		String result(*this);

		result.Append(other);

		return result;
	}

	//! Appends the data of a given C string to this String.
	String operator+(const char* other) const
	{
		String result(*this);

		result.Append(other);

		return result;
	}

	//! Appends a single character to this String.
	String operator+(const char character) const
	{
		String result(*this);

		result.Append(character);

		return result;
	}

	//! Appends the data of another String to this String.
	String& operator+=(const String& other)
	{
		Append(other);
		return *this;
	}

	//! Appends the data of a given C string to this String.
	String& operator+=(const char* other)
	{
		Append(other);
		return *this;
	}

	//! Appends a single character to this String.
	String& operator+=(const char character)
	{
		Append(character);
		return *this;
	}

	//! Returns whether or not this String's data equals another given String's data.
	constexpr bool operator==(const String& right) const
	{
		if (length_ != right.length_)
		{
			return false;
		}

		return CompareMemory(data_, right.data_, length_);
	}

	//! Returns whether or not this String's data equals a given C string's data.
	constexpr bool operator==(const char* right) const
	{
		if (!right)
		{
			return false;
		}

		const uint32 rightLength = StringLength(right);

		if (length_ != rightLength)
		{
			return false;
		}

		return CompareMemory(data_, right, length_);
	}

	//! Returns whether or not this String's data does not equal another given String's data.
	constexpr bool operator!=(const String& right) const
	{
		return !(*this == right);
	}

	//! Returns whether or not this String's data does not equal a given C string's data.
	constexpr bool operator!=(const char* right) const
	{
		return !(*this == right);
	}

	//! Returns whether or not this String is less than another given String.
	//! Determine via Compare() which compares characters and lengths.
	bool operator<(const String& right) const
	{
		return Compare(right) < 0;
	}

	//! Returns whether or not this String is less than or equal to another given String.
	//! Determine via Compare() which compares characters and lengths.
	bool operator<=(const String& right) const
	{
		return Compare(right) <= 0;
	}

	//! Returns whether or not this String is greater than another given String.
	//! Determine via Compare() which compares characters and lengths.
	bool operator>(const String& right) const
	{
		return Compare(right) > 0;
	}

	//! Returns whether or not this String is greater than or equal to another given String.
	//! Determine via Compare() which compares characters and lengths.
	bool operator>=(const String& right) const
	{
		return Compare(right) >= 0;
	}

	//! Returns the character at the given index.
	constexpr char& operator[](const uint32 index)
	{
		return data_[index];
	}

	//! Returns the character at the given index as a constant.
	constexpr const char& operator[](const uint32 index) const
	{
		return data_[index];
	}

private:
	//! Stores a pointer to this String's first character
	char* data_ = nullptr;

	//! Stores the length of this String (number of characters)
	uint32 length_	 = 0;
	//! Stores the reserved capacity of this String
	uint32 capacity_ = 0;

	//! Allocates a given capacity that can store characters for this String.
	void Allocate(const uint32 capacity)
	{
		data_ = new char[capacity];
		capacity_ = capacity;
	}

	//! Ensures that this String's capacity supports a given required capacity by reserving new space if needed.
	void EnsureCapacity(const uint32 requiredCapacity)
	{
		if (requiredCapacity <= capacity_)
		{
			return;
		}

		uint32 newCapacity = capacity_ > 0 ? capacity_ : 1;

		while (newCapacity < requiredCapacity)
		{
			newCapacity *= 2;
		}

		Reserve(newCapacity);
	}

	//! Appends a series of characters to this String based on a given starting char value and its length.
	void Append(const char* value, const uint32 valueLength)
	{
		if (!value || valueLength == 0)
		{
			return;
		}

		if (valueLength > (MaxInt<uint32> - length_ - 1))
		{
			return;
		}

		EnsureCapacity(length_ + valueLength + 1);

		CopyMemory(data_ + length_, value, valueLength);

		length_ += valueLength;

		data_[length_] = '\0';
	}

	//! Compares the characters and length of a given String to this String.
	[[nodiscard]] int8 Compare(const String& other) const
	{
		const uint32 compareLength = length_ < other.length_ ? length_ : other.length_;

		for (uint32 i = 0; i < compareLength; ++i)
		{
			if (data_[i] < other.data_[i])
			{
				return -1;
			}

			if (data_[i] > other.data_[i])
			{
				return 1;
			}
		}

		if (length_ < other.length_)
		{
			return -1;
		}

		if (length_ > other.length_)
		{
			return 1;
		}

		return 0;
	}

	//! Returns the length of a given C string.
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

	//! Copies the source characters (based on source and then the count of characters) to the destination character pointer.
	static void CopyMemory(char* destination, const char* source, const uint32 count)
	{
		if (!destination || !source || count == 0)
		{
			return;
		}

		memmove(destination, source, count);
	}

	//! Returns whether or not the left and right buffers are identical for the first character up to the given count.
	static bool CompareMemory(const char* left, const char* right, const uint32 count)
	{
		for (uint32 i = 0; i < count; ++i)
		{
			if (left[i] != right[i])
			{
				return false;
			}
		}

		return true;
	}
};