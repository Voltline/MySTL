#include "string.h"
#include "exceptions.h"

namespace MySTL
{
	string::string()
	{
		this->container = vector<unsigned char>{};
	}

	string::string(const char* _c_str)
	{
		size_t length{ strlen(_c_str) };
		this->_size = length;
		this->container =
			vector<unsigned char>{
				const_cast<unsigned char*>((unsigned char*)_c_str),
				const_cast<unsigned char*>((unsigned char*)(_c_str + length))
		};
		this->container[_size] = '\0';
	}

	string::string(const char* _c_str, size_t _size)
	{
		size_t length{ _size };
		if (_size > strlen(_c_str)) {
			length = strlen(_c_str);
		}

		this->_size = length;
		this->container =
			vector<unsigned char>{
				const_cast<unsigned char*>((unsigned char*)_c_str),
				const_cast<unsigned char*>((unsigned char*)(_c_str + length))
		};
		this->container[_size] = '\0';
	}

	string::string(const char* _c_str, size_t _begin, size_t _size)
	{
		size_t length{ _size };
		if (_size > strlen(_c_str + _begin)) {
			length = strlen(_c_str + _begin);
		}

		this->_size = length;
		this->container =
			vector<unsigned char>{
				const_cast<unsigned char*>((unsigned char*)_c_str),
				const_cast<unsigned char*>((unsigned char*)(_c_str + length))
		};
		this->container[_size] = '\0';
	}

	string::string(size_t _size, char c)
	{
		this->container = vector<unsigned char>(_size, c);
		this->_size = _size;
	}

	string::string(const string& _str)
	{
		this->container = vector<unsigned char>(_str.container);
		this->_size = _str._size;
	}

	string::string(string&& _mv_str) noexcept
	{
		this->container = std::move(_mv_str.container);
		this->_size = _mv_str._size;
		_mv_str.container = vector<unsigned char>{};
	}

	string::string(std::initializer_list<char> l)
	{
		this->container = vector<unsigned char>(l.size() + 128);
		this->_size = l.size();
		for (auto it = l.begin(); it != l.end(); it++) {
			this->container.push_back(static_cast<unsigned char>(*it));
		}
		this->container.push_back('\0');
	}

	string::~string()
	{
		this->_size = 0;
		this->container.~vector();
	}

	string& string::operator=(const string& _Right)
	{
		this->container.~vector();
		this->container = _Right.container;
		this->_size = _Right._size;
		return *this;
	}

	string& string::operator=(string&& _Right) noexcept
	{
		this->container.~vector();
		this->container = std::move(_Right.container);
		this->_size = _Right._size;
		return *this;
	}

	string& string::operator=(const char* _str)
	{
		this->container.~vector();
		size_t length{ strlen(_str) };
		this->container = vector<unsigned char>(length + 128);
		this->_size = 0;
		for (size_t i = 0; i < length; i++) {
			this->container.push_back(_str[i]);
			this->_size++;
		}
		return *this;
	}

	string& string::operator=(char c)
	{
		this->clear();
		this->push_back(c);
		return *this;
	}

	string string::operator+(const string& _Right)
	{
		string temp{ *this };
		for (auto& i : _Right) {
			temp.push_back(i);
		}
		return temp;
	}

	string string::operator+(const char* _str)
	{
		string temp{ *this };
		size_t length{ strlen(_str) };
		for (size_t i = 0; i < length; i++) {
			temp.push_back(_str[i]);
		}
		return temp;
	}

	string string::operator+(char c)
	{
		string temp{ *this };
		temp.push_back(c);
		return temp;
	}

	void string::operator+=(const string& _Right)
	{
		for (auto& i : _Right) {
			this->push_back(i);
		}
	}

	void string::operator+=(const char* _str)
	{
		size_t length{ strlen(_str) };
		for (size_t i = 0; i < length; i++) {
			this->push_back(_str[i]);
		}
	}

	void string::operator+=(char c)
	{
		this->push_back(c);
	}

	unsigned char& string::operator[](size_t _index)
	{
		return this->container[_index];
	}

	const unsigned char& string::operator[](size_t _index) const
	{
		return this->container[_index];
	}

	unsigned char& string::at(size_t _index)
	{
		if (_index <= this->_size) {
			return this->container[_index];
		}
		else {
			throw std::out_of_range("Index Out of Range");
		}
	}

	bool string::operator==(const string& _Right)
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

	bool string::operator!=(const string& _Right)
	{
		return !(*this == _Right);
	}

	bool string::operator>(const string& _Right)
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

	bool string::operator<(const string& _Right)
	{
		return (*this <= _Right) && (*this != _Right);
	}

