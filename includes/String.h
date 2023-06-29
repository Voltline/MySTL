#pragma once
#include <iostream>
#include <cstring>
#include "vector.h"

namespace MySTL 
{
	template <typename T>
	class basic_string
	{
	private:
		vector<T> container;
		size_t _size;
	public:
		using iterator = T*;
		using const_iterator = const T*;
	public:
		basic_string();
		basic_string(const char* _c_str);
		basic_string(const char* _c_str, size_t _size);
		basic_string(const char* _c_str, size_t _begin, size_t _size);
		basic_string(size_t _size, char c);
		basic_string(const basic_string<T>& _str);
		basic_string(basic_string<T>&& _mv_str) noexcept;
		basic_string(std::initializer_list<T> l);
		~basic_string();

		basic_string& operator=(const basic_string<T>& _Right);
		basic_string& operator=(basic_string<T>&& _Right) noexcept;
		basic_string& operator=(const char* _str);
		basic_string& operator=(char c);

		basic_string operator+(const basic_string<T>& _Right);
		basic_string operator+(const char* _str);
		basic_string operator+(char c);

		basic_string& operator+=(const basic_string<T>& _Right);
		basic_string& operator+=(const char* _str);
		basic_string& operator+=(char c);

		T& operator[](size_t _index);
		const T& operator[](size_t _index) const;
		T& at(size_t _index);

		bool operator==(const basic_string<T>& _Right);
		bool operator!=(const basic_string<T>& _Right);
		bool operator>(const basic_string<T>& _Right);
		bool operator<(const basic_string<T>& _Right);
		bool operator>=(const basic_string<T>& _Right);
		bool operator<=(const basic_string<T>& _Right);

		bool operator==(const char* _c_Right);
		bool operator!=(const char* _c_Right);
		bool operator>(const char* _c_Right);
		bool operator<(const char* _c_Right);
		bool operator>=(const char* _c_Right);
		bool operator<=(const char* _c_Right);

		size_t size() const noexcept;
		size_t capacity() const noexcept;
		bool empty() const noexcept;
		const T* data();
		const T* c_str();
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
		void append(const basic_string<T>& _str);
		void append(const basic_string<T>& _str, size_t _Begin = 0);
		void append(const basic_string<T>& _str, size_t _Begin, size_t _Count);
		void append(const char* _str);
		void append(const char* _str, size_t _Begin);
		void append(const char* _str, size_t _Begin, size_t _Count);
		void append(std::initializer_list<char> l);
		void push_back(char c);

		size_t find(char c, size_t _begin_pos = 0);
		size_t find(const char* _str, size_t _begin_pos = 0);
		size_t find(const basic_string<T>& _str, size_t _begin_pos = 0);

		void swap(basic_string<T>& _Right);

		friend std::ostream& operator<<(std::ostream& output, const basic_string<T>& _str)
		{
			for (auto& i : _str) {
				output << i;
			}
			return output;
		}

		friend std::istream& operator>>(std::istream& input, basic_string<T>& _str)
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

	template<typename T>
	basic_string<T>::basic_string()
	{
		this->container = vector<unsigned char>{};
	}

	template<typename T>
	basic_string<T>::basic_string(const char* _c_str)
	{
		size_t length{ strlen(_c_str) };
		this->_size = length;
		this->container = vector<T>();
		for (size_t i = 0; i < length; i++) {
			this->container.push_back(*(_c_str + i));
		}
		this->container.push_back('\0');
	}

	template<typename T>
	basic_string<T>::basic_string(const char* _c_str, size_t _size)
	{
		size_t length{ _size };
		if (_size > strlen(_c_str)) {
			length = strlen(_c_str);
		}

		this->_size = length;
		this->container = vector<T>();
		for (size_t i = 0; i < length; i++) {
			this->container.push_back(*(_c_str + i));
		}
		this->container.push_back('\0');
	}

