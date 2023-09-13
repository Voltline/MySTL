#pragma once
#include <initializer_list>

namespace MySTL
{
	template<typename T>
	class Node
	{
	public:
		T value;
		Node* next{ nullptr };
		Node* last{ nullptr };
	public:
		Node() = default;
		Node(T value);
		~Node();
	};

	template<typename T>
	inline Node<T>::Node(T value)
	{
		value = value;
	}

	template<typename T>
	inline Node<T>::~Node()
	{
		if (last != nullptr && next != nullptr) {
			last->next = next;
		}
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
		if (node_ptr == _Right.node_ptr) return true;
		else return false;
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
		Node<T>* _head;
		Node<T>* _tail;
		Node<T>* _end;
		size_t _size;
	public:
		using iterator = Iterator<T>;
		using const_iterator = const Iterator<T>;
	public:
		list() : _head(nullptr), _tail(nullptr), _end(nullptr), _size(0) {}
		list(std::initializer_list<T> l);
		list(const list<T>& _Right);
		list(list<T>&& _mv_Right) noexcept;
		~list();

		iterator begin()
		{
			return Iterator<T>(_head);
		}

		iterator end()
		{
			return Iterator<T>(_end);
		}

		const_iterator begin() const
		{
			return Iterator(_head);
		}

		const_iterator end() const
		{
			return Iterator(_end);
		}

		void insert();

		void push_back(T value);
		void push_front(T value);
		void pop_back();
		void pop_front();
		void clear();

		void erase(list<T>::const_iterator _Where);
		void erase(list<T>::const_iterator _First, list<T>::const_iterator _Last);

		T& front();
		T& back();

		list<T>& operator=(const list<T>& _Right);
		list<T>& operator=(list<T>&& _Right);
		void view();
		const size_t size();
	};

	template<typename T>
	inline list<T>::list(std::initializer_list<T> l)
		: _head(nullptr)
		, _tail(nullptr)
		, _end(nullptr)
		, _size(0)
	{
		size_t length{ l.size() };
		if (length == 1) {
			_head = new Node<T>{ *l.begin() };
			_tail = _head;
			_size++;
		}
		else {
			size_t i = 0;
			for (auto& val : l) {
				if (i == 0) {
					_head = new Node<T>{ val };
					_tail = _head;
				}
				else if (i < length) {
					Node<T>* temp = new Node<T>{ val };
					temp->last = _tail;
					_tail->next = temp;
					_tail = temp;
				}
				i++;
				_size++;
			}
		}
		_end = new Node<T>{};
		_end->last = _tail;
		_tail->next = _end;
	}

	template<typename T>
	inline list<T>::list(const list<T>& _Right)
		: _head(nullptr)
		, _tail(nullptr)
		, _end(nullptr)
		, _size(0)
	{
		size_t length = _Right._size;
		if (_Right._size == 1) {
			_head = new Node<T>{ *_Right._head };
			_end = _head;
			_size++;
		}
		else {
			size_t i = 0;
			for (auto& val : _Right) {
				if (i == 0) {
					_head = new Node<T>{ val };
					_tail = _head;
				}
				else if (i < length) {
					Node<T>* temp = new Node<T>{ val };
					temp->last = _tail;
					_tail->next = temp;
					_tail = temp;
				}
				i++;
				_size++;
			}
		}
		_end = new Node<T>{};
		_end->last = _tail;
		_tail->next = _end;
	}
	
	template<typename T>
	inline list<T>::list(list<T>&& _mv_Right) noexcept
		: _head(_mv_Right._head)
		, _tail(_mv_Right._tail)
		, _end(_mv_Right._end)
		, _size(_mv_Right._size)
	{
		_mv_Right._head = nullptr;
		_mv_Right._tail = nullptr;
		_mv_Right._end = nullptr;
		_mv_Right._size = 0;
	}

	template<typename T>
	inline list<T>::~list()
	{
		Node<T>* _node_ptr{ _head }, * _temp_ptr{ nullptr };
		while (_node_ptr != _end) {
			_temp_ptr = _node_ptr;
			_node_ptr = _node_ptr->next;
			delete _temp_ptr;
		}
		delete _end;
		_head = nullptr;
		_tail = nullptr;
		_end = nullptr;
		_size = 0;
	}

	template<typename T>
	inline void list<T>::push_back(T value)
	{
		if (_size == 1) {
			_tail = new Node<T>{ value };
			_head->next = _tail;
			_tail->last = _head;

			_tail->next = _end;
			_end->last = _tail;
			_size++;
		}
		else {
			Node<T>* temp_node_ptr = new Node<T>{ value };
			_tail->next = temp_node_ptr;
			temp_node_ptr->last = _tail;
			
			_tail = temp_node_ptr;
			_tail->next = _end;
			_end->last = _tail;

			_size++;
		}
	}
	
	template<typename T>
	inline void list<T>::push_front(T value)
	{
		Node<T>* temp_node_ptr = new Node<T>{ value };
		if (_size == 1) {
			_head = temp_node_ptr;
			_head->next = _tail;
			_tail->last = _head;
			_head->last = nullptr;
			_size++;
		}
		else {
			temp_node_ptr->next = _head;
			_head->last = temp_node_ptr;
			_head = temp_node_ptr;
			_size++;
		}
	}
	
	template<typename T>
	void list<T>::pop_back()
	{
		/*
		if (_size != 1) {
			Node<T>* temp = _tail;
			_tail = _tail->last;
			_tail->next = _end;
			_end->last = _tail;
			temp->~Node();
		}
		else {
			Node<T>* temp = _tail;
			_
		}

		_size--;*/
	}
	
	template<typename T>
	inline void list<T>::pop_front()
	{

	}
	
	template<typename T>
	inline void list<T>::clear()
	{
		Node<T>* _node_ptr{ _head }, * _temp_ptr{ nullptr };
		while (_node_ptr != _end) {
			_temp_ptr = _node_ptr;
			_node_ptr = _node_ptr->next;
			delete _temp_ptr;
		}
		delete _end;
		_head = nullptr;
		_tail = nullptr;
		_end = nullptr;
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
	inline void list<T>::view()
	{
		for (auto& i : *this) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}

	template<typename T>
	inline const size_t list<T>::size()
	{
		return _size;
	}
}
