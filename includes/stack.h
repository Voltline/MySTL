#pragma once
#include "vector.h"

namespace MySTL
{
	template<typename T>
	class stack
	{
	private:
		vector<T> _data;
		size_t _size;
	public:
		stack() : _data(), _size(0) {}
		stack(const stack<T>& _stack);
		stack(stack<T>&& _stack);
		stack(std::initializer_list<T> l);
		stack(vector<T>::const_iterator first, vector<T>::const_iterator last);
		~stack();

		stack<T>& operator=(const stack<T>& _stack);
		stack<T>& operator=(stack<T>&& _stack);

		void push(const T& _value);
		void push(T&& _value);
		void pop();

		T& top();
		const T& top() const;
		size_t size() const;
		bool empty() const;
		void view() const;

		bool operator==(const stack<T>& _stack) const;
		bool operator!=(const stack<T>& _stack) const;
		bool operator<(const stack<T>& _stack) const;
		bool operator>(const stack<T>& _stack) const;
		bool operator>=(const stack<T>& _stack) const;
		bool operator<=(const stack<T>& _stack) const;
	};

	template<typename T>
	stack<T>::stack(const stack<T>& _stack)
		: _size(_stack._size), _data(_stack._data) {}

	template<typename T>
	stack<T>::stack(stack<T>&& _stack)
		: _size(_stack._size), _data(std::move(_stack._data)) {}

	template<typename T>
	stack<T>::stack(std::initializer_list<T> l)
	{
		for (auto& i : l) {
			_data.push_back(i);
			_size++;
		}
	}

	template<typename T>
	stack<T>::stack(vector<T>::const_iterator first, vector<T>::const_iterator last)
	{
		if (first <= last) {
			for (auto& it = first; it != last; it++) {
				_data.push_back(*it);
				_size++;
			}
		}
	}

	template<typename T>
	stack<T>::~stack()
	{
		_size = 0;
	}

	template<typename T>
	stack<T>& stack<T>::operator=(const stack<T>& _stack)
	{
		_data.~vector();
		_data = _stack._data;
		_size = _stack._size;
	}

	template<typename T>
	stack<T>& stack<T>::operator=(stack<T>&& _stack)
	{
		_data.~vector();
		_data = std::move(_stack._data);
		_size = _stack._size;
	}

	template<typename T>
	void stack<T>::push(const T& _value)
	{
		_data.push_back(_value);
		_size++;
	}

	template<typename T>
	void stack<T>::push(T&& _value)
	{
		_data.push_back(std::move(_value));
		_size++;
	}

	template<typename T>
	void stack<T>::pop()
	{
		_data.pop_back();
		_size--;
	}

	template<typename T>
	T& stack<T>::top()
	{
		return _data[_size - 1];
	}

	template<typename T>
	const T& stack<T>::top() const
	{
		return _data[_size - 1];
	}

	template<typename T>
	size_t stack<T>::size() const
	{
		return _size;
	}

	template<typename T>
	bool stack<T>::empty() const
	{
		return (_size == 0);
	}

	template<typename T>
	void stack<T>::view() const
	{
		_data.view();
	}

	template<typename T>
	bool stack<T>::operator==(const stack<T>& _stack) const
	{
		if (_size == _stack._size) {
			return _data == _stack._data;
		}
		else return false;
	}

	template<typename T>
	bool stack<T>::operator!=(const stack<T>& _stack) const
	{
		return !(*this == _stack);
	}

	template<typename T>
	bool stack<T>::operator<(const stack<T>& _stack) const
	{
		return _data < _stack._data;
	}

	template<typename T>
	bool stack<T>::operator>(const stack<T>& _stack) const
	{
		return _data > _stack._data;
	}

	template<typename T>
	bool stack<T>::operator>=(const stack<T>& _stack) const
	{
		return _data >= _stack._data;
	}

	template<typename T>
	bool stack<T>::operator<=(const stack<T>& _stack) const
	{
		return _data <= _stack._data;
	}
}