	template<typename T>
	basic_string<T>::basic_string(const char* _c_str, size_t _begin, size_t _size)
	{
		size_t c_str_len{ strlen(_c_str) };
		this->container = vector<T>();
		if (_begin > c_str_len) {
			this->_size = 0;
		}
		else {
			size_t length{ _size };
			if (_size > strlen(_c_str + _begin)) {
				length = strlen(_c_str + _begin);
			}

			this->_size = length;
			for (size_t i = _begin; i < length; i++) {
				this->container.push_back(*(_c_str + i));
			}
			this->container.push_back('\0');
		}
	}

	template<typename T>
	basic_string<T>::basic_string(size_t _size, char c)
	{
		this->container = vector<T>(_size, c);
		this->_size = _size;
	}

	template<typename T>
	basic_string<T>::basic_string(const basic_string<T>& _str)
	{
		this->container = vector<T>(_str.container);
		this->_size = _str._size;
	}

	template<typename T>
	basic_string<T>::basic_string(basic_string<T>&& _mv_str) noexcept
	{
		this->container = std::move(_mv_str.container);
		this->_size = _mv_str._size;
		_mv_str.container = vector<T>{};
	}

	template<typename T>
	basic_string<T>::basic_string(std::initializer_list<T> l)
	{
		this->container = vector<T>(l.size() + 128);
		this->_size = l.size();
		for (auto it = l.begin(); it != l.end(); it++) {
			this->container.push_back(static_cast<T>(*it));
		}
		this->container.push_back('\0');
	}

	template<typename T>
	basic_string<T>::~basic_string()
	{
		this->_size = 0;
		this->container.~vector();
	}

	template<typename T>
	basic_string<T>& basic_string<T>::operator=(const basic_string<T>& _Right)
	{
		this->container.~vector();
		this->container = _Right.container;
		this->_size = _Right._size;
		return *this;
	}

	template<typename T>
	basic_string<T>& basic_string<T>::operator=(basic_string<T>&& _Right) noexcept
	{
		this->container.~vector();
		this->container = std::move(_Right.container);
		this->_size = _Right._size;
		return *this;
	}

	template<typename T>
	basic_string<T>& basic_string<T>::operator=(const char* _str)
	{
		this->container.~vector();
		size_t length{ strlen(_str) };
		this->container = vector<T>(length + 128);
		this->_size = 0;
		for (size_t i = 0; i < length; i++) {
			this->container.push_back(_str[i]);
			this->_size++;
		}
		return *this;
	}

	template<typename T>
	basic_string<T>& basic_string<T>::operator=(char c)
	{
		this->clear();
		this->push_back(c);
		return *this;
	}

	template<typename T>
	basic_string<T> basic_string<T>::operator+(const basic_string<T>& _Right)
	{
		basic_string<T> temp{ *this };
		for (auto& i : _Right) {
			temp.push_back(i);
		}
		return temp;
	}

	template<typename T>
	basic_string<T> basic_string<T>::operator+(const char* _str)
	{
		basic_string<T> temp{ *this };
		size_t length{ strlen(_str) };
		for (size_t i = 0; i < length; i++) {
			temp.push_back(_str[i]);
		}
		return temp;
	}

	template<typename T>
	basic_string<T> basic_string<T>::operator+(char c)
	{
		basic_string<T> temp{ *this };
		temp.push_back(c);
		return temp;
	}

	template<typename T>
	basic_string<T>& basic_string<T>::operator+=(const basic_string<T>& _Right)
	{
		for (auto& i : _Right) {
			this->push_back(i);
		}
		return *this;
	}

	template<typename T>
	basic_string<T>& basic_string<T>::operator+=(const char* _str)
	{
		size_t length{ strlen(_str) };
		for (size_t i = 0; i < length; i++) {
			this->push_back(_str[i]);
		}
		return *this;
	}

	template<typename T>
	basic_string<T>& basic_string<T>::operator+=(char c)
	{
		this->push_back(c);
		return *this;
	}

	template<typename T>
	T& basic_string<T>::operator[](size_t _index)
	{
		return this->container[_index];
	}

	template<typename T>
	const T& basic_string<T>::operator[](size_t _index) const
	{
		return this->container[_index];
	}

