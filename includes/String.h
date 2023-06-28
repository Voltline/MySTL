#pragma once
#include <iostream>
#include <cstring>
#include "vector.h"

namespace MySTL 
{
	class string
	{
	private:
		vector<unsigned char> container;
		size_t _size{ 0 };
	public:
		using iterator = unsigned char*;
		using const_iterator = const unsigned char*;
	public:
		string();
		string(const char* _c_str);
		string(const char* _c_str, size_t _size);
		string(const char* _c_str, size_t _begin, size_t _size);
		string(size_t _size, char c);
		string(const string& _str);
		string(string&& _mv_str) noexcept;
		string(std::initializer_list<char> l);
		~string();

		string& operator=(const string& _Right);
		string& operator=(string&& _Right) noexcept;
		string& operator=(const char* _str);
		string& operator=(char c);

		string operator+(const string& _Right);
		string operator+(const char* _str);
		string operator+(char c);

		void operator+=(const string& _Right);
		void operator+=(const char* _str);
		void operator+=(char c);

		unsigned char& operator[](size_t _index);
		const unsigned char& operator[](size_t _index) const;
		unsigned char& at(size_t _index);

		bool operator==(const string& _Right);
		bool operator!=(const string& _Right);
		bool operator>(const string& _Right);
		bool operator<(const string & _Right);
		bool operator>=(const string& _Right);
		bool operator<=(const string& _Right);

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
		void append(const string& _str);
		void append(const string& _str, size_t _Begin = 0);
		void append(const string& _str, size_t _Begin, size_t _Count);
		void append(const char* _str);
		void append(const char* _str, size_t _Begin);
		void append(const char* _str, size_t _Begin, size_t _Count);
		void append(std::initializer_list<char> l);
		void push_back(char c);

		size_t find(char c, size_t _begin_pos = 0);
		size_t find(const char* _str, size_t _begin_pos = 0);
		size_t find(const string& _str, size_t _begin_pos = 0);

		void swap(string& _Right);

		friend std::ostream& operator<<(std::ostream& output, string _str)
		{
			for (auto& i : _str) {
				output << i;
			}
			return output;
		}

		friend std::istream& operator>>(std::istream& input, string& _str)
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

	bool operator==(const char* _Left, string _Right);
	bool operator!=(const char* _Left, string _Right);
	bool operator>(const char* _Left, string _Right);
	bool operator<(const char* _Left, string _Right);
	bool operator>=(const char* _Left, string _Right);
	bool operator<=(const char* _Left, string _Right);

	std::istream& getline(std::istream& input, string& _Target, const char _End = '\n');
}
