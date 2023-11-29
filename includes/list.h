#pragma once
#include <initializer_list>
#include "exceptions.h"

namespace MySTL
{
	template<typename T>
	class Node
	{
	public:
		T value;
		Node* next;
		Node* last;
	public:
		Node() = default;
		Node(const T& val);
		~Node();
	};

	template<typename T>
	inline Node<T>::Node(const T& val)
		: value(val), next(nullptr), last(nullptr) {}

	template<typename T>
	inline Node<T>::~Node()
	{
		last = nullptr;
		next = nullptr;
	}

	template<typename T>
	class Iterator
	{
	private:
		Node<T>* node_ptr{ nullptr };
	public:
		Iterator() = delete;
		Iterator(Node<T>& _node);
		Iterator(Node<T>* _node_ptr);
		~Iterator() = default;

		T& operator*();
		T* operator->();
		Iterator<T> operator+(size_t _Off);
		Iterator<T> operator-(size_t _Off);
		Iterator<T> operator++();
		Iterator<T> operator++(int n);
		Iterator<T> operator--();
		Iterator<T> operator--(int n);
		
		bool operator==(Iterator<T> _Right);
		bool operator!=(Iterator<T> _Right);

		Iterator<T>& operator=(const Iterator<T>& _Right);
		Iterator<T>& operator+=(size_t _Off);
		Iterator<T>& operator-=(size_t _Off);
	};

	template<typename T>
	inline Iterator<T>::Iterator(Node<T>& _node)
	{
		node_ptr = &(_node);
	}

	template<typename T>
	inline Iterator<T>::Iterator(Node<T>* _node_ptr)
	{
		node_ptr = _node_ptr;
	}

	template<typename T>
	inline T& Iterator<T>::operator*()
	{	
		return node_ptr->value;
	}

	template<typename T>
	inline T* Iterator<T>::operator->()
	{
		return &(node_ptr->value);
	}

	template<typename T>
	inline Iterator<T> Iterator<T>::operator+(size_t _Off)
	{
		Node<T>* _target_node_ptr{ this };
		for (size_t i = 0; i < _Off; i++) {
			if (_target_node_ptr->next != nullptr) {
				_target_node_ptr = _target_node_ptr->next;
			}
			else {
				_target_node_ptr = nullptr;
				break;
			}
		}
		return Iterator<T>(_target_node_ptr);
	}

	template<typename T>
	inline Iterator<T> Iterator<T>::operator-(size_t _Off)
	{
		Node<T>* _target_node_ptr{ this };
		for (size_t i = 0; i < _Off; i++) {
			if (_target_node_ptr->last != nullptr) {
				_target_node_ptr = _target_node_ptr->last;
			}
			else {
				_target_node_ptr = nullptr;
				break;
			}
		}
		return Iterator<T>(_target_node_ptr);
	}

	template<typename T>
	inline Iterator<T> Iterator<T>::operator++() // ++a
	{
		*this += 1;
		return *this;
	}

	template<typename T>
	inline Iterator<T> Iterator<T>::operator++(int n) // a++
	{
		Node<T>* temp_ptr{ node_ptr };
		*this += 1;
		return Iterator<T>(temp_ptr);
	}

	template<typename T>
	inline Iterator<T> Iterator<T>::operator--() // --a
	{
		*this -= 1;
		return this;
	}

	template<typename T>
	inline Iterator<T> Iterator<T>::operator--(int n) // a--
	{
		Node<T>* temp_ptr{ node_ptr };
		*this -= 1;
		return Iterator<T>(temp_ptr);
	}

	template<typename T>
	inline bool Iterator<T>::operator==(Iterator<T> _Right)
	{
		return node_ptr == _Right.node_ptr;
	}
	template<typename T>
	inline bool Iterator<T>::operator!=(Iterator<T> _Right)
	{
		return !(*this == _Right);
	}

	template<typename T>
	inline Iterator<T>& Iterator<T>::operator=(const Iterator<T>& _Right)
	{
		node_ptr = _Right.node_ptr;
		return *this;
	}

	template<typename T>
	inline Iterator<T>& Iterator<T>::operator+=(size_t _Off)
	{
		for (size_t i = 0; i < _Off; i++) {
			if (node_ptr->next != nullptr) {
				node_ptr = node_ptr->next;
			}
			else {
				node_ptr = nullptr;
				break;
			}
		}
		return *this;
	}

	template<typename T>
	inline Iterator<T>& Iterator<T>::operator-=(size_t _Off)
	{
		for (size_t i = 0; i < _Off; i++) {
			if (node_ptr->last != nullptr) {
				node_ptr = node_ptr->last;
			}
			else {
				node_ptr = nullptr;
				break;
			}
		}
		return *this;
	}

	template<typename T>
	class list
	{
	private:
		inline static Node<T>* _end{ new Node<T>{} };
	private:
		Node<T>* _head;
		Node<T>* _tail;
		size_t _size;
	public:
		using iterator = Iterator<T>;
		using const_iterator = const Iterator<T>;
	public:
		list() :
			_head(new Node<T>), _tail(nullptr), _size(0) 
		{
			_head->next = nullptr;
		};
		list(std::initializer_list<T> l);
		list(const list<T>& _Right);
		list(list<T>&& _mv_Right) noexcept;
		~list();

		iterator begin()
		{
			return Iterator(_head->next);
		}

		iterator end()
		{
			return Iterator(_end);
		}

		const_iterator begin() const
		{
			return Iterator(_head);
		}

