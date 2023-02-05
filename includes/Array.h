#pragma once
#include <iostream>
#include <cstring>
#include "exceptions.h"

namespace MySTL
{
	template<typename T, size_t _Size>
	class Array
	{
	private:
		T _data[_Size]{ 0 };
		size_t _size{ _Size };
	public:
		using iterator = T*;
		using const_iterator = const T*;
	public:
		Array() = default;
		Array(T _array[_Size]);
		Array(const Array<T, _Size>& _array);
		Array(Array<T, _Size>&& _array) noexcept;
		Array(std::initializer_list<T> l);
		~Array() = default;

		constexpr void fill(const T& _value); // 填满_value
		constexpr void swap(Array<T, _Size> _array); // 仅交换值(线性时间复杂度)

		T& front() noexcept;
		T& back() noexcept;

		constexpr size_t size() const;
		constexpr size_t max_size() const;

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		constexpr const T* data() const noexcept;

		T& operator[](size_t _index);
		const T& operator[](size_t _index) const;
		T& at(size_t _index);

		void operator=(std::initializer_list<T> l);
		constexpr bool operator==(Array<T, _Size> _array);
		constexpr bool operator!=(Array<T, _Size> _array);

		constexpr void view();

		bool empty() { return false; }
	};

	template<typename T, size_t _Size>
	Array<T, _Size>::Array(T _array[_Size])
	{
		memmove(this->_data, _array, _Size * sizeof(T));
	}

	template<typename T, size_t _Size>
	Array<T, _Size>::Array(const Array<T, _Size>& _array)
	{
		memmove(this->_data, _array._data, _Size * sizeof(T));
	}

	template<typename T, size_t _Size>
	Array<T, _Size>::Array(Array<T, _Size>&& _array) noexcept
	{
		this->_data = _array._data;
		_array.~Array();
	}

	template<typename T, size_t _Size>
	Array<T, _Size>::Array(std::initializer_list<T> l)
	{
		if (l.size() <= _Size) {
			size_t i = 0;
			for (auto it = l.begin(); it != l.end(); it++) {
				this->_data[i++] = *it;
			}
		}
		else {
			throw std::runtime_error{ "Invalid initializer list size" };
		}
	}

	template<typename T, size_t _Size>
	inline constexpr void Array<T, _Size>::fill(const T& _value)
	{
		for (size_t i = 0; i < _Size; i++) {
			this->_data[i] = _value;
		}
	}

	template<typename T, size_t _Size>
	inline constexpr void Array<T, _Size>::swap(Array<T, _Size> _array)
	{
		for (size_t i = 0; i < _Size; i++) {
			T temp{ _array[i] };
			_array[i] = this->at(i);
			this->_data[i] = temp;
		}
	}

	template<typename T, size_t _Size>
	inline constexpr size_t Array<T, _Size>::size() const
	{
		return this->_size;
	}

	template<typename T, size_t _Size>
	inline constexpr size_t Array<T, _Size>::max_size() const
	{
		return this->_size;
	}

	template<typename T, size_t _Size>
	inline Array<T, _Size>::iterator Array<T, _Size>::begin()
	{
		return this->_data;
	}

	template<typename T, size_t _Size>
	inline Array<T, _Size>::iterator Array<T, _Size>::end()
	{
		return this->_data + this->_size;
	}

	template<typename T, size_t _Size>
	inline Array<T, _Size>::const_iterator Array<T, _Size>::begin() const
	{
		return this->_data;
	}

	template<typename T, size_t _Size>
	inline Array<T, _Size>::const_iterator Array<T, _Size>::end() const
	{
		return this->_data + this->_size;
	}

	template<typename T, size_t _Size>
	inline constexpr const T* Array<T, _Size>::data() const noexcept
	{
		return this->_data;
	}

	template<typename T, size_t _Size>
	inline T& Array<T, _Size>::operator[](size_t _index)
	{
		return this->_data[_index];
	}

	template<typename T, size_t _Size>
	inline const T& Array<T, _Size>::operator[](size_t _index) const
	{
		return this->_data[_index];
	}

	template<typename T, size_t _Size>
	inline T& Array<T, _Size>::at(size_t _index)
	{
		if (_index < this->_size) {
			return this->_data[_index];
		}
		else {
			throw std::out_of_range{ "Index Out of Range!" };
		}
	}

	template<typename T, size_t _Size>
	inline void Array<T, _Size>::operator=(std::initializer_list<T> l)
	{
		if (l.size() <= _Size) {
			size_t i = 0;
			for (auto it = l.begin(); it != l.end(); it++) {
				this->_data[i++] = *it;
			}
		}
		else {
			throw std::runtime_error{ "Invalid initializer list size" };
		}
	}

	template<typename T, size_t _Size>
	inline constexpr bool Array<T, _Size>::operator==(Array<T, _Size> _array)
	{
		for (size_t i = 0; i < _Size; i++) {
			if (this->_data[i] != _array[i]) {
				return false;
			}
		}
		return true;
	}

	template<typename T, size_t _Size>
	inline constexpr bool Array<T, _Size>::operator!=(Array<T, _Size> _array)
	{
		return !(*this == _array);
	}

	template<typename T, size_t _Size>
	inline T& Array<T, _Size>::front() noexcept
	{
		return this->_data[0];
	}

	template<typename T, size_t _Size>
	inline T& Array<T, _Size>::back() noexcept
	{
		return this->_data[this->_size - 1];
	}

	template<typename T, size_t _Size>
	inline constexpr void Array<T, _Size>::view()
	{
		for (auto& i : this->_data) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}

	template<typename T>
	class Array<T, 0>
	{
	public:
		using iterator = T*;
		using const_iterator = const T*;
	public:
		Array() = default;
		Array(T _array[0]) {}
		Array(const Array<T, 0>& _array) {}
		Array(Array<T, 0>&& _array) noexcept {}
		Array(std::initializer_list<T> l) {}

		constexpr void fill(const T& _value) {}
		constexpr void swap(Array<T, 0> _array) {}

		void front() { throw OutOfRangeException{}; }
		void back() { throw OutOfRangeException{}; }

		size_t size() { return 0; }
		size_t max_size() { return 0; }

		iterator begin() { return nullptr; }
		iterator end() { return nullptr; }
		const_iterator begin() const { return nullptr; }
		const_iterator end() const { return nullptr; }

		const T* data() const noexcept { return nullptr; }

		T& operator[](size_t _index) { return this->_data[_index]; }
		T& at(size_t _index) { throw OutOfRangeException{}; }

		void operator=(std::initializer_list<T> l) {}
		constexpr bool operator==(Array<T, 0> _array) { return true; }
		constexpr bool operator!=(Array<T, 0> _array) { return false; }

		bool empty() { return true; }
	};
}