	bool string::operator>=(const string& _Right)
	{
		return (*this > _Right) || (*this == _Right);
	}

	bool string::operator<=(const string& _Right)
	{
		return !(*this > _Right);
	}

	bool string::operator==(const char* _c_Right)
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

	bool string::operator!=(const char* _c_Right)
	{
		return !(*this == _c_Right);
	}

	bool string::operator>(const char* _c_Right)
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

	bool string::operator<(const char* _c_Right)
	{
		return (*this <= _c_Right) && (*this != _c_Right);
	}

	bool string::operator>=(const char* _c_Right)
	{
		return (*this > _c_Right) || (*this == _c_Right);
	}

	bool string::operator<=(const char* _c_Right)
	{
		return !(*this > _c_Right);
	}


	size_t string::size() const noexcept
	{
		return this->_size;
	}

	size_t string::capacity() const noexcept
	{
		return this->container.capacity();
	}

	bool string::empty() const noexcept
	{
		if (this->_size != 0) return false;
		else return true;
	}

	const unsigned char* string::data()
	{
		return this->container.data();
	}

	const unsigned char* string::c_str()
	{
		return this->container.data();
	}

	string::iterator string::begin()
	{
		return this->container.begin();
	}

	string::iterator string::end()
	{
		return this->container.begin() + this->_size;
	}

	string::const_iterator string::begin() const
	{
		return this->container.begin();
	}

	string::const_iterator string::end() const
	{
		return this->container.begin() + this->_size;
	}

	void string::reserve(size_t new_capacity_size)
	{
		this->container.reserve(new_capacity_size);
	}

	void string::resize(size_t new_elem_size)
	{
		this->container.resize(new_elem_size);
		this->_size = new_elem_size;
	}

	void string::clear()
	{
		this->_size = 0;
		this->container.clear();
	}

	void string::erase(const size_t _Where)
	{
		if (_Where <= this->_size) {
			this->_size = _Where;
			this->container.erase(this->container.begin() + _Where, this->container.end());
			this->container.push_back('\0');
		}
	}

	void string::erase(const size_t _Off, const size_t _Count)
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

	void string::erase(iterator _begin, iterator _end)
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

	void string::erase(iterator _pos)
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

	void string::append(size_t _Count, char c)
	{
		for (size_t i = 0; i < _Count; i++) {
			this->push_back(c);
		}
	}

	void string::append(const string& _str)
	{
		*this += _str;
	}

	void string::append(const string& _str, size_t _Begin)
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

	void string::append(const string& _str, size_t _Begin, size_t _Count)
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

	void string::append(const char* _str)
	{
		*this += _str;
	}

	void string::append(const char* _str, size_t _Begin)
	{
		if (_Begin <= strlen(_str)) {
			*this += (_str + _Begin);
		}
		else {
			throw std::out_of_range("Begin index out of range!");
		}
	}

	void string::append(const char* _str, size_t _Begin, size_t _Count)
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

	void string::append(std::initializer_list<char> l)
	{
		for (auto& i : l) {
			this->push_back(i);
		}
	}

	void string::push_back(char c)
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

	size_t string::find(char c, size_t _begin_pos)
	{
		for (size_t i = _begin_pos; i < this->_size; i++) {
			if (this->container[i] == c) {
				return i;
			}
		}
		return -1;
	}

	size_t string::find(const char* _str, size_t _begin_pos)
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

	size_t string::find(const string& _str, size_t _begin_pos)
	{
		size_t length{ _str.size()};
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
	void string::swap(string& _Right)
	{
		string temp{ _Right };
		_Right.clear();
		for (auto& c : *this) {
			_Right.push_back(c);
		}
		this->clear();
		for (auto& c : temp) {
			this->push_back(c);
		}
	}

	bool operator==(const char* _Left, string _Right)
	{
		return _Right == _Left;
	}

	bool operator!=(const char* _Left, string _Right)
	{
		return _Right != _Left;
	}

	bool operator>(const char* _Left, string _Right)
	{
		return _Right < _Left;
	}

	bool operator<(const char* _Left, string _Right)
	{
		return _Right > _Left;
	}

	bool operator>=(const char* _Left, string _Right)
	{
		return _Right <= _Left;
	}
	bool operator<=(const char* _Left, string _Right)
	{
		return _Right >= _Left;
	}

	std::istream& getline(std::istream& input, string& _Target, const char _End)
	{
		_Target.clear();
		unsigned char c = input.get();
		while (c != '\n') {
			_Target.push_back(c);
			c = input.get();
		}
		return input;
	}
}
