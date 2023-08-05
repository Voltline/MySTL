#pragma once
#include <iostream>
#include <cstring>
#include "exceptions.h"

namespace MySTL
{
	template<typename T, size_t _Size>
	class array
	{
	private:
		T _data[_Size];
		size_t _size{ _Size };
	public:
		using iterator = T*;
		using const_iterator = const T*;
	public:
		array() = default;
		array(T _array[_Size]);
		array(const array<T, _Size>& _array);
		array(std::initializer_list<T> l);
		~array() = default;

		constexpr void fill(const T& _value); // 填满_value
		constexpr void swap(array<T, _Size>& _array); // 仅交换值(线性时间复杂度)

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
		constexpr bool operator==(array<T, _Size> _array);
		constexpr bool operator!=(array<T, _Size> _array);

		constexpr void view();

		bool empty() { return false; }
	};

	template<typename T, size_t _Size>
	array<T, _Size>::array(T _array[_Size])
	{
		for (size_t i = 0; i < _Size; i++) {
			_data[i] = _array[i];
		}
	}

	template<typename T, size_t _Size>
	array<T, _Size>::array(const array<T, _Size>& _array)
	{
		for (size_t i = 0; i < _Size; i++) {
			_data[i] = _array._data[i];
		}
	}

	template<typename T, size_t _Size>
	array<T, _Size>::array(std::initializer_list<T> l)
	{
		if (l.size() <= _Size) {
			size_t i = 0;
			for (auto it = l.begin(); it != l.end(); it++) {
				_data[i++] = *it;
			}
		}
		else {
			throw std::runtime_error{ "Invalid initializer list size" };
		}
	}

	template<typename T, size_t _Size>
	inline constexpr void array<T, _Size>::fill(const T& _value)
	{
		for (size_t i = 0; i < _Size; i++) {
			_data[i] = _value;
		}
	}

	template<typename T, size_t _Size>
	inline constexpr void array<T, _Size>::swap(array<T, _Size>& _array)
	{
		for (size_t i = 0; i < _Size; i++) {
			T temp{ _array[i] };
			_array[i] = at(i);
			_data[i] = temp;
		}
	}

	template<typename T, size_t _Size>
	inline constexpr size_t array<T, _Size>::size() const
	{
		return _size;
	}

	template<typename T, size_t _Size>
	inline constexpr size_t array<T, _Size>::max_size() const
	{
		return _size;
	}

	template<typename T, size_t _Size>
	inline array<T, _Size>::iterator array<T, _Size>::begin()
	{
		return _data;
	}

	template<typename T, size_t _Size>
	inline array<T, _Size>::iterator array<T, _Size>::end()
	{
		return _data + _size;
	}

	template<typename T, size_t _Size>
	inline array<T, _Size>::const_iterator array<T, _Size>::begin() const
	{
		return _data;
	}

	template<typename T, size_t _Size>
	inline array<T, _Size>::const_iterator array<T, _Size>::end() const
	{
		return _data + _size;
	}

	template<typename T, size_t _Size>
	inline constexpr const T* array<T, _Size>::data() const noexcept
	{
		return _data;
	}

	template<typename T, size_t _Size>
	inline T& array<T, _Size>::operator[](size_t _index)
	{
		return _data[_index];
	}

	template<typename T, size_t _Size>
	inline const T& array<T, _Size>::operator[](size_t _index) const
	{
		return _data[_index];
	}

	template<typename T, size_t _Size>
	inline T& array<T, _Size>::at(size_t _index)
	{
		if (_index < _size) {
			return _data[_index];
		}
		else {
			throw std::out_of_range{ "Index Out of Range!" };
		}
	}

	template<typename T, size_t _Size>
	inline void array<T, _Size>::operator=(std::initializer_list<T> l)
	{
		if (l.size() <= _Size) {
			size_t i = 0;
			for (auto it = l.begin(); it != l.end(); it++) {
				_data[i++] = *it;
			}
		}
		else {
			throw std::runtime_error{ "Invalid initializer list size" };
		}
	}

	template<typename T, size_t _Size>
	inline constexpr bool array<T, _Size>::operator==(array<T, _Size> _array)
	{
		for (size_t i = 0; i < _Size; i++) {
			if (_data[i] != _array[i]) {
				return false;
			}
		}
		return true;
	}

	template<typename T, size_t _Size>
	inline constexpr bool array<T, _Size>::operator!=(array<T, _Size> _array)
	{
		return !(*this == _array);
	}

	template<typename T, size_t _Size>
	inline T& array<T, _Size>::front() noexcept
	{
		return _data[0];
	}

	template<typename T, size_t _Size>
	inline T& array<T, _Size>::back() noexcept
	{
		return _data[_size - 1];
	}

	template<typename T, size_t _Size>
	inline constexpr void array<T, _Size>::view()
	{
		for (auto& i : _data) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}

	template<typename T>
	class array<T, 0>
	{
	public:
		using iterator = T*;
		using const_iterator = const T*;
	public:
		array() = default;
		array(T _array[0]) {}
		array(const array<T, 0>& _array) {}
		array(std::initializer_list<T> l) {}

		constexpr void fill(const T& _value) {}
		constexpr void swap(array<T, 0>& _array) {}

		void front() { throw OutOfRangeException{}; }
		void back() { throw OutOfRangeException{}; }

		size_t size() { return 0; }
		size_t max_size() { return 0; }

		iterator begin() { return nullptr; }
		iterator end() { return nullptr; }
		const_iterator begin() const { return nullptr; }
		const_iterator end() const { return nullptr; }

		const T* data() const noexcept { return nullptr; }

		T& operator[](size_t _index) { throw OutOfRangeException{}; }
		T& at(size_t _index) { throw OutOfRangeException{}; }

		void operator=(std::initializer_list<T> l) {}
		constexpr bool operator==(array<T, 0> _array) { return true; }
		constexpr bool operator!=(array<T, 0> _array) { return false; }

		bool empty() { return true; }
	};
}

