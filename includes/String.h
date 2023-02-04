#pragma once
#include <iostream>
#include <cstring>
#include "Vector.h"

namespace MySTL 
{
	class String
	{
	private:
		Vector<unsigned char> container;
		size_t _size{ 0 };
	public:
		using iterator = unsigned char*;
	public:
		String() = default;
		String(const char* _c_str);
		String(const char* _c_str, size_t _size);
		String(const char* _c_str, size_t _begin, size_t _size);
		String(size_t _size, char c);
		String(String& _str);
		String(String&& _mv_str) noexcept;
		String(std::initializer_list<char> l);
		~String();

		void operator=(const String& _Right);
		void operator=(const char* _str);
		void operator=(char c);

		String operator+(const String& _Right);
		String operator+(const char* _str);
		String operator+(char c);

		void operator+=(const String& _Right);
		void operator+=(const char* _str);
		void operator+=(char c);

		unsigned char& operator[](size_t _index);
		unsigned char& at(size_t _index);

		constexpr bool operator==(const String& _Right);
		constexpr bool operator!=(const String& _Right);
		constexpr bool operator>(const String& _Right);
		constexpr bool operator<(const String & _Right);
		constexpr bool operator>=(const String& _Right);
		constexpr bool operator<=(const String& _Right);

		constexpr bool operator==(const char* _c_Right);
		constexpr bool operator!=(const char* _c_Right);
		constexpr bool operator>(const char* _c_Right);
		constexpr bool operator<(const char* _c_Right);
		constexpr bool operator>=(const char* _c_Right);
		constexpr bool operator<=(const char* _c_Right);

		size_t size();
		size_t capacity();
		constexpr bool empty();
		const unsigned char* data();
		const unsigned char* c_str();
		iterator begin();
		iterator end();

		void reserve(size_t new_capacity_size);
		void resize(size_t new_elem_size);
		void clear();
		void erase(const size_t _Where);
		void erase(const size_t _Off, const size_t _Count);
		void erase(iterator _begin, iterator _end);
		void erase(iterator _pos);

		void append(size_t _Count, char c);
		void append(const String& _str);
		void append(const char* _str, size_t _Count = 0);
		void append(std::initializer_list<char> l);
		void push_back(char c);

		size_t find(char c, size_t _begin_pos = 0);
		size_t find(const char* _str, size_t _begin_pos = 0);
		size_t find(const String& _str, size_t _begin_pos = 0);

		constexpr void swap(const String& _Right);

		friend std::ostream& operator<<(std::ostream& output, String _str)
		{
			for (auto& i : _str) {
				output << i;
			}
			return output;
		}

		friend std::istream& operator>>(std::istream& input, String& _str)
		{
			_str.clear();
			unsigned char c = input.get();
			while (c != ' ' && c != '\n' && c != '\t') {
				_str.push_back(c);
				c = input.get();
			}
			return input;
		}
	};

	constexpr bool operator==(const char* _Left, String _Right);
	constexpr bool operator!=(const char* _Left, String _Right);
	constexpr bool operator>(const char* _Left, String _Right);
	constexpr bool operator<(const char* _Left, String _Right);
	constexpr bool operator>=(const char* _Left, String _Right);
	constexpr bool operator<=(const char* _Left, String _Right);

}