	template<typename T>
	T& basic_string<T>::at(size_t _index)
	{
		if (_index <= this->_size) {
			return this->container[_index];
		}
		else {
			throw std::out_of_range("Index Out of Range");
		}
	}

	template<typename T>
	bool basic_string<T>::operator==(const basic_string<T>& _Right)
	{
		if (this->_size != _Right._size) {
			return false;
		}
		else {
			for (size_t i = 0; i < this->_size; i++) {
				if (this->container[i] != _Right[i]) return false;
			}
			return true;
		}
	}

	template<typename T>
	bool basic_string<T>::operator!=(const basic_string<T>& _Right)
	{
		return !(*this == _Right);
	}

	template<typename T>
	bool basic_string<T>::operator>(const basic_string<T>& _Right)
	{
		size_t min_size{ this->_size < _Right.size() ? this->_size : _Right.size() };
		for (size_t i = 0; i < min_size; i++) {
			if (this->container[i] > _Right[i]) return true;
			else if (this->container[i] < _Right[i]) {
				return false;
			}
		}
		return this->_size > _Right.size();
	}

	template<typename T>
	bool basic_string<T>::operator<(const basic_string<T>& _Right)
	{
		return (*this <= _Right) && (*this != _Right);
	}

	template<typename T>
	bool basic_string<T>::operator>=(const basic_string<T>& _Right)
	{
		return (*this > _Right) || (*this == _Right);
	}

	template<typename T>
	bool basic_string<T>::operator<=(const basic_string<T>& _Right)
	{
		return !(*this > _Right);
	}

	template<typename T>
	bool basic_string<T>::operator==(const char* _c_Right)
	{
		if (strlen(_c_Right) != this->_size) return false;
		else {
			for (size_t i = 0; i < this->_size; i++) {
				if (this->container[i] != _c_Right[i])
					return false;
			}
			return true;
		}
	}

	template<typename T>
	bool basic_string<T>::operator!=(const char* _c_Right)
	{
		return !(*this == _c_Right);
	}

	template<typename T>
	bool basic_string<T>::operator>(const char* _c_Right)
	{
		size_t length{ strlen(_c_Right) };
		size_t min_size{ this->_size < length ? this->_size : length };
		for (size_t i = 0; i < min_size; i++) {
			if (this->container[i] > _c_Right[i]) return true;
			else if (this->container[i] < _c_Right[i]) {
				return false;
			}
		}
		return this->_size > length;
	}

	template<typename T>
	bool basic_string<T>::operator<(const char* _c_Right)
	{
		return (*this <= _c_Right) && (*this != _c_Right);
	}

	template<typename T>
	bool basic_string<T>::operator>=(const char* _c_Right)
	{
		return (*this > _c_Right) || (*this == _c_Right);
	}

	template<typename T>
	bool basic_string<T>::operator<=(const char* _c_Right)
	{
		return !(*this > _c_Right);
	}

	template<typename T>
	size_t basic_string<T>::size() const noexcept
	{
		return this->_size;
	}

	template<typename T>
	size_t basic_string<T>::capacity() const noexcept
	{
		return this->container.capacity();
	}

	template<typename T>
	bool basic_string<T>::empty() const noexcept
	{
		if (this->_size != 0) return false;
		else return true;
	}

	template<typename T>
	const T* basic_string<T>::data()
	{
		return this->container.data();
	}

	template<typename T>
	const T* basic_string<T>::c_str()
	{
		return this->container.data();
	}

	template<typename T>
	basic_string<T>::iterator basic_string<T>::begin()
	{
		return this->container.begin();
	}

	template<typename T>
	basic_string<T>::iterator basic_string<T>::end()
	{
		return this->container.begin() + this->_size;
	}

	template<typename T>
	basic_string<T>::const_iterator basic_string<T>::begin() const
	{
		return this->container.begin();
	}

	template<typename T>
	basic_string<T>::const_iterator basic_string<T>::end() const
	{
		return this->container.begin() + this->_size;
	}

