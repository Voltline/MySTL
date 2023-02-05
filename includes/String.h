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
		using const_iterator = const unsigned char*;
	public:
		String();
		String(const char* _c_str);
		String(const char* _c_str, size_t _size);
		String(const char* _c_str, size_t _begin, size_t _size);
		String(size_t _size, char c);
		String(const String& _str);
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
		const unsigned char& operator[](size_t _index) const;
		unsigned char& at(size_t _index);

		bool operator==(const String& _Right);
		bool operator!=(const String& _Right);
		bool operator>(const String& _Right);
		bool operator<(const String & _Right);
		bool operator>=(const String& _Right);
		bool operator<=(const String& _Right);

		bool operator==(const char* _c_Right);
		bool operator!=(const char* _c_Right);
		bool operator>(const char* _c_Right);
		bool operator<(const char* _c_Right);
		bool operator>=(const char* _c_Right);
		bool operator<=(const char* _c_Right);

		size_t size() const noexcept;
		size_t capacity() const noexcept;
		bool empty() const noexcept;
		const unsigned char* data();
		const unsigned char* c_str();
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;

		void reserve(size_t new_capacity_size);
		void resize(size_t new_elem_size);
		void clear();
		void erase(const size_t _Where);
		void erase(const size_t _Off, const size_t _Count);
		void erase(iterator _begin, iterator _end);
		void erase(iterator _pos);

		void append(size_t _Count, char c);
		void append(const String& _str);
		void append(const String& _str, size_t _Begin = 0);
		void append(const String& _str, size_t _Begin, size_t _Count);
		void append(const char* _str);
		void append(const char* _str, size_t _Begin);
		void append(const char* _str, size_t _Begin, size_t _Count);
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

	bool operator==(const char* _Left, String _Right);
	bool operator!=(const char* _Left, String _Right);
	bool operator>(const char* _Left, String _Right);
	bool operator<(const char* _Left, String _Right);
	bool operator>=(const char* _Left, String _Right);
	bool operator<=(const char* _Left, String _Right);
}
