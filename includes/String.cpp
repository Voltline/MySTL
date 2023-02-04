#include "String.h"

namespace MySTL
{
	String::String(const char* _c_str)
	{
		size_t length{ strlen(_c_str) };
		this->_size = length;
		this->container = 
			Vector<unsigned char>{ 
				const_cast<unsigned char *>((unsigned char*)_c_str), 
				const_cast<unsigned char*>((unsigned char*)(_c_str + (length + 1))) 
			};
		this->container[_size] = '\0';
	}

	String::String(const char* _c_str, size_t _size)
	{
		size_t length{ _size };
		if (_size > strlen(_c_str)) {
			length = strlen(_c_str);
		}

		this->_size = length;
		this->container =
			Vector<unsigned char>{
				const_cast<unsigned char*>((unsigned char*)_c_str),
				const_cast<unsigned char*>((unsigned char*)(_c_str + (length + 1)))
		};
		this->container[_size] = '\0';
	}

	String::String(const char* _c_str, size_t _begin, size_t _size)
	{
		size_t length{ _size };
		if (_size > strlen(_c_str + _begin)) {
			length = strlen(_c_str + _begin);
		}

		this->_size = length;
		this->container =
			Vector<unsigned char>{
				const_cast<unsigned char*>((unsigned char*)_c_str),
				const_cast<unsigned char*>((unsigned char*)(_c_str + (length + 1)))
		};
		this->container[_size] = '\0';
	}

	String::String(size_t _size, char c)
	{
		this->container = Vector<unsigned char>(_size, c);
		this->_size = _size;
	}

	String::String(String& _str)
	{
		this->container = Vector<unsigned char>(_str.container);
		this->_size = _str._size;
	}

	String::String(String&& _mv_str) noexcept
	{
		this->container = std::move(_mv_str.container);
		this->_size = _mv_str._size;
		_mv_str.container = Vector<unsigned char>{};
		_mv_str.~String();
	}

	String::String(std::initializer_list<char> l)
	{
		this->container = Vector<unsigned char>(l.size() + 128);
		this->_size = l.size();
		for (auto it = l.begin(); it != l.end(); it++) {
			this->container.push_back(static_cast<unsigned char>(*it));
		}
		this->container.push_back('\0');
	}

	String::~String()
	{
		this->_size = 0;
		this->container.~Vector();
	}

	void String::operator=(const String& _Right)
	{
		this->container.~Vector();
		this->container = _Right.container;

	}
	void String::operator=(const char* _str)
	{
		this->container.~Vector();
		size_t length{ strlen(_str) };
		this->container = Vector<unsigned char>(length + 128);
		this->_size = 0;
		for (size_t i = 0; i < length; i++) {
			this->container.push_back(_str[i]);
			this->_size++;
		}
	}

	constexpr bool String::empty()
	{
		return (this->_size == 0);
	}

	size_t String::size()
	{
		return this->_size;
	}

	size_t String::capacity()
	{
		return this->container.capacity();
	}

	const unsigned char* String::data()
	{
		return this->container.data();
	}

	const unsigned char* String::c_str()
	{
		return this->container.data();
	}

	String::iterator String::begin()
	{
		return this->container.begin();
	}

	String::iterator String::end()
	{
		return this->container.end();
	}

	void String::reserve(size_t new_capacity_size)
	{
		this->container.reserve(new_capacity_size);
	}

	void String::resize(size_t new_elem_size)
	{
		this->container.resize(new_elem_size);
		this->_size = new_elem_size;
	}

	void String::clear()
	{
		this->_size = 0;
		this->container.clear();
	}

	String String::operator+(char c)
	{
		String temp{ *this };
		temp.push_back(c);
		return temp;
	}

	unsigned char& String::operator[](size_t _index)
	{
		return this->container[_index];
	}

	unsigned char& String::at(size_t _index)
	{
		if (_index <= this->_size) {
			return this->container[_index];
		}
		else {
			throw std::out_of_range("Index Out of Range");
		}
	}

	void String::push_back(char c)
	{
		if (this->_size == 0) {
			this->container.push_back(c);
		}
		else {
			this->container[_size] = c;
		}
		this->container.push_back('\0');
		this->_size++;
	}
}