	template<typename T>
	void basic_string<T>::reserve(size_t new_capacity_size)
	{
		this->container.reserve(new_capacity_size);
	}

	template<typename T>
	void basic_string<T>::resize(size_t new_elem_size)
	{
		this->container.resize(new_elem_size);
		this->_size = new_elem_size;
	}

	template<typename T>
	void basic_string<T>::clear()
	{
		this->_size = 0;
		this->container.clear();
	}

	template<typename T>
	void basic_string<T>::erase(const size_t _Where)
	{
		if (_Where <= this->_size) {
			this->_size = _Where;
			this->container.erase(this->container.begin() + _Where, this->container.end());
			this->container.push_back('\0');
		}
	}

	template<typename T>
	void basic_string<T>::erase(const size_t _Off, const size_t _Count)
	{
		if (_Off <= this->_size) {
			if (this->_size - _Off > _Count) {
				this->_size -= _Count;
				this->container.erase(this->container.begin() + _Off, this->container.begin() + _Off + _Count);
				this->container[this->_size] = '\0';
			}
			else {
				this->erase(_Off);
			}
		}
	}

	template<typename T>
	void basic_string<T>::erase(basic_string<T>::iterator _begin, basic_string<T>::iterator _end)
	{
		if (_end >= _begin) {
			if (_begin >= this->begin()) {
				size_t _Off = _begin - this->begin();
				size_t _Count = _end - _begin;
				if (_Off <= this->_size) {
					if (this->_size - _Off > _Count) {
						this->_size -= _Count;
						this->container.erase(this->container.begin() + _Off, this->container.begin() + _Off + _Count);
						this->container[this->_size] = '\0';
					}
					else {
						this->erase(_Off);
					}
				}
			}
			else {
				throw IteratorOutOfRangeException{};
			}
		}
		else {
			throw IteratorErrorException{};
		}
	}

	template<typename T>
	void basic_string<T>::erase(basic_string<T>::iterator _pos)
	{
		if (_pos >= this->begin()) {
			if (_pos < this->end()) {
				size_t _Where = _pos - this->begin();
				if (_Where <= this->_size) {
					this->_size--;
					this->container.erase(_pos, _pos + 1);
				}
			}
		}
		else {
			throw IteratorErrorException{};
		}
	}

	template<typename T>
	void basic_string<T>::append(size_t _Count, char c)
	{
		for (size_t i = 0; i < _Count; i++) {
			this->push_back(c);
		}
	}

	template<typename T>
	void basic_string<T>::append(const basic_string<T>& _str)
	{
		*this += _str;
	}

	template<typename T>
	void basic_string<T>::append(const basic_string<T>& _str, size_t _Begin)
	{
		if (_Begin <= _str.size()) {
			if (_Begin == 0) {
				*this += _str;
			}
			else {
				for (auto it = _str.begin() + _Begin; it != _str.end(); it++) {
					this->push_back(*it);
				}
			}
		}
		else {
			throw std::out_of_range("Begin index out of range!");
		}
	}

	template<typename T>
	void basic_string<T>::append(const basic_string<T>& _str, size_t _Begin, size_t _Count)
	{
		if (_Begin <= _str.size()) {
			if (_Begin + _Count > _str.size()) {
				_Count = _str.size() - _Begin;
			}
			for (size_t i = 0; i < _Count; i++) {
				this->push_back(_str[_Begin + i]);
			}
		}
		else {
			throw std::out_of_range("Begin index out of range!");
		}
	}

	template<typename T>
	void basic_string<T>::append(const char* _str)
	{
		*this += _str;
	}

	template<typename T>
	void basic_string<T>::append(const char* _str, size_t _Begin)
	{
		if (_Begin <= strlen(_str)) {
			*this += (_str + _Begin);
		}
		else {
			throw std::out_of_range("Begin index out of range!");
		}
	}