		const_iterator end() const
		{
			return Iterator(_end);
		}

		void insert(list<T>::const_iterator _Where, const T& val);

		void push_back(const T& value);
		void push_front(const T& value);
		void pop_back();
		void pop_front();
		void clear();

		void erase(list<T>::const_iterator _Where);
		void erase(list<T>::const_iterator _First, list<T>::const_iterator _Last);

		T& front();
		T& back();
		const T& front() const;
		const T& back() const;

		list<T>& operator=(const list<T>& _Right);
		list<T>& operator=(list<T>&& _Right);
		void view() const;
		const size_t size() const;
		const bool empty() const;
	};

	template<typename T>
	inline list<T>::list(std::initializer_list<T> l) : list()
	{
		Node<T>* _tail_node_ptr{ _head };
		for (auto& val : l) {
			Node<T>* _node{ new Node<T>{ val } };
			_tail_node_ptr->next = _node;
			_node->last = _tail_node_ptr;
			_tail_node_ptr = _node;
			_size++;
		}
		_tail = _tail_node_ptr;
		_tail->next = _end;
	}

	template<typename T>
	inline list<T>::list(const list<T>& _Right) : list()
	{
		Node<T>* _tail_node_ptr{ _head };
		for (auto& val : _Right) {
			Node<T>* _node{ new Node<T>{val} };
			_tail_node_ptr->next = _node;
			_node->last = _tail_node_ptr;
			_tail_node_ptr = _node;
			_size++;
		}
		_tail = _tail_node_ptr;
		_tail = _end;
	}
	
	template<typename T>
	inline list<T>::list(list<T>&& _mv_Right) noexcept
		: _head(_mv_Right._head)
		, _tail(_mv_Right._tail)
		, _size(_mv_Right._size)
	{
		_mv_Right._head = nullptr;
		_mv_Right._tail = nullptr;
		_mv_Right._size = 0;
	}

	template<typename T>
	inline list<T>::~list()
	{
		Node<T>* _node_ptr{ _head }, * _temp_ptr{ nullptr };
		while (_node_ptr != nullptr) {
			_temp_ptr = _node_ptr;
			_node_ptr = _node_ptr->next;
			delete _temp_ptr;
		}
		_head = nullptr;
		_tail = nullptr;
		_size = 0;
	}

	template<typename T>
	inline void list<T>::push_back(const T& value)
	{
		Node<T>* temp_node_ptr = new Node<T>{ value };
		temp_node_ptr->next = nullptr;
		_size++;
		if (_size == 0) {
			temp_node_ptr->last = _head;
			_tail = temp_node_ptr;
			_head->next = temp_node_ptr;
		}
		else {
			_tail->next = temp_node_ptr;
			temp_node_ptr->last = _tail;
			_tail = temp_node_ptr;
		}
		_tail->next = _end;
	}
	
	template<typename T>
	inline void list<T>::push_front(const T& value)
	{
		Node<T>* temp_node_ptr = new Node<T>{ value };
		Node<T>* rest{ _head->next };
		_head->next = temp_node_ptr;
		temp_node_ptr->next = rest;
		temp_node_ptr->last = _head;
		if (rest) rest->last = temp_node_ptr;
		_size++;
		if (_size == 0) {
			_tail = temp_node_ptr;
			temp_node_ptr->next = nullptr;
		}
		_tail->next = _tail;
	}
	
	template<typename T>
	void list<T>::pop_back()
	{
		if (!empty()) {
			Node<T>* temp{ _tail->last };
			temp->next = _tail->next;
			_size--;
			delete temp;
		}
	}
	
	template<typename T>
	inline void list<T>::pop_front()
	{
		if (!empty()) {
			Node<T>* temp{ _head->next };
			_head->next = temp->next;
			if (!_head->next) {
				_head->next->last = _head;
			}
			_size--;
			delete temp;
		}
	}
	
	template<typename T>
	inline void list<T>::clear()
	{
		Node<T>* _node_ptr{ _head->next }, * _temp_ptr{ nullptr };
		while (_node_ptr != nullptr) {
			_temp_ptr = _node_ptr;
			_node_ptr = _node_ptr->next;
			delete _temp_ptr;
		}
		_tail = nullptr;
		_size = 0;
	}

	template<typename T>
	inline T& list<T>::front()
	{
		return _head->value;
	}

	template<typename T>
	inline T& list<T>::back()
	{
		return _tail->value;
	}

	template<typename T>
	inline const T& list<T>::front() const
	{
		return _head->value;
	}

	template<typename T>
	inline const T& list<T>::back() const
	{
		return _tail->value;
	}

	template<typename T>
	inline list<T>& list<T>::operator=(const list<T>& _Right)
	{
		clear();
		for (auto it = _Right.begin(); it != _Right.end(); it++) {
			push_back(*it);
		}
		return *this;
	}

	template<typename T>
	inline list<T>& list<T>::operator=(list<T>&& _Right)
	{
		clear();
		_head = _Right._head;
		_tail = _Right._tail;
		_size = _Right._size;
		return *this;
	}

	template<typename T>
	inline void list<T>::view() const
	{
		if (!empty()) {
			for (auto& i : *this) {
				std::cout << i << " ";
			}
			std::cout << std::endl;
		}
	}

	template<typename T>
	inline const size_t list<T>::size() const
	{
		return _size;
	}

	template<typename T>
	inline const bool list<T>::empty() const
	{
		return (_size == 0);
	}
}