	template<typename T>
	void basic_string<T>::append(const char* _str, size_t _Begin, size_t _Count)
	{
		if (_Begin <= strlen(_str)) {
			if (strlen(_str) - _Begin < _Count) {
				_Count = strlen(_str) - _Begin;
			}
			if (_Count != 0) {
				for (size_t i = 0; i < _Count; i++) {
					this->push_back(_str[_Begin + i]);
				}
			}
		}
		else {
			throw std::out_of_range("Begin index out of range!");
		}
	}

	template<typename T>
	void basic_string<T>::append(std::initializer_list<char> l)
	{
		for (auto& i : l) {
			this->push_back(i);
		}
	}

	template<typename T>
	void basic_string<T>::push_back(char c)
	{
		if (this->_size == this->container.size()) {
			this->container.push_back(c);
		}
		else {
			this->container[_size] = c;
		}
		this->container.push_back('\0');
		this->_size++;
	}

	template<typename T>
	size_t basic_string<T>::find(char c, size_t _begin_pos)
	{
		for (size_t i = _begin_pos; i < this->_size; i++) {
			if (this->container[i] == c) {
				return i;
			}
		}
		return -1;
	}

	template<typename T>
	size_t basic_string<T>::find(const char* _str, size_t _begin_pos)
	{
		size_t length{ strlen(_str) };
		bool isFind{ true };
		if (this->_size < length) return -1;
		else {
			for (size_t i = _begin_pos; i < this->_size; i++) {
				if (this->_size - i >= length) {
					if (this->container[i] == _str[0]) {
						isFind = true;
						for (size_t j = 1; j < length; j++) {
							if (this->container[i + j] != _str[j]) {
								i = i + j - 1;
								isFind = false;
								break;
							}
						}
						if (isFind) return i;
					}
				}
				else {
					return -1;
				}
			}
			return -1;
		}
	}

	template<typename T>
	size_t basic_string<T>::find(const basic_string<T>& _str, size_t _begin_pos)
	{
		size_t length{ _str.size() };
		bool isFind{ true };
		if (this->_size < length) return -1;
		else {
			for (size_t i = _begin_pos; i < this->_size; i++) {
				if (this->_size - i >= length) {
					if (this->container[i] == _str[0]) {
						isFind = true;
						for (size_t j = 1; j < length; j++) {
							if (this->container[i + j] != _str[j]) {
								i = i + j - 1;
								isFind = false;
								break;
							}
						}
						if (isFind) return i;
					}
				}
				else {
					return -1;
				}
			}
			return -1;
		}
	}

	template<typename T>
	void basic_string<T>::swap(basic_string<T>& _Right)
	{
		basic_string<T> temp{ _Right };
		_Right.clear();
		for (auto& c : *this) {
			_Right.push_back(c);
		}
		this->clear();
		for (auto& c : temp) {
			this->push_back(c);
		}
	}

	template<typename T>
	bool operator==(const char* _Left, const basic_string<T>& _Right)
	{
		return _Right == _Left;
	}

	template<typename T>
	bool operator!=(const char* _Left, const basic_string<T>& _Right)
	{
		return _Right != _Left;
	}

	template<typename T>
	bool operator>(const char* _Left, const basic_string<T>& _Right)
	{
		return _Right < _Left;
	}

	template<typename T>
	bool operator<(const char* _Left, const basic_string<T>& _Right)
	{
		return _Right > _Left;
	}

	template<typename T>
	bool operator>=(const char* _Left, const basic_string<T>& _Right)
	{
		return _Right <= _Left;
	}

	template<typename T>
	bool operator<=(const char* _Left, const basic_string<T>& _Right)
	{
		return _Right >= _Left;
	}

	template<typename T>
	std::istream& getline(std::istream& input, basic_string<T>& _Target, const char _End = '\n')
	{
		_Target.clear();
		unsigned char c = input.get();
		while (c != '\n') {
			_Target.push_back(c);
			c = input.get();
		}
		return input;
	}

	using string = basic_string<char>;
	using wstring = basic_string<wchar_t>;
#ifdef __cpp_lib_char8_t
	using u8string = basic_string<char8_t>;
#endif // __cpp_lib_char8_t
	using u16string = basic_string<char16_t>;
	using u32string = basic_string<char32_t>;
}
